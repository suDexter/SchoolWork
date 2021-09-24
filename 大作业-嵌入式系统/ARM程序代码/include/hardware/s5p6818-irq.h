#ifndef __S5P6818_IRQ_H__
#define __S5P6818_IRQ_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <cp15.h>
#include <s5p6818/reg-gpio.h>
#include <s5p6818/reg-alv.h>
#include <s5p6818/reg-gic.h>
#include <interrupt/interrupt.h>

struct pt_regs {
	unsigned long elr;
	unsigned long regs[31];
};

void s5p6818_irq_init(void);
void s5p6818_irq_exit(void);

#ifdef __cplusplus
}
#endif

#endif /* __S5P6818_IRQ_H__ */
