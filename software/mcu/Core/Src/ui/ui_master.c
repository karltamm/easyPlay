#include <main.h>
#include <string.h>

#include <flags.h>
#include <ui_master.h>

/* GLOBAL VARIABLES */
uint8_t g_btn_press_flag_group = 0;
uint8_t g_knob_flag_group = 0;

DebounceData g_switches_debounce_data[SWITCHES_COUNT];

/* PRIVATE FUNCTION PROTOTYPES */
static void init_debounce_data(DebounceData* data,
                               uint8_t min_stable_period_ms);
static void debounce_switch(DebounceData* data, uint8_t switch_val);

// void handle_btn_press2() {
//   // TODO: #define IO_HIGH 1

//   static uint8_t btn_press_happening = 0;
//   static uint8_t btn_last_state = 1;
//   static uint32_t btn_state_change_time_ms = 0;

//   uint8_t btn_cur_state = HAL_GPIO_ReadPin(BTN_A_GPIO_Port, BTN_A_Pin);

//   if (!btn_press_happening && btn_cur_state == 0) {
//     set_flag(&g_btn_press_flag_group, BTN_A_FLAG);
//     btn_press_happening = 1;
//   }

//   uint32_t cur_time = HAL_GetTick();
//   if (btn_cur_state != btn_last_state) {
//     btn_state_change_time_ms = cur_time;
//   }

//   btn_last_state = btn_cur_state;

//   if (btn_cur_state != 1) {
//     return;
//   }

//   if (cur_time - btn_state_change_time_ms < 10) {
//     return;
//   }

//   btn_press_happening = 0;

//   // static uint8_t btn_a_last_state = 1;
//   // static uint32_t btn_state_change_time_ms = 0;
//   // static uint8_t btn_press_happened = 0;

//   // uint8_t btn_a_cur_state = HAL_GPIO_ReadPin(BTN_A_GPIO_Port, BTN_A_Pin);
//   // uint32_t cur_time = HAL_GetTick();

//   // if (btn_a_cur_state != btn_a_last_state) {
//   //   btn_state_change_time_ms = cur_time;
//   //   btn_press_happened = 1;
//   //   btn_a_last_state = btn_a_cur_state;
//   // }

//   // if (!btn_press_happened) {
//   //   return;
//   // }

//   // if (cur_time - btn_state_change_time_ms < 50) {
//   //   return;
//   // }

//   // btn_press_happened = 0;
//   // set_flag(&g_btn_press_flag_group, BTN_A_FLAG);

//   // static uint8_t btn_a_last_state = 1;
//   // static uint32_t btn_state_change_time_ms = 0;
//   // static uint8_t btn_press_happened = 0;

//   // uint8_t btn_a_cur_state = HAL_GPIO_ReadPin(BTN_A_GPIO_Port, BTN_A_Pin);
//   // uint32_t cur_time = HAL_GetTick();

//   // if (btn_a_cur_state != btn_a_last_state) {
//   //   btn_state_change_time_ms = cur_time;
//   //   btn_press_happened = 1;
//   //   btn_a_last_state = btn_a_cur_state;
//   // }

//   // if (!btn_press_happened) {
//   //   return;
//   // }

//   // if (cur_time - btn_state_change_time_ms < 50) {
//   //   return;
//   // }

//   // btn_press_happened = 0;
//   // set_flag(&g_btn_press_flag_group, BTN_A_FLAG);
// }

