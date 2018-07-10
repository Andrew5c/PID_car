//=============
//uart.c
//=============

#include "main.h"

float set_distance_2 = 10.00 ;//���������ֵ������λ����һ��ֱ����Ϊ�ο�
extern float real_distance;   //����ʵ�ʾ���

extern PID_value  xdata ASR;  //����pid�����ֵ


/* ********************************************************
** ���� ��Andrew
** ����	��2018.3.11    
** ˵�� ��
	1��ʹ�ö�ʱ��2�������ʷ�������11.0592M���񣬿��Բ���115200�Ĳ�����
	2��ʹ��85C52ϵ�еĵ�Ƭ��ʱ��һ��P3.1-TXD,   P3.0-RXD ,����USB���ء�
	3��115200�����ʵ�ʱ�򣬱���ʹ��11.0592�ľ���12M�Ĳ��У����ϸ���������˰����bug������ing 
	4��12M����ʱ�Ĳ��������ʱ4800�������С��                      
******************************************************** */
void uart_init()
{
	SCON = 0X50;			//SCON:���пڹ�����ʽ1, 8-bit UART,�����н���λ(REN=1)
	TH2 = RCAP2H = 0XFF;	//baud : 115200
	TL2 = RCAP2L = 0XFD;	//0xdc Ϊ9600 baud	   ,0XFDΪ115200 baud
	T2CON = 0X34;			//���ƼĴ��������������ֹ���ģʽ�����񡢼������������ʷ�����
	IE = 0X90;				//IE�ж�����Ĵ�����0x90�ǿ����жϺʹ����жϡ�
		 
}

/* *************************************
** ���� ��Andrew
** ����	��2018.3.11  
** ˵�� ���жϷ�ʽͨ�����ڷ���һ���ַ�
****************************************/
void uart_send_char(unsigned char _data)
{
	ES = 0;			//�ȹرմ����ж�
	SBUF = _data;
	while(!TI);		//������ɺ�TI����1
	TI = 0;			//�����־
	ES = 1;

}


/* *************************************
** ���� ��Andrew
** ����	��2018.3.11  
** ˵�� ��
	1���������Ϊ���ݵ�ͷ��ַ�����ݵĳ���
	2��ѭ������һ������Ϊcnt������
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
** ˵����
	1�� ���͸���λ��������֡���� 
		@��ͷ--������--����--���ݣ�һ�����������忴Э��˵����-У��
		@ǰ2���ֽ�Ϊ֡ͷ0xAAAA 
		@��3���ֽ�Ϊ֡ID��Ҳ���ǹ����֣�Ӧ����Ϊ0xF1~0xFA�е�һ�� 
		@��4���ֽ�Ϊ�������ݳ���(dlc) 
		@��5���ֽڿ�ʼ����5+dlc-1���ֽ�ΪҪ������������ݶΣ�ÿ�����ݳ�Ϊ���ֽ���ǰ�����ֽ��ں� 
		@��5+dlc���ֽ�ΪCheckSum,Ϊ��1���ֽڵ���5+dlc-1���ֽ������ֽڵ�ֵ��Ӻ󣬱�������ĵͰ�λ��ΪCheckSum 
	2�� �ⲿֱ�ӵ������������
	3�� ��Ҫ�ڴ��ļ���������Ҫ���͵������ļ��е����ݡ�
	4�� ���͵����ݱ����� int_16 �͵�����
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
	

	data_to_send[cnt++]=0xAA;	 //֡ͷ��AAAA
	data_to_send[cnt++]=0xAA;
	data_to_send[cnt++]=0x02;	 //�����֣�OXFnֻ�������ݣ�����ʾͼ��0x0n��ʾ���ݺ�ͼ��
	data_to_send[cnt++]=0;	     //��Ҫ�������ݵ��ֽ������������

	data_to_send[cnt++] = BYTE1(int_set_distance_2);	//���ֽ�
	data_to_send[cnt++] = BYTE0(int_set_distance_2);	//���ֽ�
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

	data_to_send[3] = cnt-4;//���������ݵ��ֽ�����

	for(i=0;i<cnt;i++) //����for��䣬����д�����ŵ�ʱ��ִֻ�е������һ���ֺŽ�����
	{
		sum+=data_to_send[i];
	}
	data_to_send[cnt++] = sum;	//����У��λ

	uart_send_string(data_to_send,cnt);	   //�������ݰ�

}


//========================
//END OF FILE
//========================
