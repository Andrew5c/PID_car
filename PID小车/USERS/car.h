#ifndef __CAR_H
#define __CAR_H

/*left_1 = 1;
  left_0 = 0;����ǰ��*/
sbit left_en = P2^5; //����ʹ��
sbit left_1 = P2^3;//IN3
sbit left_0 = P2^4;//IN4

/*right_1 = 1;
  right_0 = 0;����ǰ��*/
sbit right_en = P2^2;//�ҵ��ʹ��
sbit right_1 = P2^1;//IN1
sbit right_0 = P2^0;//IN2

#define left_go_ahead {left_1 = 1;left_0 = 0;}
#define left_go_back {left_1 = 0;left_0 = 1;}
#define left_stop {left_1 = 1;left_0 = 1;}

#define right_go_ahead {right_1 = 1;right_0 = 0;}
#define right_go_back {right_1 = 0;right_0 = 1;}
#define right_stop {right_1 = 1;right_0 = 1;}

//��������ʹ��
extern uint Low_Speed; 	   	
extern uint Left_Forward_Duty;	    /* ���� ��ת */
extern uint Right_Forward_Duty;		/* �ҵ�� ��ת */


void pwm_init();
void car_stop();


#endif