/* HAL */
void HAL_GPIO_EXTI_Callback(uint16_t input_pin) {
  /* Debounce for knob */
  static uint32_t input_start_time = 0;
  if (HAL_GetTick() - input_start_time < DEBOUNCE_PERIOD_MS) {
    return;
  }
  input_start_time = HAL_GetTick();
  // TODO: improved debounce algorithm

  switch (input_pin) {
      // case BTN_A_Pin:
      //   set_flag(&g_btn_press_flag_group, BTN_A_FLAG);
      //   break;

    case BTN_B_Pin:
      set_flag(&g_btn_press_flag_group, BTN_B_FLAG);
      break;

    case BTN_C_Pin:
      set_flag(&g_btn_press_flag_group, BTN_C_FLAG);
      break;

    case BTN_D_Pin:
      set_flag(&g_btn_press_flag_group, BTN_D_FLAG);
      break;

    case KNOB_CH_A_Pin:
      /* Knob channel A is pulled up by default.
       * Channel A interrupt is triggered on falling edge.
       * If channel A drops (falling edge) and channel B is still high,
       * then knob is rotated clockwise (CW).
       */
      if (HAL_GPIO_ReadPin(KNOB_CH_B_GPIO_Port, KNOB_CH_B_Pin) == 1) {
        set_flag(&g_knob_flag_group, KNOB_CW_FLAG);
      }
      break;

    case KNOB_CH_B_Pin:
      /* Knob channel B is pulled up by default.
       * Channel B interrupt is triggered on falling edge.
       * If channel B drops (falling edge) and channel A is still high,
       * then knob is rotated counterclockwise (CCW).
       */
      if (HAL_GPIO_ReadPin(KNOB_CH_A_GPIO_Port, KNOB_CH_A_Pin) == 1) {
        set_flag(&g_knob_flag_group, KNOB_CCW_FLAG);
      }
      break;

    case KNOB_BTN_Pin:
      set_flag(&g_knob_flag_group, KNOB_BTN_FLAG);
      break;

    default:
      break;
  }
}

/* PUBLIC FUNCTIONS */
void init_switches_debounce_data() {
  /* Keyboard switches */
  init_debounce_data(&g_switches_debounce_data[BTN_A_ID],
                     BTN_MIN_STABLE_PERIOD_MS);
  init_debounce_data(&g_switches_debounce_data[BTN_B_ID],
                     BTN_MIN_STABLE_PERIOD_MS);
  init_debounce_data(&g_switches_debounce_data[BTN_C_ID],
                     BTN_MIN_STABLE_PERIOD_MS);
  init_debounce_data(&g_switches_debounce_data[BTN_D_ID],
                     BTN_MIN_STABLE_PERIOD_MS);

  /* Knob */
  init_debounce_data(&g_switches_debounce_data[KNOB_CH_A_ID],
                     KNOB_MIN_STABLE_PERIOD_MS);
  init_debounce_data(&g_switches_debounce_data[KNOB_CH_B_ID],
                     KNOB_MIN_STABLE_PERIOD_MS);
  init_debounce_data(&g_switches_debounce_data[KNOB_BTN_ID],
                     BTN_MIN_STABLE_PERIOD_MS);
}

USB_QueueStatus send_user_action_to_PC(const char* action_msg) {
  Msg msg;
  uint8_t msg_size = strlen(action_msg) + 1;  // + 1 because '\0'
  memcpy(msg.data, action_msg, msg_size);
  return add_USB_TX_msg_to_queue(&msg);
}

bool switch_was_used(DebounceData* data, uint8_t switch_val) {
  /* This function must be called every 1 ms to handle debounce correctly */
  if (!data->debounce_happening && switch_val == SWITCH_ON) {
    debounce_switch(data, switch_val);
    return true;
  }

  if (data->debounce_happening) {
    debounce_switch(data, switch_val);
  }

  return false;
}

/* PRIVATE FUNCTIONS */
static void init_debounce_data(DebounceData* data,
                               uint8_t min_stable_period_ms) {
  data->debounce_happening = 0;
  data->switch_last_val = SWITCH_OFF;
  data->min_stable_period_ms = min_stable_period_ms;
  data->val_change_time_ms = 0;
}

static void debounce_switch(DebounceData* data, uint8_t switch_val) {
  data->debounce_happening = true;

  uint32_t cur_time = HAL_GetTick();

  if (switch_val != data->switch_last_val) {
    data->val_change_time_ms = cur_time;
  }

  data->switch_last_val = switch_val;

  if (switch_val != SWITCH_OFF) {
    return;
  }

  if (cur_time - data->val_change_time_ms < data->min_stable_period_ms) {
    return;
  }

  data->debounce_happening = false;
}