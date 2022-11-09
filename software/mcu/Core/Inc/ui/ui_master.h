#include <stdint.h>
#include <usb_comm.h>

#ifndef UI_MASTER_H
#define UI_MASTER_H

#if __cplusplus
extern "C" {
#endif

/* ENUMS */
enum BtnFlags {
  BTN_A_FLAG = 1,
  BTN_B_FLAG = 2,
  BTN_C_FLAG = 4,
  BTN_D_FLAG = 8
};

enum KnobFlags { KNOB_CW_FLAG = 1, KNOB_CCW_FLAG = 2, KNOB_BTN_FLAG = 4 };

/* PUBLIC FUNCTIONS */
USB_QueueStatus send_user_action_to_PC(const char* action_msg);

#if __cplusplus
}
#endif
#endif