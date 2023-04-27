#include <main.h>
#include <string.h>

#include <flags.h>
#include <ui_master.h>

/* GLOBAL VARIABLES */
DebounceData g_sws_debounce_data[SWS_COUNT];

/* PRIVATE FUNCTION PROTOTYPES */
static void init_debounce_data(DebounceData* data,
                               uint8_t min_stable_period_ms);
static void debounce_sw(DebounceData* data, uint8_t sw_val);

/* PUBLIC FUNCTIONS */
void init_sws_debounce_data() {
  /* Keyboard switches */
  init_debounce_data(&g_sws_debounce_data[BTN_A_ID], BTN_MIN_STABLE_PERIOD_MS);
  init_debounce_data(&g_sws_debounce_data[BTN_B_ID], BTN_MIN_STABLE_PERIOD_MS);
  init_debounce_data(&g_sws_debounce_data[BTN_C_ID], BTN_MIN_STABLE_PERIOD_MS);
  init_debounce_data(&g_sws_debounce_data[BTN_D_ID], BTN_MIN_STABLE_PERIOD_MS);

  /* Knob */
  init_debounce_data(&g_sws_debounce_data[KNOB_CH_A_ID],
                     KNOB_MIN_STABLE_PERIOD_MS);
  init_debounce_data(&g_sws_debounce_data[KNOB_CH_B_ID],
                     KNOB_MIN_STABLE_PERIOD_MS);
  init_debounce_data(&g_sws_debounce_data[KNOB_BTN_ID],
                     BTN_MIN_STABLE_PERIOD_MS);
}

USB_QueueStatus send_user_action_to_PC(const char* action_msg) {
  Msg msg;
  uint8_t msg_size = strlen(action_msg) + 1;  // + 1 because '\0'
  memcpy(msg.data, action_msg, msg_size);
  return add_USB_TX_msg_to_queue(&msg);
}

bool sw_was_used(DebounceData* data, uint8_t sw_val) {
  /* This function must be called every 1 ms to handle debounce correctly */
  if (data->debounce_happening) {
    debounce_sw(data, sw_val);
    return false;
  }

  if (sw_val == SW_ON) {
    debounce_sw(data, sw_val);
  }

  return sw_val == SW_ON;
}

/* PRIVATE FUNCTIONS */
static void init_debounce_data(DebounceData* data,
                               uint8_t min_stable_period_ms) {
  data->debounce_happening = false;
  data->sw_last_state = SW_OFF;
  data->min_stable_period_ms = min_stable_period_ms;
  data->sw_state_change_time_ms = 0;
}

static void debounce_sw(DebounceData* data, uint8_t sw_val) {
  data->debounce_happening = true;

  uint32_t cur_time = HAL_GetTick();

  if (sw_val != data->sw_last_state) {
    data->sw_state_change_time_ms = cur_time;
  }

  data->sw_last_state = sw_val;

  if (sw_val == SW_ON) {
    return;
  }

  if (cur_time - data->sw_state_change_time_ms < data->min_stable_period_ms) {
    return;
  }

  data->debounce_happening = false;
}