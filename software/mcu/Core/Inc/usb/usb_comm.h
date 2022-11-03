#include <stdint.h>

#ifndef USB_COMM_H
#define USB_COMM_H

#if __cplusplus
extern "C" {
#endif

/* CONSTANTS */
#define USB_RX_QUEUE_MAX_SIZE 5
#define USB_TX_QUEUE_MAX_SIZE 10

#define USB_MSG_SWITCH_A_LED_ON "SW_A_LED_ON"  // Turn on switch A LED
#define USB_MSG_SWITCH_B_LED_ON "SW_B_LED_ON"  // Turn on switch B LED
#define USB_MSG_SWITCH_C_LED_ON "SW_C_LED_ON"  // Turn on switch C LED
#define USB_MSG_SWITCH_D_LED_ON "SW_D_LED_ON"  // Turn on switch D LED

#define USB_MSG_HANDSHAKE_IN "EP_MARCO"
#define USB_MSG_HANDSHAKE_OUT (uint8_t*)"EP_POLO"
#define USB_MSG_HANDSHAKE_OUT_SIZE 8

/* STRUCTS */

/* PUBLIC FUNCTIONS */
void notify_about_usb_rx_msg(uint32_t* msg_size);
void init_usb_rx_queue();
void add_usb_rx_msg_to_queue();
void process_usb_rx_queue();

#if __cplusplus
}
#endif
#endif