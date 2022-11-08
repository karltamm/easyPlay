#include <main.h>
#include <stdbool.h>

#include <tasks.h>
#include <usb_comm.h>

/* GLOBAL VARIABLES */
static uint8_t g_timer_flags;  // Every bit represents different flag

/* PRIVATE FUNCTION PROTOTYPES */
static bool is_timer_flag_up(uint8_t flag);
static void set_timer_flag(uint8_t flag);
static void clear_timer_flag(uint8_t flag);
static void blink_debug_LED();

/* FUNCTIONS */
void run_schedule() {
  add_USB_RX_msg_to_queue();

  if (is_timer_flag_up(FLAG_15_MS)) {
    process_USB_TX_queue();
  }

  if (is_timer_flag_up(FLAG_55_MS)) {
    process_USB_RX_queue();
  }

  if (is_timer_flag_up(FLAG_1000_MS)) {
    blink_debug_LED();
  }
}

/* HAL */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
  static uint16_t time_ms = 0;
  if (time_ms == 5000) {
    time_ms = 0;
  }

  set_timer_flag(FLAG_1_MS);

  if (time_ms % 15 == 0) {
    set_timer_flag(FLAG_15_MS);
  }

  if (time_ms % 55 == 0) {
    set_timer_flag(FLAG_55_MS);
  }

  if (time_ms % 1000 == 0) {
    set_timer_flag(FLAG_1000_MS);
  }

  time_ms++;
}

/* Timer flags */
static bool is_timer_flag_up(uint8_t flag) {
  if (g_timer_flags & flag) {
    clear_timer_flag(flag);
    return true;
  }

  return false;
}

static void set_timer_flag(uint8_t flag) {
  g_timer_flags |= flag;
}

static void clear_timer_flag(uint8_t flag) {
  g_timer_flags &= ~flag;
}

static void blink_debug_LED() {
  HAL_GPIO_TogglePin(DEBUG_LED_B_GPIO_Port, DEBUG_LED_B_Pin);
}
