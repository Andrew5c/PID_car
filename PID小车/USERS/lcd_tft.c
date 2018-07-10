
//==================
//LCD_TFT.c
//==================

#include "main.h"

//************д����********
void write_cmd(uchar cmd){	//8λ��������
	CS = 0;	//Ƭѡ���͵�ƽ��Ч
	RS = 0;
	DATA = cmd;
	RW = 0;	   //������д�룿�������ֲ�����û���ҵ���������
	RW = 1;
	CS = 1;		//ȡ��Ƭѡ
}
//*******д����**********
void write_data(uchar dat){

	CS = 0;	//Ƭѡ���͵�ƽ��Ч
	RS = 1;
	DATA = dat;
	RW = 0;	   //������д�룿�������ֲ�����û���ҵ���������
	RW = 1;
	CS = 1;		//ȡ��Ƭѡ
}

//******һ��д��**********
void write_data_16(uint dat){
	write_data(dat>>8);
	write_data(dat);
}

//****LCD��ʼ��
void lcd_init(){

		CS = 1;		 //ȡ��Ƭѡ
		delayms(20);	
		RES = 0;
		delayms(20); //150ms
		RES = 1;	  //��λˢ��
	 	delayms(20); //150ms

	 	write_cmd(0x2A);     //�е�ַ����
        write_data(0x00);    //����ʼ��ַ��8λ
        write_data(0x00);    //����ʼ��ַ��8λ
        write_data(0x00);    //����ֹ��ַ��8λ
		write_data(0x9F);     //����ֹ��ַ��8λ
 						//���������ֹ��ַΪʲô���ó�0x9f��0x9f=ʮ���Ƶ�159��1.8������ķֱ�����128*160.
						//Ҳ����˵��0-159��160�С� �����ͬ���ĵ���ֻ������˵���е���ʼ����ֹ��ַ�� 
 
  		write_cmd(0x2B); //�е�ַ����
        write_data(0x00);
        write_data(0x00);
        write_data(0x00);
		write_data(0x7F); 
 
  		write_cmd(0xCB); //���Ŀ���A 
        write_data(0x39); 
        write_data(0x2C); 
        write_data(0x00); 
        write_data(0x34); 
        write_data(0x02); 
 
   		write_cmd(0xCF);//���Ŀ���B  
        write_data(0x00); 
        write_data(0XC1); 
        write_data(0X30); 
 
        write_cmd(0xE8);//����ʱ�����A  
        write_data(0x85); 
        write_data(0x00); 
        write_data(0x78); 
 
        write_cmd(0xEA);//����ʱ�����B  
        write_data(0x00); 
        write_data(0x00); 
 
        write_cmd(0xED);//��Դ���п���  
        write_data(0x64); 
        write_data(0x03); 
        write_data(0X12); 
        write_data(0X81); 
 
        write_cmd(0xF7); //�ñȿ��� 
        write_data(0x20); 
  
        write_cmd(0xC0);    //Power control ���Ŀ���1
        write_data(0x23);   //VRH[5:0] `
 
        write_cmd(0xC1);    //Power control ���Ŀ���2
        write_data(0x10);   //SAP[2:0];BT[3:0] 
 
        write_cmd(0xC5);    //VCM control 
        write_data(0x3e); //�Աȶȵ���
        write_data(0x28); 
 
        write_cmd(0xC7);    //VCM control2 
        write_data(0x86);  //--
 
        write_cmd(0x36);  // Memory Access Control  �洢�����ʿ���
        write_data(0x68); //C8   //48 68����//28 E8 ����
                           //ccͬc8
 
        write_cmd(0x3A); //���ظ�ʽ����   
        write_data(0x55); 
 
        write_cmd(0xB1);//֡���ʿ���    
        write_data(0x00);  
        write_data(0x18); 
 
        write_cmd(0xB6);    // Display Function Control 
        write_data(0x08); 
        write_data(0x82);
        write_data(0x27);  
 
        write_cmd(0xF2);    // 3Gamma Function Disable 
        write_data(0x00); 
 
        write_cmd(0x26);    //Gamma curve selected 
        write_data(0x01); //��4�����߹�ѡ�񣬷ֱ���1248������ѡ��1��
 
        write_cmd(0xE0);    //Set Gamma 
        write_data(0x0F); 
        write_data(0x31); 
        write_data(0x2B); 
        write_data(0x0C); 
        write_data(0x0E); 
        write_data(0x08); 
        write_data(0x4E); 
        write_data(0xF1); 
        write_data(0x37); 
        write_data(0x07); 
        write_data(0x10); 
        write_data(0x03); 
        write_data(0x0E); 
        write_data(0x09); 
        write_data(0x00); 
 
        write_cmd(0XE1);    //Set Gamma 
        write_data(0x00); 
        write_data(0x0E); 
        write_data(0x14); 
        write_data(0x03); 
        write_data(0x11); 
        write_data(0x07); 
        write_data(0x31); 
        write_data(0xC1); 
        write_data(0x48); 
        write_data(0x08); 
        write_data(0x0F); 
        write_data(0x0C); 
        write_data(0x31); 
        write_data(0x36); 
        write_data(0x0F); 
 
        write_cmd(0x11);    //Exit Sleep 
        delayms(50); 		//120ms
        write_cmd(0x29);    //Display on 
        write_cmd(0x2c); 
}

