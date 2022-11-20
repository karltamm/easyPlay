#include <main.h>

#include <debug_leds.h>

/* PUBLIC FUNCTIONS */
void toggle_heartbeat_LED() {
  HAL_GPIO_TogglePin(DEBUG_LED_B_GPIO_Port, DEBUG_LED_B_Pin);
}

void set_problem_LED_state(uint8_t state) {
  HAL_GPIO_WritePin(DEBUG_LED_A_GPIO_Port, DEBUG_LED_A_Pin, state);
}
