/*
 * hw-led.c
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

#include <types.h>
#include <io.h>
#include <s5p6818-gpio.h>
#include <hw-led.h>

/*
 * LEDR -> S5P6818_GPIOA(28)
 * LEDG -> S5P6818_GPIOE(13)
 * LEDB -> S5P6818_GPIOB(12)
 */
void led_initial(void)
{
	/* LEDR */
	//gpio_set_cfg(S5P6818_GPIOA(28), 0);
	gpio_set_pull(S5P6818_GPIOA(28), GPIO_PULL_UP);
	gpio_direction_output(S5P6818_GPIOA(28), 1);

	/* LEDG */
	//gpio_set_cfg(S5P6818_GPIOE(13), 0);
	gpio_set_pull(S5P6818_GPIOE(13), GPIO_PULL_UP);
	gpio_direction_output(S5P6818_GPIOE(13), 1);

	/* LEDB */
	gpio_set_cfg(S5P6818_GPIOB(12),0x2);
	gpio_set_pull(S5P6818_GPIOB(12), GPIO_PULL_UP);
	gpio_direction_output(S5P6818_GPIOB(12), 1);

	gpio_set_cfg(S5P6818_GPIOC(2),0x1);
	gpio_set_pull(S5P6818_GPIOC(2), GPIO_PULL_UP);
	gpio_direction_output(S5P6818_GPIOC(2), 1);

}

void led_set_status(enum led_name name, enum led_status status)
{
	switch(name)
	{
	case LED_NAME_LED1:
		if(status == LED_STATUS_ON)
			gpio_direction_output(S5P6818_GPIOA(28), 1);
		else if(status == LED_STATUS_OFF)
			gpio_direction_output(S5P6818_GPIOA(28), 0);
		break;

	case LED_NAME_LED2:
		if(status == LED_STATUS_ON)
			gpio_direction_output(S5P6818_GPIOE(13), 1);
		else if(status == LED_STATUS_OFF)
			gpio_direction_output(S5P6818_GPIOE(13), 0);
		break;

	case LED_NAME_LED3:
		if(status == LED_STATUS_ON)
			gpio_direction_output(S5P6818_GPIOB(12), 1);
		else if(status == LED_STATUS_OFF)
			gpio_direction_output(S5P6818_GPIOB(12), 0);
		break;

	case LED_NAME_LED4:
		if(status == LED_STATUS_ON)
			gpio_direction_output(S5P6818_GPIOC(2), 1);
		else if(status == LED_STATUS_OFF)
			gpio_direction_output(S5P6818_GPIOC(2), 0);
		break;

	default:
		break;
	}
}
