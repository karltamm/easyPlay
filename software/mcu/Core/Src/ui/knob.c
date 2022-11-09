#include <main.h>

#include <flags.h>
#include <knob.h>
#include <ui_master.h>
#include <usb_comm.h>

/* GLOBAL VARIABLES */
extern uint8_t g_knob_flag_group;

/* PUBLIC FUNCTIONS */
void handle_knob_actions() {
  if (g_knob_flag_group == 0) {
    /* User hasn't recently used knob */
    return;
  }

  if (is_flag_up(g_knob_flag_group, KNOB_BTN_FLAG)) {
    send_user_action_to_PC(USB_MSG_KNOB_PRESS, USB_MSG_KNOB_PRESS_SIZE);
  } else if (is_flag_up(g_knob_flag_group, KNOB_CW_FLAG)) {
    send_user_action_to_PC(USB_MSG_KNOB_CW, USB_MSG_KNOB_CW_SIZE);
  } else if (is_flag_up(g_knob_flag_group, KNOB_CCW_FLAG)) {
    send_user_action_to_PC(USB_MSG_KNOB_CCW, USB_MSG_KNOB_CCW_SIZE);
  }
}
