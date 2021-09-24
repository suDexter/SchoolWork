#ifndef __S5P6818_CLK_H__
#define __S5P6818_CLK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <s5p6818-rstcon.h>
#include <s5p6818/reg-sys.h>
#include <s5p6818/reg-clk.h>
#include <s5p6818/reg-timer.h>
#include <s5p6818/reg-pwm.h>
#include <clk/clk.h>

void s5p6818_clk_init(void);
void s5p6818_clk_exit(void);

#ifdef __cplusplus
}
#endif

#endif /* __S5P6818_CLK_H__ */
