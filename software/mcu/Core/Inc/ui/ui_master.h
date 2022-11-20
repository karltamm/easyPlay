#include <stdbool.h>
#include <stdint.h>

#include <usb_comm.h>

#ifndef UI_MASTER_H
#define UI_MASTER_H

#if __cplusplus
extern "C" {
#endif

/* CONSTANTS */
#define SW_OFF 1  // Switches pulled up by default
#define SW_ON 0

#define BTN_MIN_STABLE_PERIOD_MS 100
#define KNOB_MIN_STABLE_PERIOD_MS 10

/* STRUCTS */
typedef struct DebounceData {
  bool debounce_happening;
  uint8_t sw_last_state;
  uint8_t min_stable_period_ms;
  uint32_t sw_state_change_time_ms;
} DebounceData;

/* ENUMS */
enum Switches {
  BTN_A_ID,
  BTN_B_ID,
  BTN_C_ID,
  BTN_D_ID,
  KNOB_CH_A_ID,
  KNOB_CH_B_ID,
  KNOB_BTN_ID,
  SWS_COUNT
};

/* PUBLIC FUNCTIONS */
USB_QueueStatus send_user_action_to_PC(const char* action_msg);
void init_sws_debounce_data();
bool sw_was_used(DebounceData* data, uint8_t sw_val);

#if __cplusplus
}
#endif
#endif