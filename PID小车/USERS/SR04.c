
//==================
//SR04.c
//==================
//一个安全优秀的程序，必然包含了所有的可能情况，但是这样的话势必增大程序体积，优化很重要！

#include "main.h"

#define NUM 3			//滤波次数

uchar time0_flag = 0;	//定时器溢出标志

/*初始化函数
 定时器模式1，从0开始计数，最大到65535，一次溢出需要的时间是0.065s，声速为340m/s
 那么溢出时的距离为22.1m，已经远远超过了超声波模块的测量范围(0-5m),所以只要产生一次溢出，就可以认为是超出测量范围. 
*/
void sr04_init()
{	
	TRIG = 0;
	ECHO = 0;

	TMOD |= 0X01;	//定时器0模式设置1
	TH0 = 0;		//从0开始计数
	TL0 = 0;
	TR0 = 0;		//关闭定时器
	EA = 1;			//开总中断
	ET0 = 1;		//允许定时器0中断
}

/*start*/
void  sr04_start()
{
	 TRIG = 1;	
	 delay_10us(5); //拉高50us
	 TRIG = 0;
}

/*开启定时器0，打开之前先清除之前的计数,不然会累计计数*/
void time_0_start()
{	
	TH0 = 0;	   //打开前计数清零
	TL0 = 0;
	TR0 = 1;	   //打开定时器
}

/*********************************
作者 ：Andre
日期 ：2018.3.8
说明 ：
	1、开启超声波测距，多次测量取平均值，当超出测量范围时，舍去
**********************************/
float get_distence()
{
	unsigned long int time_buf = 0;		//总耗时
	float distence = 0;		//计算一次距离
	float sum = 0;		    //多次计算的总距离
	uchar i = 0;

	while(i < NUM)
	{
		time0_flag = 0;	//先清除标志
		sr04_start();	//开始测距
		while(!ECHO); 	//等待发出40khz脉冲，触发信号之后，echo会变成高电平
		time_0_start();	//当把trig拉高10us之后，模块即开始发出8个40khz的脉冲，与此同时，echo变为高电平时，打开定时器。
		while(ECHO); 	//等待回响信号，收到回响信号，echo会变低电平
		TR0 = 0;	  	//关闭定时器

		if(time0_flag != 0)  //超出测量范围
			continue;		//不进行计算，放弃这次测量，从新测量

		else				//time_flag = 0,没有超出测量范围
		{
			time_buf = (TH0 * 256) + TL0;
			distence = time_buf * 0.0168;//（单位:cm）虽然声速340m/s，发现使用0.0168更精确，可能和温度有关
			sum+= distence;
			i++;
		}	  
	}	
	return (sum/NUM) ;	//取NUM次平均值
}

/*
中断处理函数，65535个计数产生溢出，大概为71.1ms
如果产生溢出，说明距离已经超过了22.1米
已经远远超过了模块的测量范围
*/
void TIME0() interrupt 1
{
//	TF0 = 0;	   //模式1硬件自动清零
	TH0 = 0;
	TL0 = 0;
	time0_flag++;
}

//========================
//END OF FILE
//========================



