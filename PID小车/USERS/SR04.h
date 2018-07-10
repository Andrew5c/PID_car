
#ifndef __SR04_H
#define	__SR04_H

//超声波使用T0定时器进行计数,测量回响信号的持续时间，中断号为1,

sbit TRIG = P2^6;//控制端
sbit ECHO = P2^7;//接收端


void sr04_init();//初始化超声波模块
void sr04_start();//打开超声波，就是拉高TRIG持续10us然后释放
void time_0_start();  //打开定时器前清空计数
float get_distence();//获取当前距离


#endif



