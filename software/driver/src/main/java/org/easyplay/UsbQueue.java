package org.easyplay;

import lombok.extern.slf4j.Slf4j;

import java.util.Objects;
import java.util.concurrent.ConcurrentLinkedQueue;

@Slf4j
public class UsbQueue {
    private final int maxSize;
    private final ConcurrentLinkedQueue<String> queue = new ConcurrentLinkedQueue<>();
    private final String queueName;

    public UsbQueue(int maxSize, String queueName) {
        this.maxSize = maxSize;
        this.queueName = queueName;
    }

    public boolean addMsg(String msg) {
        if (Objects.isNull(msg)) {
            log.warn("Can't add empty message to {}", queueName);
            return false;
        }
        if (queue.size() > maxSize) {
            log.warn("{} max size is reached. Can't add message: {}", queueName, msg);
            return false;
        }
        queue.add(msg);
        return true;
    }

    public int size() {
        return queue.size();
    }

    public String popMsg() {
        return queue.poll();
    }
}
