
#ifndef __LCD_H
#define __LCD_H

#define LCD_DB P0//数据

//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

sbit LCD_RS	= P2^6;
sbit LCD_RW	= P2^5;
sbit LCD_CE	= P2^7;

void init_lcd1602(void);
void lcd_wait();//等待液晶准备好
void lcd_write_cmd(uchar cmd);
void lcd_write_dat(uchar dat);
void lcd_set_cursor(uchar x,uchar y); //设置字符坐标
void lcd_show_string(uchar x,uchar y,uchar *str);//显示字符


#endif

