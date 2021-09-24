#ifndef __S5P6818_REG_GPIO_H__
#define __S5P6818_REG_GPIO_H__

#define S5P6818_GPIOA_BASE				(0xC001A000)
#define S5P6818_GPIOB_BASE				(0xC001B000)
#define S5P6818_GPIOC_BASE				(0xC001C000)
#define S5P6818_GPIOD_BASE				(0xC001D000)
#define S5P6818_GPIOE_BASE				(0xC001E000)

#define GPIO_OUT						(0x00)
#define GPIO_OUTENB						(0x04)
#define GPIO_DETMODE0					(0x08)
#define GPIO_DETMODE1					(0x0C)
#define GPIO_INTENB						(0x10)
#define GPIO_DET						(0x14)
#define GPIO_PAD						(0x18)
#define GPIO_ALTFN0						(0x20)
#define GPIO_ALTFN1						(0x24)
#define GPIO_DETMODEEX					(0x28)
#define GPIO_DETENB						(0x3C)
#define GPIO_SLEW						(0x40)
#define GPIO_SLEW_DISABLE_DEFAULT		(0x44)
#define GPIO_DRV1						(0x48)
#define GPIO_DRV1_DISABLE_DEFAULT		(0x4C)
#define GPIO_DRV0						(0x50)
#define GPIO_DRV0_DISABLE_DEFAULT		(0x54)
#define GPIO_PULLSEL					(0x58)
#define GPIO_PULLSEL_DISABLE_DEFAULT	(0x5C)
#define GPIO_PULLENB					(0x60)
#define GPIO_PULLENB_DISABLE_DEFAULT	(0x64)

#endif /* __S5P6818_REG_GPIO_H__ */
