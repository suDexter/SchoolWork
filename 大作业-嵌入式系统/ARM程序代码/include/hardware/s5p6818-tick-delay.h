#ifndef __S5P6818_TICK_DELAY_H__
#define __S5P6818_TICK_DELAY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>
#include <stddef.h>
#include <io.h>
#include <sizes.h>
#include <string.h>
#include <s5p6818-clk.h>
#include <s5p6818-tick.h>

void s5p6818_tick_delay_initial(void);
void udelay(u32_t us);
void mdelay(u32_t ms);

#ifdef __cplusplus
}
#endif

#endif /* __S5P6818_TICK_DELAY_H__ */
