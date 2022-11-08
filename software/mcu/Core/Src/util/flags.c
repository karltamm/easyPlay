#include <flags.h>

/* PRIVATE FUNCTION PROTOTYPES */
static void clear_flag(uint8_t flag_group, uint8_t flag);

/* FUNCTIONS */
bool is_flag_up(uint8_t flag_group, uint8_t flag) {
  if (flag_group & flag) {
    clear_flag(flag_group, flag);
    return true;
  }

  return false;
}

void set_flag(uint8_t flag_group, uint8_t flag) {
  flag_group |= flag;
}

/* PRIVATE FUNCTIONS */
static void clear_flag(uint8_t flag_group, uint8_t flag) {
  flag_group &= ~flag;
}
