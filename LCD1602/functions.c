
 #include "total.h"

void init_lcd1602(){

	  lcd_write_cmd(0x38);//设置显示模式，16*2，5*7，8位数据接口
	  lcd_write_cmd(0x0c);//显示器开，光标关
	  lcd_write_cmd(0x06);//文字不动，地址自动加1
	  lcd_write_cmd(0x01);//清屏
}

void lcd_wait(){

	uchar sta;
	LCD_DB = 0xff;
	LCD_RS = 0;
	LCD_RW = 1;
	do{
		LCD_CE = 1;
		sta = LCD_DB;
		LCD_CE = 0;
	}while(sta & 0x80);	 //取第七位，1表示忙，继续do，
}


void lcd_write_cmd(uchar cmd){
	lcd_wait();
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_DB = cmd;
	LCD_CE = 1;
	LCD_CE = 0;

}


void lcd_write_dat(uchar dat){

	lcd_wait();
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_DB = dat;
	LCD_CE = 1;
	LCD_CE = 0;
}


void lcd_set_cursor(uchar x,uchar y){

	uchar addr;
	if(y==0)
		addr = 0x00 + x; //第一行从0x00开始
	else 
		addr = 0x40 + x; //第二行从0x40开始
	lcd_write_cmd(addr | 0x80); //设置RAM 地址

}


void lcd_show_string(uchar x,uchar y,uchar *str){

	lcd_set_cursor(x,y);
	while(*str != '\0'){
		lcd_write_dat(*str++);
	}
}














