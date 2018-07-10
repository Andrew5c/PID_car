//=============
//uart.c
//=============

#include "main.h"

float set_distance_2 = 10.00 ;//发送这个定值，在上位机中一条直线作为参考
extern float real_distance;   //发送实际距离

extern PID_value  xdata ASR;  //发送pid的输出值


/* ********************************************************
** 作者 ：Andrew
** 日期	：2018.3.11    
** 说明 ：
	1、使用定时器2做波特率发生器，11.0592M晶振，可以产生115200的波特率
	2、使用85C52系列的单片机时，一般P3.1-TXD,   P3.0-RXD ,且与USB共地。
	3、115200波特率的时候，必须使用11.0592的晶振，12M的不行，这个细节让我找了半天的bug。发疯ing 
	4、12M晶振时的波特率最好时4800，误差最小。                      
******************************************************** */
void uart_init()
{
	SCON = 0X50;			//SCON:串行口工作方式1, 8-bit UART,允许串行接收位(REN=1)
	TH2 = RCAP2H = 0XFF;	//baud : 115200
	TL2 = RCAP2L = 0XFD;	//0xdc 为9600 baud	   ,0XFD为115200 baud
	T2CON = 0X34;			//控制寄存器，可设置三种工作模式：捕获、计数器、波特率发生器
	IE = 0X90;				//IE中断允许寄存器，0x90是开总中断和串口中断。
		 
}

/* *************************************
** 作者 ：Andrew
** 日期	：2018.3.11  
** 说明 ：中断方式通过串口发送一个字符
****************************************/
void uart_send_char(unsigned char _data)
{
	ES = 0;			//先关闭串口中断
	SBUF = _data;
	while(!TI);		//发送完成后，TI会置1
	TI = 0;			//清除标志
	ES = 1;

}


/* *************************************
** 作者 ：Andrew
** 日期	：2018.3.11  
** 说明 ：
	1、函数入口为数据的头地址，数据的长度
	2、循环发送一个长度为cnt的数据
****************************************/
void uart_send_string(unsigned char *_data,unsigned char cnt)
{
	unsigned char i;

	for(i = 0;i<cnt;i++)
	{
		uart_send_char(*(_data + i));	
	}

}



/******************************************
** 说明：
	1、 发送给上位机的数据帧定义 
		@桢头--功能字--长度--数据（一个或多个，具体看协议说明）-校验
		@前2个字节为帧头0xAAAA 
		@第3个字节为帧ID，也就是功能字，应设置为0xF1~0xFA中的一个 
		@第4个字节为报文数据长度(dlc) 
		@第5个字节开始到第5+dlc-1个字节为要传输的数据内容段，每个数据场为高字节在前，地字节在后 
		@第5+dlc个字节为CheckSum,为第1个字节到第5+dlc-1个字节所有字节的值相加后，保留结果的低八位作为CheckSum 
	2、 外部直接调用这个函数。
	3、 需要在此文件中引用需要发送的其他文件中的数据。
	4、 发送的数据必须是 int_16 型的数据
*****************************************/  
void uart_send_senser(void)
{
	unsigned char  xdata data_to_send[23] = {0};
	unsigned char i = 0;
	unsigned char cnt = 0;
	unsigned char sum = 0;

	int int_set_distance_2 = (int)set_distance_2;
	int int_real_distance = (int)real_distance;
	int int_ASR_output = (int)ASR.output;
	

	data_to_send[cnt++]=0xAA;	 //帧头：AAAA
	data_to_send[cnt++]=0xAA;
	data_to_send[cnt++]=0x02;	 //功能字：OXFn只接受数据，不显示图像。0x0n显示数据和图像
	data_to_send[cnt++]=0;	     //需要发送数据的字节数，后面计算

	data_to_send[cnt++] = BYTE1(int_set_distance_2);	//高字节
	data_to_send[cnt++] = BYTE0(int_set_distance_2);	//低字节
	data_to_send[cnt++] = BYTE1(int_real_distance);
	data_to_send[cnt++] = BYTE0(int_real_distance);
	data_to_send[cnt++] = BYTE1(int_ASR_output);
	data_to_send[cnt++] = BYTE0(int_ASR_output);

//	data_to_send[cnt++] = BYTE1(int_set_distance_2);
//	data_to_send[cnt++] = BYTE0(int_set_distance_2);
//	data_to_send[cnt++] = BYTE1(int_set_distance_2);
//	data_to_send[cnt++] = BYTE0(int_set_distance_2);
//	data_to_send[cnt++] = BYTE1(int_set_distance_2);
//	data_to_send[cnt++] = BYTE0(int_set_distance_2);
//
//	data_to_send[cnt++] = BYTE1(int_set_distance_2);
//	data_to_send[cnt++] = BYTE0(int_set_distance_2);
//	data_to_send[cnt++] = BYTE1(int_set_distance_2);
//	data_to_send[cnt++] = BYTE0(int_set_distance_2);
//	data_to_send[cnt++] = BYTE1(int_set_distance_2);
//	data_to_send[cnt++] = BYTE0(int_set_distance_2);

	data_to_send[cnt++] = 0;
	data_to_send[cnt++] = 0;
	data_to_send[cnt++] = 0;
	data_to_send[cnt++] = 0;
	data_to_send[cnt++] = 0;
	data_to_send[cnt++] = 0;

	data_to_send[cnt++] = 0;
	data_to_send[cnt++] = 0;
	data_to_send[cnt++] = 0;
	data_to_send[cnt++] = 0;
	data_to_send[cnt++] = 0;
	data_to_send[cnt++] = 0;

	data_to_send[3] = cnt-4;//计算总数据的字节数。

	for(i=0;i<cnt;i++) //对于for语句，当不写大括号的时候，只执行到下面第一个分号结束。
	{
		sum+=data_to_send[i];
	}
	data_to_send[cnt++] = sum;	//计算校验位

	uart_send_string(data_to_send,cnt);	   //发送数据包

}


//========================
//END OF FILE
//========================
