
#ifndef __DS1302_H
#define __DS1302_H

//#include "MAIN.h"

//READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};//��ȡʱ��������ַ
//WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};//дʱ��������ַ

#define UP() {SCLK = 0;nop();SCLK = 1;nop();} //������  ,ʹ�ú궨�庯��ʱ���һ���ҷֺ�
#define DOWN() {SCLK = 1;nop();SCLK = 0;nop();} //�½���
#define nop() _nop_()


 //���ģ����û�м����������裬ʹ��ʱ��ý���2
sbit CE = P2^0;//RET,ʹ���������ţ�����дʱ���ø�λ
sbit SCIO = P2^1;//IO	 ��˫��ͨ�����ţ���д���ݶ���ͨ��������
sbit SCLK = P2^2;//SCLK��ʱ���ź�


void ds1302_writebyte(uchar byte_1);//дһ���ֽ�; byte�Ǳ����֣�������Ϊ����
void ds1302_writedata(uchar addr,uchar data_);//��ĳ��ַд����,data��c51�ڲ��Ĺؼ��֣���ʾ���������������ݴ洢�����ʴ˴���data_;
uchar ds1302_readbyte();//��һ���ֽ�
uchar ds1302_readdata(uchar addr);//��ȡĳ�Ĵ�������;
void ds1302_init();
void ds1302_readtime();


extern uchar init_time[]; //�����ô�ͷ�ļ���Դ�ļ��ж���

#endif

