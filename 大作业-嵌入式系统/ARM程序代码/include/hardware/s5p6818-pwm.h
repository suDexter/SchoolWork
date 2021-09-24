#ifndef __S5P6818_PWM_H__
#define __S5P6818_PWM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <pwm/pwm.h>
#include <s5p6818-rstcon.h>
#include <s5p6818-gpio.h>
#include <s5p6818-clk.h>
#include <s5p6818/reg-pwm.h>
#include <pwm/pwm.h>

void s5p6818_pwm_init(void);
void s5p6818_pwm_exit(void);

#ifdef __cplusplus
}
#endif

#endif /* __S5P6818_PWM_H__ */
