#include <stdbool.h>
#include <stdint.h>

#include <usb_comm.h>

#ifndef UI_MASTER_H
#define UI_MASTER_H

#if __cplusplus
extern "C" {
#endif

/* CONSTANTS */
#define SWITCH_OFF 1  // Switches pulled up by default
#define SWITCH_ON 0

#define DEBOUNCE_PERIOD_MS 10

#define BTN_MIN_STABLE_PERIOD_MS 10
#define KNOB_MIN_STABLE_PERIOD_MS 5

/* STRUCTS */
typedef struct DebounceData {
  bool debounce_happening : 1;
  uint8_t switch_last_val : 1;
  uint8_t min_stable_period_ms;
  uint32_t val_change_time_ms;
} DebounceData;

/* ENUMS */
enum BtnFlags {
  BTN_A_FLAG = 1,
  BTN_B_FLAG = 2,
  BTN_C_FLAG = 4,
  BTN_D_FLAG = 8
};

enum Switches {
  BTN_A_ID,
  BTN_B_ID,
  BTN_C_ID,
  BTN_D_ID,
  KNOB_CH_A_ID,
  KNOB_CH_B_ID,
  KNOB_BTN_ID,
  SWITCHES_COUNT
};

enum KnobFlags { KNOB_CW_FLAG = 1, KNOB_CCW_FLAG = 2, KNOB_BTN_FLAG = 4 };

/* PUBLIC FUNCTIONS */
USB_QueueStatus send_user_action_to_PC(const char* action_msg);
void handle_btn_press2();

void init_switches_debounce_data();
bool switch_was_used(DebounceData* data, uint8_t switch_val);

#if __cplusplus
}
#endif
#endif