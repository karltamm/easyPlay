#include <stdint.h>

#ifndef DEBUG_LEDS_H
#define DEBUG_LEDS_H

#if __cplusplus
extern "C" {
#endif

/* PUBLIC FUNCTIONS */
void toggle_heartbeat_LED();
void set_problem_LED_state(uint8_t state);

#if __cplusplus
}
#endif
#endif