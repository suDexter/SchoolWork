#ifndef __S5P6818_GPIO_H__
#define __S5P6818_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <s5p6818/reg-gpio.h>
#include <s5p6818/reg-alv.h>
#include <gpio/gpio.h>

#define S5P6818_GPIOA(x)		(x)
#define S5P6818_GPIOB(x)		(x + 32)
#define S5P6818_GPIOC(x)		(x + 64)
#define S5P6818_GPIOD(x)		(x + 96)
#define S5P6818_GPIOE(x)		(x + 128)
#define S5P6818_GPIOALV(x)		(x + 160)

void s5p6818_gpiochip_init(void);
void s5p6818_gpiochip_exit(void);
void s5p6818_gpiochip_alv_init(void);
void s5p6818_gpiochip_alv_exit(void);

#ifdef __cplusplus
}
#endif

#endif /* __S5P6818_GPIO_H__ */
