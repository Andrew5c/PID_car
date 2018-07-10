
#ifndef __DS1302_H
#define __DS1302_H

//#include "MAIN.h"

//READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};//读取时间的命令地址
//WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};//写时间的命令地址

#define UP() {SCLK = 0;nop();SCLK = 1;nop();} //上升沿  ,使用宏定义函数时最后一定家分号
#define DOWN() {SCLK = 1;nop();SCLK = 0;nop();} //下降沿
#define nop() _nop_()


 //这个模块内没有集成上拉电阻，使用时最好接上2
sbit CE = P2^0;//RET,使能输入引脚，当读写时，置高位
sbit SCIO = P2^1;//IO	 ，双向通信引脚，读写数据都是通过这个完成
sbit SCLK = P2^2;//SCLK，时钟信号


void ds1302_writebyte(uchar byte_1);//写一个字节; byte是保留字，不能作为变量
void ds1302_writedata(uchar addr,uchar data_);//给某地址写数据,data是c51内部的关键字，表示将变量定义在数据存储区，故此处用data_;
uchar ds1302_readbyte();//读一个字节
uchar ds1302_readdata(uchar addr);//读取某寄存器数据;
void ds1302_init();
void ds1302_readtime();


extern uchar init_time[]; //在引用此头文件的源文件中定义

#endif


