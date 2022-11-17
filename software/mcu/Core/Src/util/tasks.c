#include <main.h>

#include <buttons.h>
#include <debug_leds.h>
#include <flags.h>
#include <knob.h>
#include <tasks.h>
#include <ui_master.h>
#include <usb_comm.h>

/* GLOBAL VARIABLES */
static uint8_t g_timer_flag_group;  // Every bit represents different flag

/* HAL */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
  /* Callback is called based on the configured timer (CubeMX) every 1 ms */
  static uint16_t time_ms = 0;
  if (time_ms == 5000) {
    time_ms = 0;
  }

  set_flag(&g_timer_flag_group, FLAG_1_MS);

  if (time_ms % 15 == 0) {
    set_flag(&g_timer_flag_group, FLAG_15_MS);
  }

  if (time_ms % 55 == 0) {
    set_flag(&g_timer_flag_group, FLAG_55_MS);
  }

  if (time_ms % 1000 == 0) {
    set_flag(&g_timer_flag_group, FLAG_1000_MS);
  }

  time_ms++;
}

/* PUBLIC FUNCTIONS */
void run_schedule() {
  add_USB_RX_msg_to_queue();

  handle_knob_actions();

  if (is_flag_up(&g_timer_flag_group, FLAG_1_MS)) {
    handle_btn_presses();
    check_usb_conn();
  }

  if (is_flag_up(&g_timer_flag_group, FLAG_15_MS)) {
    process_USB_TX_queue();
  } else if (is_flag_up(&g_timer_flag_group, FLAG_55_MS)) {
    process_USB_RX_queue();
  } else if (is_flag_up(&g_timer_flag_group, FLAG_1000_MS)) {
    toggle_heartbeat_LED();
  }
}
