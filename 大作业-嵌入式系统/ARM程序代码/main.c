#include <main.h>
#define GPIOFA	(*(volatile unsigned int*)0xC001A020)
#define GPIOFB	(*(volatile unsigned int*)0xC001A004)
#define GPIOFC 	(*(volatile unsigned int*)0xC001A000)
#define TO_PERIOD_NS(freq)  ((1000000000UL)/(freq))
#define TO_DUTY_NS(duty, freq)  (duty ? TO_PERIOD_NS(freq)/(100/duty) : 0)
//初始化GPIO口
void Init_GPIO(){
	unsigned int reg = 0;
	//液位开关1 = 5
	reg = GPIOFA;
	reg &= ~(0x3 << 5);
	GPIOFA = reg;
	reg = GPIOFB;
	reg &= ~(0x1 << 5);
	reg |= (0x1 << 5);
	GPIOFB = reg;
	//阀1 = 1
	reg = GPIOFA;
	reg &= ~(0x3 << 1);
	GPIOFA = reg;
	reg = GPIOFB;
	reg &= ~(0x1 << 1);
	reg |= (0x1 << 1);
	GPIOFB = reg;
	//阀2 = 2
	reg = GPIOFA;
	reg &= ~(0x3 << 2);
	GPIOFA = reg;
	reg = GPIOFB;
	reg &= ~(0x1 << 2);
	reg |= (0x1 << 2);
	GPIOFB = reg;
	//阀3 = 3
	reg = GPIOFA;
	reg &= ~(0x3 << 3);
	GPIOFA = reg;
	reg = GPIOFB;
	reg &= ~(0x1 << 3);
	reg |= (0x1 << 3);
	GPIOFB = reg;
}
//控制GPIO
void Control_GPIO(int n, int flag) {
	unsigned int reg = 0;
	if (flag == 1) {
		reg = GPIOFC;
		reg &= ~(0x1 << n);
		reg |= (0x1 << n);
		GPIOFC = reg;
	}else {
		reg = GPIOFC;
		reg &= ~(0x0 << n);
		reg |= (0x0 << n);
		GPIOFC = reg;
	}
}
//液位开关1控制
int Watch_Height() {
	unsigned int reg = 0;
	reg = GPIOFC;
	if(((reg >> 5) & 1) == 1) Control_GPIO(3,0)
	if(((reg >> 5) & 1) == 0) Control_GPIO(3,1)
	return ((reg >> 5) & 1);
}

//系统初始化
static void Init(void)
{
	pwm_config_u(2, TO_DUTY_NS(0, 1000), 1000000);
	malloc_init();
	s5p6818_pwm_init();
	s5p6818_serial_initial();
}

//延迟函数
void Delay(int ms) {
	int i, j = 0;
	for (i = 0; i < 4; i ++) {
		for (j = 0; j < 514; j ++){
		}
	}
}
//读取当前密度
double Get_Rou()
{
	return 1.6;
}
//密度计控制
void Watch_Rou()
{
	if(Watch_Height()){
			Control_GPIO(3,0);
		}
		if (getDensity() >= 1.6) {
			Control_GPIO(2,1);
			pwm_config_u(2, TO_DUTY_NS(95, 1000), 1000000);
			Delay(10*60*1000);
			Control_GPIO(2,0);
			Control_GPIO(1,1);
			pwm_config_u(2, TO_DUTY_NS(50, 1000), 1000000);
			Delay(30*1000);
			Control_GPIO(1,0);
			pwm_config_u(2, TO_DUTY_NS(0, 1000), 1000000);
		}
}

int main(int argc, char * argv[])
{
	Init();
	while(1) {
		Watch_Rou();
	}
	return 0;
}
