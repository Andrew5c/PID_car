
//==================
//main.c
//==================

#include "main.h"

#define if_need_display 0		//�Ƿ���ʾ���ݣ�����ʱ�ã���Ϊ���ȽϺĵ�Ƭ����Դ��

#define T0   0.01				//��ɢ���������ڣ���λ��s

//����һ��PID������ ASR
//data���Ѿ����ˣ����԰ѽṹ���������xdata������������������ļ���Ҫextern����ṹ��Ļ���ҲҪ����xdata
PID_value  xdata  ASR;	
	

/*
** ����������Ĳ����Լ�����޷������������KP/KI�ĵ��Ρ�
** 2018.3.16  ����T0 = 0.01��KP = 0.6��KI = 30��KD = 0.0045Ч���Ƚ����룬�ܺܿ��ȶ������岻����̫��
** PID������޷��ڣ�-3��7��֮�伴��,����ʵ����������趨
** (10-3)/50 = 14%         (10+7)/50 = 34%
*/
float distance_kp = 1,
	  distance_ki = 35,
	  distance_kd = 0.0045,
	  limit_max = 7,		//0.002s�����£������Χ��Ҫ����(-3,7)
	  limit_min = -3;

float real_distance = 0;		//ʵ�ʾ���
uchar distance[6] = {0};		//�����������Ϊ400cm������һλС������380.7cm 
uchar time1_flag = 0;  			//����pwm�Ķ�ʱ�����ж����ξ���200us������һ��pid���㡣


#if (if_need_display)
uchar code string_1[] = {"Distence"};	//8
uchar code string_2[] = {":"};			//1
uchar code string_3[] = {"CM"};			//2
#endif


//==============������=============
int main()
{

	#if (if_need_display) 	
	lcd_init();			 //LCD��ʼ��
	lcd_clear(BACK_COLOR);
	#endif

	//��ʼ��PI����������ȫΪ0, �ú�����string.h
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
	
	
	//uart_init();		 //���ڳ�ʼ��
	sr04_init();		 //������ģ���ʼ��
	pwm_init();			 //PWM��ʼ��


	#if (if_need_display)
	//��ʾ�����ʽ
	show_string(5,10,string_1);
	show_string(5 + 64,10,string_2);
	show_string(5 + 120,10,string_3);
	#endif

	while(1)
	{
		real_distance = get_distence();	//��λΪcm��ʵ�ʾ��룬����ʼ��������Ҫ����1.1s��Ȼ�󲻶�ˢ�¾���

		if(time1_flag >= 100)	   		//100*100us = 0.01s������pid�������Ŀ������ڣ�����һ��pid�������һ����������
		{
			PID_out(&real_distance);	//PID���㲢�������ռ�ձ�
			time1_flag = 0;				//��־����
		}

		//uart_send_senser();				//�������ݸ�������λ��

		#if (if_need_display)
		//ʹ��C���Կ⺯�� sprintf���� ������ǿ��ת��Ϊ�ַ������,������Ŀ��Լ��ٺܶ๤�������������̫���ˡ�
		sprintf(distance,"%.2f",real_distance);
		show_string(5+72,10,distance);
		#endif

	}
}


//========================
//END OF FILE
//========================
