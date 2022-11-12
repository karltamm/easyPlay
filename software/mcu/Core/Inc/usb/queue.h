#include <stdbool.h>
#include <stdint.h>

#ifndef QUEUE_H
#define QUEUE_H

#if __cplusplus
extern "C" {
#endif

/* CONFIGURATION */
#define OVERWRITE_QUEUE false

/* CONSTANTS */
#define MSG_MAX_SIZE 15  // Num of bytes message can contain

/* STRUCTS */
typedef struct Msg {
  char data[MSG_MAX_SIZE];
} Msg;

typedef struct Queue {
  /* Circular queue */
  uint8_t max_size;  // How many message can be stored
  uint8_t cur_size;  // How many message are currently stored
  uint8_t out;       // From which slot to take a message
  uint8_t in;        // To which slot to put a new message
  Msg* messages;
} Queue;

/* PUBLIC FUNCTIONS */
void init_queue(Queue* queue, uint8_t max_size, Msg* messages);
Msg* get_queue_input_slot(Queue* queue);
Msg* get_queue_output_slot(Queue* queue);

#if __cplusplus
}
#endif
#endif