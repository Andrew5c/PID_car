
#include "main.h"

//接收缓冲与计数变量
unsigned char RX_Buffer[20];
unsigned char CMD_RX_Buffer[20];
unsigned char RX_Counter = 0;

/* ********************************************************
** 作者 ：Andrew
** 日期	：2018.3.11    
** 说明 ：
	1、使用定时器2做波特率发生器，11.0592M晶振，可以产生115200的波特率
	2、使用85C52系列的单片机时，一般P3.1-TXD,   P3.0-RXD ,且与USB共地。
	3、115200波特率的时候，必须使用11.0592的晶振，12M的不行，这个细节让我找了半天的bug。发疯ing 
	4、12M晶振时的波特率最好时4800，误差最小。                      
*********************************************************/
void TIME2_UART_Init(void)
{
	SCON = 0X50;			//SCON:串行口工作方式1, 8-bit UART,允许串行接收位(REN=1)
	TH2 = RCAP2H = 0XFF;	//baud : 115200
	TL2 = RCAP2L = 0XFD;	//0xdc 为9600 baud	   ,0XFD为115200 baud
	T2CON = 0X34;			//控制寄存器，可设置三种工作模式：捕获、计数器、波特率发生器
	IE = 0X90;				//IE中断允许寄存器，0x90是开总中断和串口中断。
//	TI = 1;					//使用printf
}


/*
** 串口发送一个字符串
*/
void UART_send_string(unsigned char *TX_str)
{
	ES = 0;					//先关闭串口中断
	while(*TX_str != 0)
	{
		SBUF = *TX_str;
		while(TI == 0);		//发送完成后，TI会置1
		TI = 0;				//清除标志
		TX_str++;
	}
	ES = 1;
}


/*
** 串口中断处理函数
** 在这里根据蓝牙串口发送过来的命令调整风扇的转速。
** 命令格式为最后要有回车键
*/
void UART_Handle(void) interrupt 4
{
	//接收
	if(RI)
	{
		RI = 0;
		EA = 0;
		RX_Buffer[RX_Counter++] = SBUF;
		
		if((RX_Counter == 3) && (RX_Buffer[RX_Counter-2] == 0x0d))
		{
			//如果符合命令格式，就拷贝到命令缓冲区
			memcpy(CMD_RX_Buffer,RX_Buffer,RX_Counter);
			CMD_RX_Buffer[RX_Counter] = '\0';
			RX_Counter = 0;
			is_first_time_start = 1;
			is_first_time_blow_nature = 1;
			UART_send_string("Receieved!");
		}
		EA = 1;		
	}
		
	//发送就不处理，在发送函数中延时发送，其实都差不多
}

/*
** 对串口接收的内容进行分类,规定上位机只发送单字节的命令
** 注意全是ascii码值
** CMD_RX_Buffer的第一个元素值可以有一下几种情况：
	S :start，开始，并怠速转动
	C :close，关闭
	N :nature，自然风
	1-5 :表示五档风速调节
*/
void UART_resieve_analyse(void)
{
	//确保发送格式下，只获取命令缓冲区第一�
	unsigned char resieve = CMD_RX_Buffer[0];
	
	switch(resieve)
	{
		//模式选择
		case 83:	fan_start(10);break;		//S的ascii码，开始的时候，默认占空比50%
		case 67:	fan_start(0);break;			//C,关闭风扇就是占空比赋值为0
		case 78:	fan_blow_nature();break;	//N，自然风模式
		//五档风速可调
		case 49:	fan_start(11);break;
		case 50:	fan_start(12);break;
		case 51:	fan_start(13);break;
		case 52:	fan_start(14);break;
		case 53:	fan_start(15);break;
		
		//如果接收到的不是命令，给出反馈
		default:	
			if(is_first_time_start == 1)
			{
				is_first_time_start = 0;
				UART_send_string("Not CMD!");
			}break;
	}
}


