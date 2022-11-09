#include <queue.h>
#include <stddef.h>

// TODO: make sure that circular buffer can be overwritten

/* PUBLIC FUNCTIONS */
void init_queue(Queue* queue, uint8_t max_size, Msg* messages) {
  queue->max_size = max_size;
  queue->cur_size = 0;
  queue->out = 0;
  queue->in = 0;
  queue->messages = messages;
}

Msg* get_queue_empty_slot(Queue* queue) {
  if (queue->cur_size == queue->max_size) {
    return NULL;
  }

  Msg* empty_slot = queue->messages + queue->in++;
  queue->cur_size++;
  if (queue->in == queue->max_size) {
    queue->in = 0;
  }

  return empty_slot;
}

Msg* get_msg_from_queue(Queue* queue) {
  if (queue->cur_size == 0) {
    return NULL;
  }

  Msg* msg = queue->messages + queue->out++;
  queue->cur_size--;
  if (queue->out == queue->max_size) {
    queue->out = 0;
  }

  return msg;
}