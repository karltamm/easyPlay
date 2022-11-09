#include <stdint.h>

#include <queue.h>

#ifndef USB_COMM_H
#define USB_COMM_H

#if __cplusplus
extern "C" {
#endif

/* CONSTANTS */
#define USB_RX_QUEUE_MAX_SIZE 5
#define USB_TX_QUEUE_MAX_SIZE 10

#define USB_MSG_SWITCH_A_PRESS "SW_A_PRESS"
#define USB_MSG_SWITCH_B_PRESS "SW_B_PRESS"
#define USB_MSG_SWITCH_C_PRESS "SW_C_PRESS"
#define USB_MSG_SWITCH_D_PRESS "SW_D_PRESS"
#define USB_MSG_SWITCH_PRESS_SIZE 11

#define USB_MSG_KNOB_LEFT "KNOB_LEFT"
#define USB_MSG_KNOB_RIGHT "KNOB_RIGHT"

#define USB_MSG_SWITCH_A_LED_ON "SW_A_LED_ON"  // Turn on switch A LED
#define USB_MSG_SWITCH_B_LED_ON "SW_B_LED_ON"  // Turn on switch B LED
#define USB_MSG_SWITCH_C_LED_ON "SW_C_LED_ON"  // Turn on switch C LED
#define USB_MSG_SWITCH_D_LED_ON "SW_D_LED_ON"  // Turn on switch D LED

#define USB_MSG_HANDSHAKE_IN "EP_MARCO"
#define USB_MSG_HANDSHAKE_OUT (uint8_t*)"EP_POLO"
#define USB_MSG_HANDSHAKE_OUT_SIZE 8

/* TYPEDEFS */
typedef uint8_t USB_QueueStatus;

/* ENUMS */
enum { USB_QUEUE_OK, USB_QUEUE_FAIL };

/* PUBLIC FUNCTIONS */
void notify_about_USB_RX_msg(uint32_t* msg_size);
void init_USB_queues();
USB_QueueStatus add_USB_RX_msg_to_queue();
USB_QueueStatus add_USB_TX_msg_to_queue(Msg* msg);
void process_USB_RX_queue();
void process_USB_TX_queue();

#if __cplusplus
}
#endif
#endif