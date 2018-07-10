#ifndef __KEY_H
#define __KEY_H

//#include "MAIN.h"


sbit k1_chose = P3^1;//选择需要设置的位数
sbit k2_plus = P3^0;//增加计数
sbit k3_set = P3^2;//单片机此端口接外部中断0


void int0_config();
void key_init();
void set_remind(uchar flag);

extern uchar set_flag;//主函数里引用
extern uchar chose_flag;

#endif

