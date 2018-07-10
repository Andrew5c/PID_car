
//==================
//car.c
//==================

#include "main.h"


#define H 50	//设置pwm的频率，H=20时，1s/(20*100us) = 500hz	，H=50对应200hz

extern uchar time1_flag ;  //利用pwm的定时器，中断两次就是200us，进行一次pid运算。

/*占空比变量定义 */
uint Low_Speed = 10; 	   //经测试还是5最合适，3无法驱动电机	，200hz
uint Left_Forward_Duty = 0;	    /* 左电机 正转 */
uint Right_Forward_Duty = 0;	/* 右电机 正转 */

/* 占空比计数变量定义和 预设占空比 进行比较 */
uint Left_Forward_Cnt = 0;	  /* 左电机 正转占空比计数 */
uint Right_Forward_Cnt = 0;   /* 右电机 正转占空比计数 */


/*
** 定时器产生pwm初始化
** 使用定时器1模式2，8位自动重装，最大计数256，
** 12M晶振下，定时100us，需要赋初始值156d = 0x9c
** 11.0592M晶振下，定时100us，初值为164 = 0xa3
*/
void pwm_init()
{
	TMOD |= 0x20;	 /* 定时器1模式2, */  
    TH1 = 0XA3;		 /* 定时器设置，100us一次中断*/
    TL1 = 0XA3;
    ET1 = 1;		 /* 开定时器中断*/
    EA = 1;			 /* 开总中断*/
	TR1 = 1;		 /* 打开定时器*/
}


/*
** 停车
*/
void car_stop()
{	
	Left_Forward_Duty = 0;
	Right_Forward_Duty = 0;
}


/*
** 定时器1中断入口,中断号3
*/
void time_1() interrupt 3
{
  	/*左轮前进PWM输出*/	
	Left_Forward_Cnt++;

	if(Left_Forward_Cnt <= Left_Forward_Duty)  //这里控制占空比
		left_en = 1;//高电平，使能电机
	else 
		left_en = 0;	
	if(Left_Forward_Cnt == H)
     	Left_Forward_Cnt = 0;	
	

  /*右轮前进PWM输出*/
	Right_Forward_Cnt++;

	if(Right_Forward_Cnt <= Right_Forward_Duty)
		right_en = 1; 
	else 
		right_en = 0;	
	if(Right_Forward_Cnt == H)
     	Right_Forward_Cnt = 0;


	/*中断两次进行一次pid运算*/
	time1_flag++;

}


//========================
//END OF FILE
//========================

