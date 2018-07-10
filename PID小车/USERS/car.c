
//==================
//car.c
//==================

#include "main.h"


#define H 50	//����pwm��Ƶ�ʣ�H=20ʱ��1s/(20*100us) = 500hz	��H=50��Ӧ200hz

extern uchar time1_flag ;  //����pwm�Ķ�ʱ�����ж����ξ���200us������һ��pid���㡣

/*ռ�ձȱ������� */
uint Low_Speed = 10; 	   //�����Ի���5����ʣ�3�޷��������	��200hz
uint Left_Forward_Duty = 0;	    /* ���� ��ת */
uint Right_Forward_Duty = 0;	/* �ҵ�� ��ת */

/* ռ�ձȼ������������ Ԥ��ռ�ձ� ���бȽ� */
uint Left_Forward_Cnt = 0;	  /* ���� ��תռ�ձȼ��� */
uint Right_Forward_Cnt = 0;   /* �ҵ�� ��תռ�ձȼ��� */


/*
** ��ʱ������pwm��ʼ��
** ʹ�ö�ʱ��1ģʽ2��8λ�Զ���װ��������256��
** 12M�����£���ʱ100us����Ҫ����ʼֵ156d = 0x9c
** 11.0592M�����£���ʱ100us����ֵΪ164 = 0xa3
*/
void pwm_init()
{
	TMOD |= 0x20;	 /* ��ʱ��1ģʽ2, */  
    TH1 = 0XA3;		 /* ��ʱ�����ã�100usһ���ж�*/
    TL1 = 0XA3;
    ET1 = 1;		 /* ����ʱ���ж�*/
    EA = 1;			 /* �����ж�*/
	TR1 = 1;		 /* �򿪶�ʱ��*/
}


/*
** ͣ��
*/
void car_stop()
{	
	Left_Forward_Duty = 0;
	Right_Forward_Duty = 0;
}


/*
** ��ʱ��1�ж����,�жϺ�3
*/
void time_1() interrupt 3
{
  	/*����ǰ��PWM���*/	
	Left_Forward_Cnt++;

	if(Left_Forward_Cnt <= Left_Forward_Duty)  //�������ռ�ձ�
		left_en = 1;//�ߵ�ƽ��ʹ�ܵ��
	else 
		left_en = 0;	
	if(Left_Forward_Cnt == H)
     	Left_Forward_Cnt = 0;	
	

  /*����ǰ��PWM���*/
	Right_Forward_Cnt++;

	if(Right_Forward_Cnt <= Right_Forward_Duty)
		right_en = 1; 
	else 
		right_en = 0;	
	if(Right_Forward_Cnt == H)
     	Right_Forward_Cnt = 0;


	/*�ж����ν���һ��pid����*/
	time1_flag++;

}


//========================
//END OF FILE
//========================

