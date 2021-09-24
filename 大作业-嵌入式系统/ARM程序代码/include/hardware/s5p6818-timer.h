#ifndef __S5P6818_TIMER_H__
#define __S5P6818_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>
#include <types.h>
#include <string.h>
#include <io.h>
#include <stddef.h>
#include <s5p6818-rstcon.h>
#include <s5p6818-gpio.h>
#include <s5p6818-clk.h>
#include <s5p6818/reg-timer.h>

void s5p6818_timer_reset(void);
void s5p6818_timer_start(int ch, int irqon);
void s5p6818_timer_stop(int ch, int irqon);
u64_t s5p6818_timer_calc_tin(int ch, u32_t period);
void s5p6818_timer_count(int ch, u32_t cnt);
u32_t s5p6818_timer_read(int ch);
void s5p6818_timer_irq_clear(int ch);

#ifdef __cplusplus
}
#endif

#endif /* __S5P6818_TIMER_H__ */
