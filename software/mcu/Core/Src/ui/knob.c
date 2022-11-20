#include <main.h>

#include <flags.h>
#include <knob.h>
#include <ui_master.h>
#include <usb_comm.h>

/* GLOBAL VARIABLES */
extern DebounceData g_sws_debounce_data[SWS_COUNT];

/* PUBLIC FUNCTIONS */
void handle_knob_actions() {
  uint8_t knob_ch_A_state =
      HAL_GPIO_ReadPin(KNOB_CH_A_GPIO_Port, KNOB_CH_A_Pin);
  uint8_t knob_ch_B_state =
      HAL_GPIO_ReadPin(KNOB_CH_B_GPIO_Port, KNOB_CH_B_Pin);
  uint8_t knob_btn_state = HAL_GPIO_ReadPin(KNOB_BTN_GPIO_Port, KNOB_BTN_Pin);

  if (sw_was_used(&g_sws_debounce_data[KNOB_CH_A_ID], knob_ch_A_state)) {
    /* Knob channel A is pulled up by default.
     * Channel A interrupt is triggered on falling edge.
     * If channel A drops (falling edge) and channel B is still high,
     * then knob is rotated clockwise (CW).
     */
    if (HAL_GPIO_ReadPin(KNOB_CH_B_GPIO_Port, KNOB_CH_B_Pin) == 1) {
      send_user_action_to_PC(USB_MSG_KNOB_CW);
    }
  } else if (sw_was_used(&g_sws_debounce_data[KNOB_CH_B_ID], knob_ch_B_state)) {
    /* Knob channel B is pulled up by default.
     * Channel B interrupt is triggered on falling edge.
     * If channel B drops (falling edge) and channel A is still high,
     * then knob is rotated counterclockwise (CCW).
     */
    if (HAL_GPIO_ReadPin(KNOB_CH_A_GPIO_Port, KNOB_CH_A_Pin) == 1) {
      send_user_action_to_PC(USB_MSG_KNOB_CCW);
    }
  } else if (sw_was_used(&g_sws_debounce_data[KNOB_BTN_ID], knob_btn_state)) {
    send_user_action_to_PC(USB_MSG_KNOB_PRESS);
  }
}
