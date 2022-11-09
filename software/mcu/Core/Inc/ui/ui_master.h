#include <stdint.h>
#include <usb_comm.h>

#ifndef UI_MASTER_H
#define UI_MASTER_H

#if __cplusplus
extern "C" {
#endif

// TODO: replace "switch" with "sw"

/* ENUMS */
enum SwitchFlags {
  SWITCH_A_FLAG = 1,
  SWITCH_B_FLAG = 2,
  SWITCH_C_FLAG = 4,
  SWITCH_D_FLAG = 8
};

/* PUBLIC FUNCTIONS */
USB_QueueStatus send_user_action_to_PC(const char* action_msg,
                                       uint8_t msg_size);

#if __cplusplus
}
#endif
#endif