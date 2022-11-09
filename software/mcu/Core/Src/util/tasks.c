#include <main.h>

#include <flags.h>
#include <switches.h>
#include <tasks.h>
#include <usb_comm.h>

/* GLOBAL VARIABLES */
static uint8_t g_timer_flag_group;  // Every bit represents different flag

/* PRIVATE FUNCTION PROTOTYPES */
static void blink_debug_LED();

/* HAL */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
  /* Callback is called based on the configured timer (CubeMX) every 1 ms */
  static uint16_t time_ms = 0;
  if (time_ms == 5000) {
    time_ms = 0;
  }

  set_flag(g_timer_flag_group, FLAG_1_MS);

  if (time_ms % 15 == 0) {
    set_flag(g_timer_flag_group, FLAG_15_MS);
  }

  if (time_ms % 55 == 0) {
    set_flag(g_timer_flag_group, FLAG_55_MS);
  }

  if (time_ms % 1000 == 0) {
    set_flag(g_timer_flag_group, FLAG_1000_MS);
  }

  time_ms++;
}

/* PUBLIC FUNCTIONS */
void run_schedule() {
  add_USB_RX_msg_to_queue();
  handle_switch_press();

  if (is_flag_up(g_timer_flag_group, FLAG_15_MS)) {
    process_USB_TX_queue();
  }

  if (is_flag_up(g_timer_flag_group, FLAG_55_MS)) {
    process_USB_RX_queue();
  }

  if (is_flag_up(g_timer_flag_group, FLAG_1000_MS)) {
    blink_debug_LED();
  }
}

/* PRIVATE FUNCTIONS */
static void blink_debug_LED() {
  HAL_GPIO_TogglePin(DEBUG_LED_B_GPIO_Port, DEBUG_LED_B_Pin);
}
