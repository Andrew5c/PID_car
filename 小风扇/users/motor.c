
#include "main.h"

//中断中自然风切换变量
volatile unsigned char BLOW_NATURE = 0;
//定时器中断计数变量
unsigned char pwm_count = 0 ;
//电机转速控制变量，越大越快
volatile unsigned char pwm_duty = 0;
//自然风计数变量
volatile unsigned int nature_pwm_count = 0;
//自然风的占空比遍历
volatile unsigned char pwm_value = 0;
//每一级风速的计数变量
volatile unsigned char per_pwm_count = 0;	
//风速达到最大标志,等于1为风速最大
volatile unsigned char top_flag = 0;
//第一次自然风初始化
volatile unsigned char is_first_time_blow_nature = 0;
volatile unsigned char is_first_time_start = 0;


/*
** 定时器0作为pwm波发生器;晶振为11.0592M
** pwm频率为500HZ，周期为0.002s=2ms
** 设置电机pwm的高电平时间范围为0.5ms - 1.8ms
** 100us(oxa3)�жϺ����е�Ƶ���ˣ��������ó�200us���ԣ���ֵΪ0x47
*/
void TIME0_PWM_Init(void)
{
	TMOD |= 0X02;	 /* 定时器0模式2, */  
    TH0 = 0XA3;		 /* 定时器设置，100us一次中断*/
    TL0 = 0XA3;
    ET0 = 1;		 /* 开定时器中断*/
    EA = 1;			 /* 开总中断*/
	IP = 0X10;		 //�����ж����ȼ��������ж����ȼ����
	TR0 = 1;		 /* 打开定时器*/
}

/*
** 定时器0中断函数
** 20次中断，变量清零一次，100us*20=2ms,这就是pwm的一个周期
** 如果高电平时间范围为0.5ms - 1.8ms，也就是占空比为25% - 90%
** 那么pwm_duty范围为5-18
** 在自然风代码段的2100是设置的14个占空比从最小增加到最大的用时3s，的每一个占空比应该持续的时间
*/
void TIME0_Handle(void) interrupt 1
{
	//如果没有定义这个宏，说明在普通模式
	if(BLOW_NATURE == 0)
	{
		pwm_count++;
		if(pwm_count <= pwm_duty)
			MOTOR_PWM = 1;
		else
			MOTOR_PWM = 0;
		
		if(pwm_count == 20)
			pwm_count = 0;
	}

	else
	{
		nature_pwm_count++;
		per_pwm_count++;
		//pwm_value为初始化MOTOR_PWM = 1 持续的时间，这里要注意pwm_value的初始化值
		if(per_pwm_count <= pwm_value)
			MOTOR_PWM = 1;
		else
			MOTOR_PWM = 0;	
		if(per_pwm_count == 100)
		{
			per_pwm_count = 0;
			MOTOR_PWM = 1;
		}
		
		//风速还没有达到最大之前，继续增加占空比

		//����nature_pwm_count�Ĵ�С�����Ըı���ٱ仯�Ŀ���
		if(nature_pwm_count == 5000 && top_flag == 0)
		{
			nature_pwm_count = 0;
			pwm_value++;
			if(pwm_value == 10)
			{
				top_flag = 1;
			}	
		}
		//风速达到最大之后，开始减小占空比
		else if(nature_pwm_count == 5000 && top_flag == 1)
		{
			nature_pwm_count = 0;
			pwm_value--;
			if(pwm_value == 0)
			{
				top_flag = 0;
			}	
		}	
	}	
}

/*
** 打开风扇,并赋值占空比
*/
void fan_start(unsigned char _duty)
{
	//中断函数模式选择标志
	BLOW_NATURE = 0;
	pwm_duty = _duty;
	
	if(is_first_time_start == 1)
	{
		is_first_time_start = 0;
		
		if(CMD_RX_Buffer[0] == 83)
			UART_send_string("**Start!**");
		else if(CMD_RX_Buffer[0] == 67)
			UART_send_string("**Close!**");
		else
			UART_send_string(CMD_RX_Buffer);

		//为切换到自然风做准备
		nature_pwm_count = 0;
		per_pwm_count = 0;
		top_flag = 0;
	}
}

/*
** 自然风实现函数,风速呈正弦波变化
*/
void fan_blow_nature(void)
{
	BLOW_NATURE = 1;
	
	//自然风初始占空比为5,但是只在进入的时候初始化一次，以后遍历都不在初始化
	if(is_first_time_blow_nature == 1)
	{
		is_first_time_blow_nature = 0;
		UART_send_string("Nature!");
		pwm_value = 0;

		//正常模式的计数变量清零，防止切换时的卡顿
		pwm_count = 0;
	}		
}

