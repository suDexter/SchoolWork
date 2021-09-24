/*
 * s5p6818-pwm.c
 *

 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <s5p6818-pwm.h>

#define NS_IN_SEC 1000000000UL

#define PRESCALER_0     (8 - 1)     /* prescaler of timer 0, 1 */
#define PRESCALER_1     (16 - 1)    /* prescaler of timer 2, 3, 4 */

#define MUX_DIV_SHIFT(x)    (x * 4)
#define TCON_OFFSET(x)      ((x + 1) * (!!x) << 2)
#define TCON_START(x)       (1 << TCON_OFFSET(x))
#define TCON_UPDATE(x)      (1 << (TCON_OFFSET(x) + 1))
#define TCON_AUTO_RELOAD(x) (1 << (TCON_OFFSET(x) + 3))
#define TCON4_AUTO_RELOAD   (1 << 22)
#define TCON_INVERTER(x)    (1 << (TCON_OFFSET(x) + 2))

void s5p6818_pwm_enable()
{
	unsigned int tcon;

	tcon = read32(S5P6818_PWM_TCON);
	tcon |= TCON_START(2);
	write32(S5P6818_PWM_TCON, tcon);
}

void s5p6818_pwm_disable()
{
	u32_t tcon;

	tcon = read32(S5P6818_PWM_TCON);
	tcon &= ~TCON_START(2);

	write32(S5P6818_PWM_TCON, tcon);
}

unsigned long pwm_calc_tin(int pwm_id, unsigned long freq)
{
	unsigned long tin_parent_rate = 200000000;

	unsigned int div, val, pre_div;

	write32(S5P6818_PWM_TCFG0, 0);
	val = read32(S5P6818_PWM_TCFG0);

	if (pwm_id < 2)
		div = ((val >> 0) & 0xff) + 1;
	else
		div = ((val >> 8) & 0xff) + 1;


	write32(S5P6818_PWM_TCFG1, 0);
	val = read32(S5P6818_PWM_TCFG1);
	val = (val >> MUX_DIV_SHIFT(pwm_id)) & 0xF;
	pre_div = (1UL << val);

	freq = tin_parent_rate / div / pre_div;

	return freq;
}

int pwm_config_u(int pwm_id, int duty_ns, int period_ns)
{
    unsigned int offset;
    unsigned long tin_rate;
    unsigned long tin_ns;
    unsigned long frequency;
    unsigned long tcon;
    unsigned long tcnt;
    unsigned long tcmp;

    /*
     * We currently avoid using 64bit arithmetic by using the
     * fact that anything faster than 1GHz is easily representable
     * by 32bits.
     */

    frequency = NS_IN_SEC / period_ns;

    /* Check to see if we are changing the clock rate of the PWM */
    tin_rate = pwm_calc_tin(pwm_id, frequency);

    tin_ns = NS_IN_SEC / tin_rate;
    /* The counter starts at zero. */
    tcnt = (period_ns / tin_ns)-1;

    /* Note, counters count down */
    tcmp = duty_ns / tin_ns;
    tcmp = tcnt - tcmp;

    /* Update the PWM register block. */
    offset = pwm_id * 3;
    if (pwm_id < 4) {
    	// write32(S5P6818_PWM_TCNTB0 + offset, tcnt);
    	// write32(S5P6818_PWM_TCMPB0 + offset, tcmp);
    	write32(S5P6818_PWM2_BASE + PWM_TCNTB, tcnt);
    	write32(S5P6818_PWM2_BASE + PWM_TCMPB, tcmp);
    }

    tcon = read32(S5P6818_PWM_TCON);
    tcon |= TCON_UPDATE(pwm_id);
    if (pwm_id < 4)
        tcon |= TCON_AUTO_RELOAD(pwm_id);
    else
        tcon |= TCON4_AUTO_RELOAD;
    write32(S5P6818_PWM_TCON, tcon);

    tcon &= ~TCON_UPDATE(pwm_id);
    write32(S5P6818_PWM_TCON, tcon);

    return 0;
}

int pwm_init(int pwm_id, int div, int invert)
{
	unsigned int val;
    unsigned long ticks_per_period;
    unsigned int offset, prescaler;

    /*
     * Timer Freq(HZ) =
     *  PWM_CLK / { (prescaler_value + 1) * (divider_value) }
     */
    val = read32(S5P6818_PWM_TCFG0);
    if (pwm_id < 2) {
        prescaler = PRESCALER_0;
        val &= ~0xff;
        val |= (prescaler & 0xff);
    } else {
        prescaler = PRESCALER_1;
        val &= ~(0xff << 8);
        val |= (prescaler & 0xff) << 8;
    }
    write32(S5P6818_PWM_TCFG0, val);

    val = read32(S5P6818_PWM_TCFG1);
    val &= ~(0xf << MUX_DIV_SHIFT(pwm_id));
    val |= (div & 0xf) << MUX_DIV_SHIFT(pwm_id);
    write32(S5P6818_PWM_TCFG1, val);

    if (pwm_id == 4) {
        /*
         * TODO(sjg): Use this as a countdown timer for now. We count
         * down from the maximum value to 0, then reset.
         */
        ticks_per_period = -1UL;
    } else {
        const unsigned long pwm_hz = 1000;

        unsigned long timer_rate_hz = 12500000;

        ticks_per_period = timer_rate_hz / pwm_hz;
    }

    /* set count value */
    offset = pwm_id * 3;

    // write32(ticks_per_period, S5P6818_PWM_TCNTB0 + offset);
    write32(ticks_per_period, S5P6818_PWM2_BASE + PWM_TCNTB);

    val = read32(S5P6818_PWM_TCON) & ~(0xf << TCON_OFFSET(pwm_id));
    if (invert && (pwm_id < 4))
        val |= TCON_INVERTER(pwm_id);
    write32(S5P6818_PWM_TCON, val);

    s5p6818_pwm_enable();

    return 0;
}

#define 	GPIOCALTFN0	(*(volatile unsigned int*)0xC001C020)

void s5p6818_pwm_init(void)
{
	unsigned int reg = 0;

	s5p6818_ip_reset(RESET_ID_PWM, 0);
	s5p6818_ip_reset(RESET_ID_TIMER, 0);

	reg = GPIOCALTFN0;
	reg &= ~(0x3 << 28);
	reg |= (0x2 << 28);
	GPIOCALTFN0 = reg;

}

