
#ifndef __DS1302_H
#define __DS1302_H

//READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};//��ȡʱ��������ַ
//WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};//дʱ��������ַ

#define UP() {SCLK = 0;nop();SCLK = 1;nop();} //������  ,ʹ�ú궨�庯��ʱ���һ���ҷֺ�
#define DOWN() {SCLK = 1;nop();SCLK = 0;nop();} //�½���

//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

 //���ģ����û�м����������裬ʹ��ʱ��ý���2
sbit CE = P2^0;//RET,ʹ���������ţ�����дʱ���ø�λ
sbit SCIO = P2^1;//IO	 ��˫��ͨ�����ţ���д���ݶ���ͨ��������
sbit SCLK = P2^2;//SCLK��ʱ���ź�


//Ϊʲô��ʱ��úõģ�Ҳ�������ʾ���˷ֺ��أ������˰���������

void ds1302_writebyte(uchar byte);//дһ���ֽ�; 
void ds1302_writedata(uchar addr,uchar data_);//��ĳ��ַд����,data��c51�ڲ��Ĺؼ��֣���ʾ���������������ݴ洢�����ʴ˴���data_;
uchar ds1302_readbyte();//��һ���ֽ�
uchar ds1302_readdata(uchar addr);//��ȡĳ�Ĵ�������	 ;
void init_ds1302();
void ds1302_readtime();


extern uchar init_time[];

#endif


