#include <main.h>
#include <string.h>

#include <flags.h>
#include <ui_master.h>

/* GLOBAL VARIABLES */
uint8_t g_btn_press_flag_group = 0;
uint8_t g_knob_flag_group = 0;

/* HAL */
void HAL_GPIO_EXTI_Callback(uint16_t input_pin) {
  switch (input_pin) {
    case BTN_A_Pin:
      set_flag(g_btn_press_flag_group, BTN_A_FLAG);
      break;

    case BTN_B_Pin:
      set_flag(g_btn_press_flag_group, BTN_B_FLAG);
      break;

    case BTN_C_Pin:
      set_flag(g_btn_press_flag_group, BTN_C_FLAG);
      break;

    case BTN_D_Pin:
      set_flag(g_btn_press_flag_group, BTN_D_FLAG);
      break;

    case KNOB_CH_A_Pin:
      /* Knob channel A is pulled up by default.
       * Channel A interrupt is triggered on falling edge.
       * If channel A drops (falling edge) and channel B is still high,
       * then knob is rotated clockwise (CW).
       */
      if (HAL_GPIO_ReadPin(KNOB_CH_B_GPIO_Port, KNOB_CH_B_Pin) == 1) {
        set_flag(g_knob_flag_group, KNOB_CW_FLAG);
      }
      break;

    case KNOB_CH_B_Pin:
      /* Knob channel B is pulled up by default.
       * Channel B interrupt is triggered on falling edge.
       * If channel B drops (falling edge) and channel A is still high,
       * then knob is rotated counterclockwise (CCW).
       */
      if (HAL_GPIO_ReadPin(KNOB_CH_A_GPIO_Port, KNOB_CH_A_Pin) == 1) {
        set_flag(g_knob_flag_group, KNOB_CCW_FLAG);
      }
      break;

    case KNOB_BTN_Pin:
      set_flag(g_knob_flag_group, KNOB_BTN_FLAG);
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