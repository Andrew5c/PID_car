
//==================
//LCD_TFT.c
//==================

#include "main.h"

//************写命令********
void write_cmd(uchar cmd){	//8位二进制数
	CS = 0;	//片选，低电平有效
	RS = 0;
	DATA = cmd;
	RW = 0;	   //上升沿写入？在数据手册里面没有找到啊！！！
	RW = 1;
	CS = 1;		//取消片选
}
//*******写数据**********
void write_data(uchar dat){

	CS = 0;	//片选，低电平有效
	RS = 1;
	DATA = dat;
	RW = 0;	   //上升沿写入？在数据手册里面没有找到啊！！！
	RW = 1;
	CS = 1;		//取消片选
}

//******一次写入**********
void write_data_16(uint dat){
	write_data(dat>>8);
	write_data(dat);
}

//****LCD初始化
void lcd_init(){

		CS = 1;		 //取消片选
		delayms(20);	
		RES = 0;
		delayms(20); //150ms
		RES = 1;	  //复位刷新
	 	delayms(20); //150ms

	 	write_cmd(0x2A);     //列地址设置
        write_data(0x00);    //列起始地址低8位
        write_data(0x00);    //列起始地址高8位
        write_data(0x00);    //列终止地址高8位
		write_data(0x9F);     //列终止地址低8位
 						//上面的列终止地址为什么设置成0x9f，0x9f=十进制的159，1.8寸的屏的分辨率是128*160.
						//也就是说有0-159共160列。 下面的同样的道理，只不过是说明行的起始和终止地址。 
 
  		write_cmd(0x2B); //行地址设置
        write_data(0x00);
        write_data(0x00);
        write_data(0x00);
		write_data(0x7F); 
 
  		write_cmd(0xCB); //功耗控制A 
        write_data(0x39); 
        write_data(0x2C); 
        write_data(0x00); 
        write_data(0x34); 
        write_data(0x02); 
 
   		write_cmd(0xCF);//功耗控制B  
        write_data(0x00); 
        write_data(0XC1); 
        write_data(0X30); 
 
        write_cmd(0xE8);//驱动时序控制A  
        write_data(0x85); 
        write_data(0x00); 
        write_data(0x78); 
 
        write_cmd(0xEA);//驱动时序控制B  
        write_data(0x00); 
        write_data(0x00); 
 
        write_cmd(0xED);//电源序列控制  
        write_data(0x64); 
        write_data(0x03); 
        write_data(0X12); 
        write_data(0X81); 
 
        write_cmd(0xF7); //泵比控制 
        write_data(0x20); 
  
        write_cmd(0xC0);    //Power control 功耗控制1
        write_data(0x23);   //VRH[5:0] `
 
        write_cmd(0xC1);    //Power control 功耗控制2
        write_data(0x10);   //SAP[2:0];BT[3:0] 
 
        write_cmd(0xC5);    //VCM control 
        write_data(0x3e); //对比度调节
        write_data(0x28); 
 
        write_cmd(0xC7);    //VCM control2 
        write_data(0x86);  //--
 
        write_cmd(0x36);  // Memory Access Control  存储器访问控制
        write_data(0x68); //C8   //48 68竖屏//28 E8 横屏
                           //cc同c8
 
        write_cmd(0x3A); //像素格式设置   
        write_data(0x55); 
 
        write_cmd(0xB1);//帧速率控制    
        write_data(0x00);  
        write_data(0x18); 
 
        write_cmd(0xB6);    // Display Function Control 
        write_data(0x08); 
        write_data(0x82);
        write_data(0x27);  
 
        write_cmd(0xF2);    // 3Gamma Function Disable 
        write_data(0x00); 
 
        write_cmd(0x26);    //Gamma curve selected 
        write_data(0x01); //共4条曲线供选择，分别是1248；这里选择1，
 
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

//写入数据时要先确定图像的起始和终止坐标
void lcd_setpos(uint x0,uint x1,uint y0,uint y1){

   write_cmd(0x2A);   //列地址设置
   write_data(x0>>8);       //列起始地址高8位
   write_data(x0);          //列起始地址低8位
   write_data(x1>>8);       //列终止地址高8位
   write_data(x1);          //列终止地址低8位
  
   write_cmd(0x2B);//页地址设置
   write_data(y0>>8);
   write_data(y0);
   write_data(y1>>8);
   write_data(y1);
   write_cmd(0x2c);//写存储器 

}

//****显示颜色*******
//void dsp_single_color(uint fount_color,uint back_color){	//前景颜色，背景颜色,前景颜色是什么东东？
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


//把上面两个函数结合
//***********就是在全屏显示颜色********//调试成功
void lcd_clear(uint lcd_color){

 	 uint i,j;

	 lcd_setpos(0,LCD_WIDE-1,0,LCD_HIGH-1);//全屏范围

	 for(i=0;i<LCD_WIDE;i++){

	 	for(j=0;j<LCD_HIGH;j++){
					   
			write_data_16(lcd_color);	
		}	 
	 }
}

//*************画点************* //调试成功
//void draw_point(uint x,uint y,uint point_color){
//
//	 lcd_setpos(x,x,y,y);
//	 write_data_16(point_color);
//}

/*
******指定位置显示单个字符
******xy位置，num为字符， char_color为颜色
**调用方式：
			show_char(5,0,string[0]);
	  		show_char(5,16,'A');
*/
void show_char(uint x,uint y,uchar num){
	  
	  uint pos,temp,t;
	  uint x0 = x;

	  if(x>LCD_WIDE-16 || y>LCD_HIGH-16)return;//防止字体过大
	  
	  num = num - ' ';//得到偏移后的值 ？,但是去掉这一句的话，没有偏移值，显示和预订不符，but why?

	  lcd_setpos(x,x+8-1,y,y+16-1);	//设置光标位置

	  for(pos = 0;pos<16;pos++){

	  		temp = 	asc2_1608[(unsigned short)num*16 + pos];

			for(t=0;t<8;t++){	//下面是在背景颜色上面区分出需要写入的字体，避免字体颜色与背景颜色重合。
				
				if(temp & 0x01)write_data_16(PEN_COLOR);//看来还是需要提前在头文件里面define一个笔画和背景颜色方便一点。
				else write_data_16(BACK_COLOR);
				temp>>=1;
				x++;			
			}
			x = x0;
			y++;	  
	  }
}
/*
如果把屏横着放，第一个参数时向右x值的增加量，第二个参数是向下y值的增加量，字体宽8高16，换行的时候第二个参数加16
为了防止遮挡，第一个参数开始设置5比较好看，160-5=155，155/8=19，一行最多显示18个字符
*/
//*******特定位置显示字符串******	//成功
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


//**********显示数字*****
void show_number(uint x,uint y,uint num,uchar len){

	  uint t,temp;
	  for(t=0;t<len;t++){
	  	 temp = (num/my_pow(10,len-t-1))%10;//从高位到低位依次取出
	  	 show_char(x+8*t,y,temp+'0');
	  }
}

#endif


//***********延时*************
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

