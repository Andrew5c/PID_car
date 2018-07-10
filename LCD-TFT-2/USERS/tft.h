
#ifndef __TFT_H
#define	__TFT_H

//#include "MAIN.h"

/* ���ֳ�����ɫ */
#define White          0xFFFF    //��
#define Black          0x0000    //��
#define Red           0x001F     //��
#define Blue            0xF800   //��
#define Magenta        0xF81F    //��
#define Green          0x07E0    //��
#define Yellow           0x07FF  //��   
#define Cyan         0xFFE0      //��

//���屳���ͱʻ���ɫ���������,ע��������ɫ�Ĵ���
#define PEN_COLOR Black			//������ɫ�ȽϺÿ�һ��
#define BACK_COLOR Cyan

//LCD�ߴ�
#define LCD_WIDE 160
#define LCD_HIGH 160


//�ӿڶ���
#define DATA P0	    //���ݿ�
sbit CS = P2^7;		//Ƭѡ             
sbit RES = P2^5;	//��λ
sbit RS = P2^4;		//����/����ѡ��
sbit RW = P2^3;		//��дѡ��


//1.8����ʾ��������128*160
//���԰�����ʵ�鷢����ô������160ȫ������
void write_cmd(uchar cmd);
void write_data(uchar dat);
void write_data_16(uint dat);//������д��
void lcd_init();
//void dsp_single_color(uint fount_color,uint back_color);//����ǰ����ɫ�뱳����ɫ
void delayms(uint tt);
void lcd_setpos(uint x0,uint x1,uint y0,uint y1);//����ָ��λ��
void lcd_clear(uint color);//��ɫ����
//void draw_line(uchar color);
void draw_point(uint x,uint y,uint point_color);//����,λ�ú���ɫ
void show_char(uint x,uint y,uchar num);//ָ��λ����ʾ�����ַ�
void show_string(uint x,uint y,const uchar *p);
uint my_pow(uchar m,uchar n);
void show_number(uint x,uint y,uint num,uchar len);


#endif

