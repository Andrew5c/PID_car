#ifndef __KEY_H
#define __KEY_H

//#include "MAIN.h"


sbit k1_chose = P3^1;//ѡ����Ҫ���õ�λ��
sbit k2_plus = P3^0;//���Ӽ���
sbit k3_set = P3^2;//��Ƭ���˶˿ڽ��ⲿ�ж�0


void int0_config();
void key_init();
void set_remind(uchar flag);

extern uchar set_flag;//������������
extern uchar chose_flag;

#endif

