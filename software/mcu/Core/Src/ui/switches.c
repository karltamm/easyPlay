#include <main.h>

#include <flags.h>
#include <switches.h>
#include <ui_master.h>

/* GLOBAL VARIABLES */
extern uint8_t g_switch_press_flag_group;

/* PRIVATE FUNCTION PROTOTYPES */
static uint8_t get_LED_state_from_msg(const char* LEDs_state_msg,
                                      uint8_t LED_index);

/* PUBLIC FUNCTIONS */
void handle_switch_press() {
  if (g_switch_press_flag_group == 0) {
    /* No switch presses to deal with */
    return;
  }

  if (is_flag_up(g_switch_press_flag_group, SWITCH_A_FLAG)) {
    send_user_action_to_PC(USB_MSG_SWITCH_A_PRESS, USB_MSG_SWITCH_PRESS_SIZE);
  }

  if (is_flag_up(g_switch_press_flag_group, SWITCH_B_FLAG)) {
    send_user_action_to_PC(USB_MSG_SWITCH_B_PRESS, USB_MSG_SWITCH_PRESS_SIZE);
  }

  if (is_flag_up(g_switch_press_flag_group, SWITCH_C_FLAG)) {
    send_user_action_to_PC(USB_MSG_SWITCH_C_PRESS, USB_MSG_SWITCH_PRESS_SIZE);
  }

  if (is_flag_up(g_switch_press_flag_group, SWITCH_D_FLAG)) {
    send_user_action_to_PC(USB_MSG_SWITCH_D_PRESS, USB_MSG_SWITCH_PRESS_SIZE);
  }
}

void handle_switches_LED_state(const char* LEDs_state_msg) {
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

  HAL_GPIO_WritePin(SWITCH_A_LED_GPIO_Port, SWITCH_A_LED_Pin, LED_A_state);
  HAL_GPIO_WritePin(SWITCH_B_LED_GPIO_Port, SWITCH_B_LED_Pin, LED_B_state);
  HAL_GPIO_WritePin(SWITCH_C_LED_GPIO_Port, SWITCH_C_LED_Pin, LED_C_state);
  HAL_GPIO_WritePin(SWITCH_D_LED_GPIO_Port, SWITCH_D_LED_Pin, LED_D_state);
}

/* PRIVATE FUNCTIONS */
static uint8_t get_LED_state_from_msg(const char* LEDs_state_msg,
                                      uint8_t LED_index) {
  /* LED indexes:
   * A = 0
   * B = 1
   * etc
   */
  char LED_state = LEDs_state_msg[USB_MSG_SW_LED_OFFSET + LED_index];
  return LED_state == '1' ? 1 : 0;
}
