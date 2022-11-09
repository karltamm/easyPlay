#include <flags.h>
#include <switches.h>
#include <ui_master.h>

/* GLOBAL VARIABLES */
extern uint8_t g_active_sw_flag_group;

/* PUBLIC FUNCTIONS */
void handle_switch_press() {
  if (!g_active_sw_flag_group) {
    /* No switch presses to deal with */
    return;
  }

  if (is_flag_up(g_active_sw_flag_group, SWITCH_A_FLAG)) {
    send_user_action_to_PC(USB_MSG_SWITCH_A_PRESS, USB_MSG_SWITCH_PRESS_SIZE);
  }

  if (is_flag_up(g_active_sw_flag_group, SWITCH_B_FLAG)) {
    send_user_action_to_PC(USB_MSG_SWITCH_B_PRESS, USB_MSG_SWITCH_PRESS_SIZE);
  }

  if (is_flag_up(g_active_sw_flag_group, SWITCH_C_FLAG)) {
    send_user_action_to_PC(USB_MSG_SWITCH_C_PRESS, USB_MSG_SWITCH_PRESS_SIZE);
  }

  if (is_flag_up(g_active_sw_flag_group, SWITCH_D_FLAG)) {
    send_user_action_to_PC(USB_MSG_SWITCH_D_PRESS, USB_MSG_SWITCH_PRESS_SIZE);
  }
}
