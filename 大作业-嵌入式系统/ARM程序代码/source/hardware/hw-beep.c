/*
 * hw-beep.c

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
#include <hw-beep.h>

/*
 * Beep Pin -> S5P6818_GPIOC(14)
 */
void beep_initial(void)
{
	gpio_set_pull(S5P6818_GPIOC(14), GPIO_PULL_DOWN);
	gpio_direction_output(S5P6818_GPIOC(14), 0);
}

void beep_set_status(enum beep_status status)
{
	if(status == BEEP_STATUS_ON)
		gpio_direction_output(S5P6818_GPIOC(14), 1);
	else if(status == BEEP_STATUS_OFF)
		gpio_direction_output(S5P6818_GPIOC(14), 0);
}
