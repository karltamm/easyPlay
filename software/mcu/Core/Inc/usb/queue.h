#include <stdint.h>

#ifndef QUEUE_H
#define QUEUE_H

#if __cplusplus
extern "C" {
#endif

/* CONSTANTS */
#define MSG_MAX_SIZE 15  // Num of bytes message can contain

/* STRUCTS */
typedef struct Msg {
  uint8_t data[MSG_MAX_SIZE];
} Msg;

typedef struct Queue {
  /* Circular FIFO queue without overwriting messages */
  uint8_t max_size;  // How many message can be stored
  uint8_t cur_size;  // How many message are currently stored
  uint8_t out;       // From which slot to take a message
  uint8_t in;        // To which slot to put a new message
  Msg* messages;
} Queue;

/* PUBLIC FUNCTIONS */
void init_queue(Queue* queue, uint8_t max_size, Msg* messages);
Msg* get_queue_empty_slot(Queue* queue);
Msg* get_msg_from_queue(Queue* queue);

#if __cplusplus
}
#endif
#endif