package org.easyplay;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import lombok.extern.slf4j.Slf4j;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.CharBuffer;
import java.nio.charset.StandardCharsets;
import java.util.Objects;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;


@Slf4j
public class BrowserCommunicator {
    private static final int MAX_BYTE_VALUE = 0xFF;
    private static final int MESSAGE_SIZE_BYTE_COUNT = 4;
    private static final int EOF_SYMBOL = -1;
    private static final int BITS_COUNT_IN_BYTE = 8;
    private static final int MESSAGE_CHECK_INTERVAL_MS = 10;
    private final BufferedReader bufferedReader;
    private final UsbQueue usbTxQueue;
    private final UsbQueue usbRxQueue;
    private final ObjectMapper objectMapper = new ObjectMapper();

    BrowserCommunicator(UsbQueue usbTxQueue, UsbQueue usbRxQueue) {
        this.usbTxQueue = usbTxQueue;
        this.usbRxQueue = usbRxQueue;
        bufferedReader = new BufferedReader(new InputStreamReader(System.in, StandardCharsets.UTF_8));
    }

    public void start() {
        handleMessagesFromBrowser();
        handleMessagesFromDevice();
    }

    private void handleMessagesFromBrowser() {
        ScheduledExecutorService service = Executors.newSingleThreadScheduledExecutor();
        service.scheduleAtFixedRate(() -> {
            String message;
            try {
                message = readMessageFromBrowser();
            } catch (IOException e) {
                log.error("Can't read message from browser. Exception: {}", e.getMessage());
                return;
            }
            if (Objects.isNull(message)) {
                return;
            }
            String parsedMessage;
            try {
                parsedMessage = parseMessageFromBrowser(message);
            } catch (JsonProcessingException e) {
                log.error(e.getMessage());
                return;
            }
            log.info("Received message from browser: {}", parsedMessage);
            usbTxQueue.addMsg(parsedMessage);
        }, 0, MESSAGE_CHECK_INTERVAL_MS, TimeUnit.MILLISECONDS);
    }

    private void handleMessagesFromDevice() {
        ScheduledExecutorService service = Executors.newSingleThreadScheduledExecutor();
        service.scheduleAtFixedRate(() -> {
            while (usbRxQueue.size() > 0) {
                try {
                    sendMessageToBrowser(usbRxQueue.popMsg());
                } catch (Exception e) {
                    log.error(e.getMessage());
                }
            }
        }, 0, MESSAGE_CHECK_INTERVAL_MS, TimeUnit.MILLISECONDS);
    }

    private String readMessageFromBrowser() throws IOException {
        if (!bufferedReader.ready()) {
            return null;
        }
        int messageSize = getRxMessageSize();
        CharBuffer buffer = CharBuffer.allocate(messageSize);
        if ((bufferedReader.read(buffer)) == EOF_SYMBOL) {
            throw new IOException("RX message is shorter than promised");
        }
        buffer.rewind();
        return buffer.toString();
    }

    private String parseMessageFromBrowser(String message) throws JsonProcessingException {
        JsonNode jsonNode = objectMapper.readTree(message);
        return jsonNode.get("message").asText();
    }


    private void sendMessageToBrowser(String message) throws Exception {
        StringBuilder packet = new StringBuilder();
        String jsonString = String.format("{\"message\":\"%s\"}", message);
        packet.append(getTxMessageSizeHeader(jsonString.length()));
        packet.append(jsonString);
        log.info("Message to browser: {}", packet);
        System.out.print(packet);
    }

    private int getRxMessageSize() throws IOException {
        int messageSize = 0;
        for (int curByte = 0; curByte < MESSAGE_SIZE_BYTE_COUNT; curByte++) {
            int byteValue = bufferedReader.read();
            if (byteValue == EOF_SYMBOL) {
                throw new IOException("RX message size uses less bytes than expected");
            }
            messageSize += byteValue << (BITS_COUNT_IN_BYTE * curByte);
        }
        return messageSize;
    }

    private char[] getTxMessageSizeHeader(long messageSize) throws Exception {
        if (messageSize < 0) {
            throw new Exception("TX message size can't be negative");
        }
        char[] messageSizeHeader = new char[MESSAGE_SIZE_BYTE_COUNT];
        for (int curByte = 0; curByte < MESSAGE_SIZE_BYTE_COUNT; curByte++) {
            messageSizeHeader[curByte] = (char) (messageSize & MAX_BYTE_VALUE);
            messageSize >>= BITS_COUNT_IN_BYTE;
        }
        return messageSizeHeader;
    }
}
