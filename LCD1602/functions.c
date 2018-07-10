
 #include "total.h"

void init_lcd1602(){

	  lcd_write_cmd(0x38);//������ʾģʽ��16*2��5*7��8λ���ݽӿ�
	  lcd_write_cmd(0x0c);//��ʾ����������
	  lcd_write_cmd(0x06);//���ֲ�������ַ�Զ���1
	  lcd_write_cmd(0x01);//����
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
	}while(sta & 0x80);	 //ȡ����λ��1��ʾæ������do��
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
		addr = 0x00 + x; //��һ�д�0x00��ʼ
	else 
		addr = 0x40 + x; //�ڶ��д�0x40��ʼ
	lcd_write_cmd(addr | 0x80); //����RAM ��ַ

}


void lcd_show_string(uchar x,uchar y,uchar *str){

	lcd_set_cursor(x,y);
	while(*str != '\0'){
		lcd_write_dat(*str++);
	}
}














