/*
 * hw-key.c
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
#include <stddef.h>
#include <s5p6818-gpio.h>
#include <hw-key.h>

/*
 * UP    -> S5P6818_GPIOB(16)
 * DOWN  -> S5P6818_GPIOB(8)
 */
void key_initial(void)
{
	/* UP */
	gpio_set_pull(S5P6818_GPIOB(16), GPIO_PULL_UP);
	gpio_direction_input(S5P6818_GPIOB(16));

	/* DOWN */
	gpio_set_pull(S5P6818_GPIOB(8), GPIO_PULL_UP);
	gpio_direction_input(S5P6818_GPIOB(8));

}

static u32_t __get_key_status(void)
{
	u32_t key = 0;

	if(gpio_get_value(S5P6818_GPIOB(16)) == 0)
		key |= KEY_NAME_UP;

	if(gpio_get_value(S5P6818_GPIOB(8)) == 0)
		key |= KEY_NAME_DOWN;

	return key;
}

bool_t get_key_status(u32_t * key)
{
	static u32_t a = 0, b = 0, c = 0;

	a = __get_key_status();
	b = __get_key_status();
	c = __get_key_status();

	if((a == b) && (a == c))
	{
		*key = a;
		return TRUE;
	}

	return FALSE;
}

bool_t get_key_event(u32_t * keyup, u32_t * keydown)
{
	static u32_t key_old = 0x0;
	u32_t key;

	if(!get_key_status(&key))
		return FALSE;

	if(key != key_old)
	{
		*keyup = (key ^ key_old) & key_old;
		*keydown = (key ^ key_old) & key;
		key_old = key;

		return TRUE;
	}

	return FALSE;
}
