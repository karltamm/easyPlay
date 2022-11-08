#include <stdint.h>

#ifndef TASKS_H
#define TASKS_H

#if __cplusplus
extern "C" {
#endif

/* ENUMS */
enum TIMER_FLAGS {
  FLAG_1_MS = 1,
  FLAG_15_MS = 2,
  FLAG_55_MS = 4,
  FLAG_1000_MS = 8,
};

/* PUBLIC FUNCTIONS */
void run_schedule();

#if __cplusplus
}
#endif
#endif