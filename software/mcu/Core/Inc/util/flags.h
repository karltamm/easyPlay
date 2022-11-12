#include <stdbool.h>
#include <stdint.h>

#ifndef FLAGS_H
#define FLAGS_H

#if __cplusplus
extern "C" {
#endif

/* PUBLIC FUNCTIONS */
bool is_flag_up(uint8_t* flag_group, uint8_t flag);
void set_flag(uint8_t* flag_group, uint8_t flag);

#if __cplusplus
}
#endif
#endif