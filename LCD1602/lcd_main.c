#include "total.h"

uchar init_time[] = {0x50,0x15,0x14,0x22,0x10,0x06,0x17};//初始化的时间	//秒 分 时 日 月 周 年 
//uint disp[8]={0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f};//把要显示的数字传给他	


void display();

 void main(){
 
	init_lcd1602();
	init_ds1302();
	
	while(1){

		display();	 //如何把从1302中获取的动态数据传送到1602上面？
	} 
 }

 void display(){

 	 ds1302_readtime();
 
 }

