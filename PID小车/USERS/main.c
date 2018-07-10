
//==================
//main.c
//==================

#include "main.h"

#define if_need_display 0		//是否显示数据，调试时用，因为它比较耗单片机资源。

#define T0   0.01				//离散化采样周期，单位：s

//定义一个PID调节器 ASR
//data区已经满了，所以把结构体参数放在xdata区，但是如果在其他文件需要extern这个结构体的话，也要加上xdata
PID_value  xdata  ASR;	
	

/*
** 定义控制器的参数以及输出限幅，在这里进行KP/KI的调参。
** 2018.3.16  调节T0 = 0.01，KP = 0.6，KI = 30，KD = 0.0045效果比较理想，能很快稳定，过冲不至于太大。
** PID的输出限幅在（-3，7）之间即可,根据实际情况进行设定
** (10-3)/50 = 14%         (10+7)/50 = 34%
*/
float distance_kp = 1,
	  distance_ki = 35,
	  distance_kd = 0.0045,
	  limit_max = 7,		//0.002s周期下，这个范围不要变了(-3,7)
	  limit_min = -3;

float real_distance = 0;		//实际距离
uchar distance[6] = {0};		//测量距离最大为400cm，保留一位小数，如380.7cm 
uchar time1_flag = 0;  			//利用pwm的定时器，中断两次就是200us，进行一次pid运算。


#if (if_need_display)
uchar code string_1[] = {"Distence"};	//8
uchar code string_2[] = {":"};			//1
uchar code string_3[] = {"CM"};			//2
#endif


//==============主函数=============
int main()
{

	#if (if_need_display) 	
	lcd_init();			 //LCD初始化
	lcd_clear(BACK_COLOR);
	#endif

	//初始化PI调节器参数全为0, 该函数在string.h
	memset(&ASR, 0, sizeof(PID_value));

	#if PID_DEBUG
		ASR.KP = distance_kp;
		ASR.KI = distance_ki;
		ASR.KD = distance_kd;
	#else
		ASR.a0 = 1;
		ASR.a0 = 2;
		ASR.a0 = 3;
	#endif
	
	ASR.T = T0;
	ASR.out_max = limit_max;
	ASR.out_min = limit_min;
	
	
	//uart_init();		 //串口初始化
	sr04_init();		 //超声波模块初始化
	pwm_init();			 //PWM初始化


	#if (if_need_display)
	//显示距离格式
	show_string(5,10,string_1);
	show_string(5 + 64,10,string_2);
	show_string(5 + 120,10,string_3);
	#endif

	while(1)
	{
		real_distance = get_distence();	//单位为cm的实际距离，程序开始到这里需要运行1.1s，然后不断刷新距离

		if(time1_flag >= 100)	   		//100*100us = 0.01s，决定pid控制器的控制周期，进行一次pid运算就是一个控制周期
		{
			PID_out(&real_distance);	//PID运算并输出增加占空比
			time1_flag = 0;				//标志清零
		}

		//uart_send_senser();				//发送数据给匿名上位机

		#if (if_need_display)
		//使用C语言库函数 sprintf（） 把数字强制转换为字符串输出,这样真的可以减少很多工作量，比上面简单太多了。
		sprintf(distance,"%.2f",real_distance);
		show_string(5+72,10,distance);
		#endif

	}
}


//========================
//END OF FILE
//========================
