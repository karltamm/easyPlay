#include <main.h>

#include <buttons.h>
#include <flags.h>
#include <ui_master.h>

/* GLOBAL VARIABLES */
extern DebounceData g_sws_debounce_data[SWS_COUNT];

/* PRIVATE FUNCTION PROTOTYPES */
static uint8_t get_LED_state_from_msg(const char* LEDs_state_msg,
                                      uint8_t LED_index);

/* PUBLIC FUNCTIONS */
void handle_btn_presses() {
  uint8_t btn_A_state = HAL_GPIO_ReadPin(BTN_A_GPIO_Port, BTN_A_Pin);
  uint8_t btn_B_state = HAL_GPIO_ReadPin(BTN_B_GPIO_Port, BTN_B_Pin);
  uint8_t btn_C_state = HAL_GPIO_ReadPin(BTN_C_GPIO_Port, BTN_C_Pin);
  uint8_t btn_D_state = HAL_GPIO_ReadPin(BTN_D_GPIO_Port, BTN_D_Pin);

  if (sw_was_used(&g_sws_debounce_data[BTN_A_ID], btn_A_state)) {
    send_user_action_to_PC(USB_MSG_BTN_A_PRESS);
  } else if (sw_was_used(&g_sws_debounce_data[BTN_B_ID], btn_B_state)) {
    send_user_action_to_PC(USB_MSG_BTN_B_PRESS);
  } else if (sw_was_used(&g_sws_debounce_data[BTN_C_ID], btn_C_state)) {
    send_user_action_to_PC(USB_MSG_BTN_C_PRESS);
  } else if (sw_was_used(&g_sws_debounce_data[BTN_D_ID], btn_D_state)) {
    send_user_action_to_PC(USB_MSG_BTN_D_PRESS);
  }
}

void handle_btns_LED_state(const char* LEDs_state_msg) {
  /*
   * This function can control every LEDs state with one message.
   * Example message:
   * LEDs_state_msg = "BTN_LED_1001" =>
   * => A =  1; B =   0; C =   0; D =  1 =>
   * => A = ON; B = OFF; C = OFF; D = ON
   */

  uint8_t LED_A_state = get_LED_state_from_msg(LEDs_state_msg, 0);
  uint8_t LED_B_state = get_LED_state_from_msg(LEDs_state_msg, 1);
  uint8_t LED_C_state = get_LED_state_from_msg(LEDs_state_msg, 2);
  uint8_t LED_D_state = get_LED_state_from_msg(LEDs_state_msg, 3);

  HAL_GPIO_WritePin(BTN_A_LED_GPIO_Port, BTN_A_LED_Pin, LED_A_state);
  HAL_GPIO_WritePin(BTN_B_LED_GPIO_Port, BTN_B_LED_Pin, LED_B_state);
  HAL_GPIO_WritePin(BTN_C_LED_GPIO_Port, BTN_C_LED_Pin, LED_C_state);
  HAL_GPIO_WritePin(BTN_D_LED_GPIO_Port, BTN_D_LED_Pin, LED_D_state);
}

void toggle_all_btns_LEDs() {
  HAL_GPIO_TogglePin(BTN_A_LED_GPIO_Port, BTN_A_LED_Pin);
  HAL_GPIO_TogglePin(BTN_B_LED_GPIO_Port, BTN_B_LED_Pin);
  HAL_GPIO_TogglePin(BTN_C_LED_GPIO_Port, BTN_C_LED_Pin);
  HAL_GPIO_TogglePin(BTN_D_LED_GPIO_Port, BTN_D_LED_Pin);
}

void turn_off_all_btns_LEDs() {
  HAL_GPIO_WritePin(BTN_A_LED_GPIO_Port, BTN_A_LED_Pin, 0);
  HAL_GPIO_WritePin(BTN_B_LED_GPIO_Port, BTN_B_LED_Pin, 0);
  HAL_GPIO_WritePin(BTN_C_LED_GPIO_Port, BTN_C_LED_Pin, 0);
  HAL_GPIO_WritePin(BTN_D_LED_GPIO_Port, BTN_D_LED_Pin, 0);
}

/* PRIVATE FUNCTIONS */
static uint8_t get_LED_state_from_msg(const char* LEDs_state_msg,
                                      uint8_t LED_index) {
  /* LED indexes:
   * A = 0
   * B = 1
   * etc
   */
  char LED_state = LEDs_state_msg[USB_MSG_BTN_LED_OFFSET + LED_index];
  return LED_state == '1' ? 1 : 0;
}
