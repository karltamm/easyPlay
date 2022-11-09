#include <stdbool.h>
#include <string.h>
#include <usbd_cdc_if.h>

#include <buttons.h>
#include <usb_comm.h>

/* GLOBAL VARIABLES */
extern uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];  // In a file usbd_cdc_if.c

static uint32_t g_USB_RX_msg_size = 0;
static Msg g_USB_RX_msgs[USB_RX_QUEUE_MAX_SIZE];
static Queue g_USB_RX_queue;

static Msg g_USB_TX_msgs[USB_TX_QUEUE_MAX_SIZE];
static Queue g_USB_TX_queue;

/* PRIVATE FUNCTION PROTOTYPES */
static bool is_RX_msg_about_btns_LED(const char* RX_msg);
static uint8_t send_USB_msg(const char* msg);

/* PUBLIC FUNCTIONS */
void notify_about_USB_RX_msg(uint32_t* msg_size) {
  g_USB_RX_msg_size = *msg_size;
}

void init_USB_queues() {
  init_queue(&g_USB_RX_queue, USB_RX_QUEUE_MAX_SIZE, g_USB_RX_msgs);
  init_queue(&g_USB_TX_queue, USB_TX_QUEUE_MAX_SIZE, g_USB_TX_msgs);
}

USB_QueueStatus add_USB_RX_msg_to_queue() {
  if (g_USB_RX_msg_size == 0) {
    return USB_QUEUE_FAIL;
  }

  Msg* msg_slot = get_queue_empty_slot(&g_USB_RX_queue);

  if (msg_slot == NULL || g_USB_RX_msg_size > MSG_MAX_SIZE) {
    g_USB_RX_msg_size = 0;
    return USB_QUEUE_FAIL;
  }

  memcpy(msg_slot->data, UserRxBufferFS, g_USB_RX_msg_size);
  g_USB_RX_msg_size = 0;

  return USB_QUEUE_OK;
}

USB_QueueStatus add_USB_TX_msg_to_queue(Msg* msg) {
  Msg* msg_slot = get_queue_empty_slot(&g_USB_TX_queue);
  if (msg_slot == NULL) {
    return USB_QUEUE_FAIL;
  }

  // Not checking input message length, because messages are hard coded.
  // It is assumed that those messages follow length limits.

  *msg_slot = *msg;

  return USB_QUEUE_OK;
}

void process_USB_RX_queue() {
  Msg* RX_msg;
  while (g_USB_RX_queue.cur_size > 0) {
    RX_msg = get_msg_from_queue(&g_USB_RX_queue);
    if (!RX_msg) {
      return;
    }

    if (strcmp(RX_msg->data, USB_MSG_HANDSHAKE_IN) == 0) {
      send_USB_msg(USB_MSG_HANDSHAKE_OUT);
    } else if (is_RX_msg_about_btns_LED(RX_msg->data)) {
      handle_btns_LED_state(RX_msg->data);
    }
  }
}

void process_USB_TX_queue() {
  Msg* TX_msg;
  while (g_USB_TX_queue.cur_size > 0) {
    TX_msg = get_msg_from_queue(&g_USB_RX_queue);
    if (!TX_msg) {
      return;
    }

    uint32_t start_time_ms = HAL_GetTick();
    while (send_USB_msg(TX_msg->data) != USBD_OK) {
      if (HAL_GetTick() - start_time_ms > USB_TX_TIMEOUT_MS) {
        break;
      }
    }
  }
}

/* PRIVATE FUNCTIONS */
static bool is_RX_msg_about_btns_LED(const char* RX_msg) {
  if (strlen(RX_msg) != USB_MSG_BTN_LED_LEN) {
    return false;
  }

  for (uint8_t i = 0; i < USB_MSG_BTN_LED_OFFSET; i++) {
    if (RX_msg[i] != USB_MSG_BTN_LED_START[i]) {
      return false;
    }
  }

  return true;
}

static uint8_t send_USB_msg(const char* msg) {
  uint8_t msg_size = strlen(msg) + 1;  // + 1 because '\0'
  return CDC_Transmit_FS((uint8_t*)msg, msg_size);
}