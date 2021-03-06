#ifndef __HW_KEY_H__
#define __HW_KEY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

enum {
	KEY_NAME_MENU	= 0x1 << 0,
	KEY_NAME_UP		= 0x1 << 1,
	KEY_NAME_DOWN	= 0x1 << 2,
	KEY_NAME_ENTER	= 0x1 << 3,
};

void key_initial(void);
bool_t get_key_status(u32_t * key);
bool_t get_key_event(u32_t * keyup, u32_t * keydown);

#ifdef __cplusplus
}
#endif

#endif /* __HW_KEY_H__ */
