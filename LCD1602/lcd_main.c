#include "total.h"

uchar init_time[] = {0x50,0x15,0x14,0x22,0x10,0x06,0x17};//��ʼ����ʱ��	//�� �� ʱ �� �� �� �� 
//uint disp[8]={0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f};//��Ҫ��ʾ�����ִ�����	


void display();

 void main(){
 
	init_lcd1602();
	init_ds1302();
	
	while(1){

		display();	 //��ΰѴ�1302�л�ȡ�Ķ�̬���ݴ��͵�1602���棿
	} 
 }

 void display(){

 	 ds1302_readtime();
 
 }

