package org.easyplay;

import lombok.extern.slf4j.Slf4j;

import static org.easyplay.UsbCommunicator.USB_RX_QUEUE_MAX_SIZE;
import static org.easyplay.UsbCommunicator.USB_TX_QUEUE_MAX_SIZE;


@Slf4j
public class Main {
    public static void main(String[] args) {
        log.info("Booting up app");
        UsbQueue usbTxQueue = new UsbQueue(USB_TX_QUEUE_MAX_SIZE, "usbTxQueue");
        UsbQueue usbRxQueue = new UsbQueue(USB_RX_QUEUE_MAX_SIZE, "usbRxQueue");
        new UsbCommunicator(usbTxQueue, usbRxQueue).start();
        new BrowserCommunicator(usbTxQueue, usbRxQueue).start();
        log.info("Booting up completed");
    }
}