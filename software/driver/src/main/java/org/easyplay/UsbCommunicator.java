package org.easyplay;

import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;
import lombok.extern.slf4j.Slf4j;

import java.util.Objects;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

@Slf4j
public class UsbCommunicator implements Runnable {
    public static final int USB_TX_TASK_PERIOD_MS = 50;
    public static final int USB_TX_QUEUE_MAX_SIZE = 1;
    public static final int USB_RX_QUEUE_MAX_SIZE = 10;
    private static final String TARGET_USB_DEVICE_NAME = "EasyPlayDevice";
    private static final String USB_MSG_HEARTBEAT = "EP_HEARTBEAT";
    private static final long USB_CONN_INIT_RETRY_PERIOD_MS = 500;
    private static final long USB_HEARTBEAT_PERIOD = 100;
    private static final int USB_MSG_MAX_SIZE = 15;
    private static final String DEVICE_CONNECTED_MSG = "DEVICE_CONNECTED";
    private final UsbQueue txQueue;
    private final UsbQueue rxQueue;
    private SerialPort devicePort = null;

    public UsbCommunicator(UsbQueue txQueue, UsbQueue rxQueue) {
        this.txQueue = txQueue;
        this.rxQueue = rxQueue;
    }

    @Override
    public void run() {
        closeUsbConnectionsOnExit();
        initConnection();
        processUsbTxQueue();
    }

    private static void closeUsbConnectionsOnExit() {
        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            log.info("Closing USB port connections");
            for (SerialPort port : SerialPort.getCommPorts()) {
                port.closePort();
            }
        }));
    }

    public void initConnection() {
        ScheduledExecutorService service = Executors.newSingleThreadScheduledExecutor();
        service.scheduleAtFixedRate(() -> {
            if (Objects.nonNull(devicePort)) {
                return;
            }
            if (connectToTargetDevice()) {
                log.info("USB device is connected");
                addUsbEventCallbacks();
                sendHeartbeatToDevice();
                rxQueue.addMsg(DEVICE_CONNECTED_MSG);
            }
        }, 0, USB_CONN_INIT_RETRY_PERIOD_MS, TimeUnit.MILLISECONDS);
    }

    private void processUsbTxQueue() {
        ScheduledExecutorService service = Executors.newSingleThreadScheduledExecutor();
        service.scheduleAtFixedRate(() -> {
            while (txQueue.size() > 0 && Objects.nonNull(devicePort)) {
                String msg = txQueue.popMsg();
                log.debug("USB TX: {}", msg);
                sendMsgToDevice(msg);
            }
        }, 0, USB_TX_TASK_PERIOD_MS, TimeUnit.MILLISECONDS);
    }

    private boolean connectToTargetDevice() {
        for (SerialPort port : SerialPort.getCommPorts()) {
            if (!port.getPortDescription().equals(TARGET_USB_DEVICE_NAME)) {
                continue;
            }
            if (!port.openPort()) {
                continue;
            }
            devicePort = port;
            return true;
        }
        return false;
    }

    private void addUsbEventCallbacks() {
        devicePort.addDataListener(new SerialPortDataListener() {
            @Override
            public int getListeningEvents() {
                return SerialPort.LISTENING_EVENT_DATA_RECEIVED | SerialPort.LISTENING_EVENT_PORT_DISCONNECTED;
            }

            @Override
            public void serialEvent(SerialPortEvent serialPortEvent) {
                switch (serialPortEvent.getEventType()) {
                    case SerialPort.LISTENING_EVENT_DATA_RECEIVED -> {
                        String rxMsg = new String(serialPortEvent.getReceivedData());
                        log.debug("USB RX message: {}", rxMsg);
                        rxQueue.addMsg(rxMsg);
                    }
                    case SerialPort.LISTENING_EVENT_PORT_DISCONNECTED -> {
                        if (Objects.isNull(devicePort)) {
                            return;
                        }
                        devicePort.closePort();
                        devicePort = null;
                        log.info("USB device is disconnected");
                    }
                }
            }
        });
    }

    private void sendHeartbeatToDevice() {
        ScheduledExecutorService service = Executors.newSingleThreadScheduledExecutor();
        service.scheduleAtFixedRate(() -> {
            sendMsgToDevice(USB_MSG_HEARTBEAT);
        }, 0, USB_HEARTBEAT_PERIOD, TimeUnit.MILLISECONDS);
    }

    private void sendMsgToDevice(String txMsg) {
        if (Objects.isNull(devicePort)) {
            return;
        }
        if (txMsg.length() > USB_MSG_MAX_SIZE) {
            log.warn("USB TX message size is too big: {}", txMsg);
            return;
        }
        devicePort.writeBytes(txMsg.getBytes(), txMsg.length());
    }

    public void start() {
        new Thread(this).start();
    }
}
