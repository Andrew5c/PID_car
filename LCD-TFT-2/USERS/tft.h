
#ifndef __TFT_H
#define	__TFT_H

//#include "MAIN.h"

/* 几种常用颜色 */
#define White          0xFFFF    //白
#define Black          0x0000    //黑
#define Red           0x001F     //红
#define Blue            0xF800   //蓝
#define Magenta        0xF81F    //紫
#define Green          0x07E0    //绿
#define Yellow           0x07FF  //黄   
#define Cyan         0xFFE0      //青

//定义背景和笔画颜色，方便后面,注意字体颜色的搭配
#define PEN_COLOR Black			//黑青颜色比较好看一点
#define BACK_COLOR Cyan

//LCD尺寸
#define LCD_WIDE 160
#define LCD_HIGH 160


//接口定义
#define DATA P0	    //数据口
sbit CS = P2^7;		//片选             
sbit RES = P2^5;	//复位
sbit RS = P2^4;		//数据/命令选择
sbit RW = P2^3;		//读写选择


//1.8寸显示点阵数是128*160
//不对啊，经实验发现怎么长宽都是160全屏啊？
void write_cmd(uchar cmd);
void write_data(uchar dat);
void write_data_16(uint dat);//分两次写入
void lcd_init();
//void dsp_single_color(uint fount_color,uint back_color);//定义前景颜色与背景颜色
void delayms(uint tt);
void lcd_setpos(uint x0,uint x1,uint y0,uint y1);//设置指定位置
void lcd_clear(uint color);//颜色清屏
//void draw_line(uchar color);
void draw_point(uint x,uint y,uint point_color);//画点,位置和颜色
void show_char(uint x,uint y,uchar num);//指定位置显示单个字符
void show_string(uint x,uint y,const uchar *p);
uint my_pow(uchar m,uchar n);
void show_number(uint x,uint y,uint num,uchar len);


#endif

