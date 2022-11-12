#include <queue.h>
#include <stddef.h>

/* PUBLIC FUNCTIONS */
void init_queue(Queue* queue, uint8_t max_size, Msg* messages) {
  queue->max_size = max_size;
  queue->cur_size = 0;
  queue->out = 0;
  queue->in = 0;
  queue->messages = messages;
}

Msg* get_queue_input_slot(Queue* queue) {
  if (queue->cur_size == queue->max_size && !OVERWRITE_QUEUE) {
    return NULL;
  }

  Msg* input_slot = queue->messages + queue->in++;
  queue->cur_size++;
  if (queue->in == queue->max_size) {
    queue->in = 0;
  }

  return input_slot;
}

Msg* get_queue_output_slot(Queue* queue) {
  if (queue->cur_size == 0) {
    return NULL;
  }

  Msg* output_slot = queue->messages + queue->out++;
  queue->cur_size--;
  if (queue->out == queue->max_size) {
    queue->out = 0;
  }

  return output_slot;
}