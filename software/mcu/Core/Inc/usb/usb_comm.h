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

#define USB_MSG_BTN_A_PRESS "BTN_A_PRESS"
#define USB_MSG_BTN_B_PRESS "BTN_B_PRESS"
#define USB_MSG_BTN_C_PRESS "BTN_C_PRESS"
#define USB_MSG_BTN_D_PRESS "BTN_D_PRESS"

#define USB_MSG_BTN_LED_START "BTN_LED_"
#define USB_MSG_BTN_LED_OFFSET 8  // strlen("BTN_LED_") = 8
#define USB_MSG_BTN_LED_LEN 12    // strlen("BTN_LED_xxxx") = 12

#define USB_MSG_KNOB_CW "KNOB_CW"    // ClockWise
#define USB_MSG_KNOB_CCW "KNOB_CCW"  // CounterClockWise
#define USB_MSG_KNOB_PRESS "KNOB_PRESS"

#define USB_MSG_HEARTBEAT "EP_HEARTBEAT"

#define USB_CONN_TIMEOUT_MS 3000
#define USB_TX_TIMEOUT_MS 1

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
void check_usb_conn();

#if __cplusplus
}
#endif
#endif