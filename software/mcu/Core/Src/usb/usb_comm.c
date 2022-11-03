#include <string.h>
#include <usbd_cdc_if.h>

#include <queue.h>
#include <usb_comm.h>

/* GLOBAL VARIABLES */
extern uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];  // In a file usbd_cdc_if.c

static uint32_t g_usb_rx_msg_size = 0;
static Msg g_usb_rx_messages[USB_RX_QUEUE_MAX_SIZE];
static Queue g_usb_rx_queue;

/* FUNCTIONS */
void notify_about_usb_rx_msg(uint32_t* msg_size) {
  g_usb_rx_msg_size = *msg_size;
}

void init_usb_rx_queue() {
  init_queue(&g_usb_rx_queue, USB_RX_QUEUE_MAX_SIZE, g_usb_rx_messages);
}

void add_usb_rx_msg_to_queue() {
  if (g_usb_rx_msg_size > 0) {
    Msg* msg_slot = get_queue_empty_slot(&g_usb_rx_queue);

    if (msg_slot == NULL || g_usb_rx_msg_size > MSG_MAX_SIZE) {
      g_usb_rx_msg_size = 0;
      return;
    }

    memcpy(msg_slot->data, UserRxBufferFS, g_usb_rx_msg_size);
    g_usb_rx_msg_size = 0;
  }
}

void process_usb_rx_queue() {
  char* rx_msg;
  while (g_usb_rx_queue.cur_size > 0) {
    rx_msg = (char*)(get_msg_from_queue(&g_usb_rx_queue)->data);

    if (strcmp(rx_msg, USB_MSG_HANDSHAKE_IN) == 0) {
      CDC_Transmit_FS(USB_MSG_HANDSHAKE_OUT, USB_MSG_HANDSHAKE_OUT_SIZE);
    }
  }
}
