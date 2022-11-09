#include <main.h>
#include <string.h>

#include <flags.h>
#include <ui_master.h>

/* GLOBAL VARIABLES */
uint8_t g_active_sw_flag_group = 0;

/* HAL */
void HAL_GPIO_EXTI_Callback(uint16_t input_pin) {
  switch (input_pin) {
    case SWITCH_A_Pin:
      set_flag(g_active_sw_flag_group, SWITCH_A_FLAG);
      break;

    case SWITCH_B_Pin:
      set_flag(g_active_sw_flag_group, SWITCH_B_FLAG);
      break;

    case SWITCH_C_Pin:
      set_flag(g_active_sw_flag_group, SWITCH_C_FLAG);
      break;

    case SWITCH_D_Pin:
      set_flag(g_active_sw_flag_group, SWITCH_D_FLAG);
      break;

    case KNOB_A_Pin:
      // TODO: handle knob A channel
      break;

    case KNOB_B_Pin:
      // TODO: handle knob B channel
      break;

    default:
      break;
  }
}

/* PUBLIC FUNCTIONS */
USB_QueueStatus send_user_action_to_PC(const char* action_msg,
                                       uint8_t msg_size) {
  Msg msg;
  memcpy(msg.data, action_msg, msg_size);
  return add_USB_TX_msg_to_queue(&msg);
}