//д������ʱҪ��ȷ��ͼ�����ʼ����ֹ����
void lcd_setpos(uint x0,uint x1,uint y0,uint y1){

   write_cmd(0x2A);   //�е�ַ����
   write_data(x0>>8);       //����ʼ��ַ��8λ
   write_data(x0);          //����ʼ��ַ��8λ
   write_data(x1>>8);       //����ֹ��ַ��8λ
   write_data(x1);          //����ֹ��ַ��8λ
  
   write_cmd(0x2B);//ҳ��ַ����
   write_data(y0>>8);
   write_data(y0);
   write_data(y1>>8);
   write_data(y1);
   write_cmd(0x2c);//д�洢�� 

}

//****��ʾ��ɫ*******
//void dsp_single_color(uint fount_color,uint back_color){	//ǰ����ɫ��������ɫ,ǰ����ɫ��ʲô������
//	uint i,j;
//	for(i=0;i<160;i++){
//		for(j=0;j<160;j++){
//		 	 write_data(fount_color>>8);
//			 write_data(fount_color);
//			 write_data(back_color>>8);
//			 write_data(back_color); 		
//		}		
//	}
//}


//�����������������
//***********������ȫ����ʾ��ɫ********//���Գɹ�
void lcd_clear(uint lcd_color){

 	 uint i,j;

	 lcd_setpos(0,LCD_WIDE-1,0,LCD_HIGH-1);//ȫ����Χ

	 for(i=0;i<LCD_WIDE;i++){

	 	for(j=0;j<LCD_HIGH;j++){
					   
			write_data_16(lcd_color);	
		}	 
	 }
}

//*************����************* //���Գɹ�
//void draw_point(uint x,uint y,uint point_color){
//
//	 lcd_setpos(x,x,y,y);
//	 write_data_16(point_color);
//}

/*
******ָ��λ����ʾ�����ַ�
******xyλ�ã�numΪ�ַ��� char_colorΪ��ɫ
**���÷�ʽ��
			show_char(5,0,string[0]);
	  		show_char(5,16,'A');
*/
void show_char(uint x,uint y,uchar num){
	  
	  uint pos,temp,t;
	  uint x0 = x;

	  if(x>LCD_WIDE-16 || y>LCD_HIGH-16)return;//��ֹ�������
	  
	  num = num - ' ';//�õ�ƫ�ƺ��ֵ ��,����ȥ����һ��Ļ���û��ƫ��ֵ����ʾ��Ԥ��������but why?

	  lcd_setpos(x,x+8-1,y,y+16-1);	//���ù��λ��

	  for(pos = 0;pos<16;pos++){

	  		temp = 	asc2_1608[(unsigned short)num*16 + pos];

			for(t=0;t<8;t++){	//�������ڱ�����ɫ�������ֳ���Ҫд������壬����������ɫ�뱳����ɫ�غϡ�
				
				if(temp & 0x01)write_data_16(PEN_COLOR);//����������Ҫ��ǰ��ͷ�ļ�����defineһ���ʻ��ͱ�����ɫ����һ�㡣
				else write_data_16(BACK_COLOR);
				temp>>=1;
				x++;			
			}
			x = x0;
			y++;	  
	  }
}
/*
����������ŷţ���һ������ʱ����xֵ�����������ڶ�������������yֵ���������������8��16�����е�ʱ��ڶ���������16
Ϊ�˷�ֹ�ڵ�����һ��������ʼ����5�ȽϺÿ���160-5=155��155/8=19��һ�������ʾ18���ַ�
*/
//*******�ض�λ����ʾ�ַ���******	//�ɹ�
void show_string(uint x,uint y,const uchar *p){

	   while(*p != '\0'){
	   		
			if(x > LCD_WIDE-16){x = 0;y+=16;}
			if(y > LCD_HIGH-16){y = x = 0;}
	   		show_char(x,y,*p) ;
			x+=8;
			p++;
	   }
}

#if 0
//*****
uint my_pow(uchar m,uchar n){

	uchar result = 1;
	while(n--)result*=m;
	return result; 
}


//**********��ʾ����*****
void show_number(uint x,uint y,uint num,uchar len){

	  uint t,temp;
	  for(t=0;t<len;t++){
	  	 temp = (num/my_pow(10,len-t-1))%10;//�Ӹ�λ����λ����ȡ��
	  	 show_char(x+8*t,y,temp+'0');
	  }
}

#endif


//***********��ʱ*************
void delayms(unsigned int tt){
	  int i,j;
	  for(i = 0;i<tt;i++){
	  	  for(j = 0;j<260;j++){
		  	  ;
		  }
	  }
}


//========================
//END OF FILE
//========================

