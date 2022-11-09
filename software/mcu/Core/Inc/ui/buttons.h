#include <stdint.h>

#ifndef BUTTONS_H
#define BUTTONS_H

#if __cplusplus
extern "C" {
#endif

/* PUBLIC FUNCTIONS */
void handle_btn_presses();
void handle_btns_LED_state();

#if __cplusplus
}
#endif
#endif