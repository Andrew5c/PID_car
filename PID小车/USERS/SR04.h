
#ifndef __SR04_H
#define	__SR04_H

//������ʹ��T0��ʱ�����м���,���������źŵĳ���ʱ�䣬�жϺ�Ϊ1,

sbit TRIG = P2^6;//���ƶ�
sbit ECHO = P2^7;//���ն�


void sr04_init();//��ʼ��������ģ��
void sr04_start();//�򿪳���������������TRIG����10usȻ���ͷ�
void time_0_start();  //�򿪶�ʱ��ǰ��ռ���
float get_distence();//��ȡ��ǰ����


#endif



