#include <main.h>

#include <buttons.h>
#include <flags.h>
#include <ui_master.h>

/* GLOBAL VARIABLES */
extern uint8_t g_btn_press_flag_group;

/* PRIVATE FUNCTION PROTOTYPES */
static uint8_t get_LED_state_from_msg(const char* LEDs_state_msg,
                                      uint8_t LED_index);

/* PUBLIC FUNCTIONS */
void handle_btn_presses() {
  if (g_btn_press_flag_group == 0) {
    /* No button presses to deal with */
    return;
  }

  if (is_flag_up(g_btn_press_flag_group, BTN_A_FLAG)) {
    send_user_action_to_PC(USB_MSG_BTN_A_PRESS, USB_MSG_BTN_PRESS_SIZE);
  }

  if (is_flag_up(g_btn_press_flag_group, BTN_B_FLAG)) {
    send_user_action_to_PC(USB_MSG_BTN_B_PRESS, USB_MSG_BTN_PRESS_SIZE);
  }

  if (is_flag_up(g_btn_press_flag_group, BTN_C_FLAG)) {
    send_user_action_to_PC(USB_MSG_BTN_C_PRESS, USB_MSG_BTN_PRESS_SIZE);
  }

  if (is_flag_up(g_btn_press_flag_group, BTN_D_FLAG)) {
    send_user_action_to_PC(USB_MSG_BTN_D_PRESS, USB_MSG_BTN_PRESS_SIZE);
  }
}

void handle_btns_LED_state(const char* LEDs_state_msg) {
  /*
   * This function can control every LEDs state with one message.
   * Example message:
   * LEDs_state_msg = "LED_1001" =>
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
