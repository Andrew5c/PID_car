
#include "MAIN.h"

//*******************
void ds1302_writebyte(uchar byte_1){
	uchar i;
	uchar t = 0x01;
	for(i=0;i<8;i++){
		SCIO = byte_1 & t;		
		t<<=1;
		DOWN();	   //下降沿完成一个位的操作
	}
	SCIO = 1;//确保释放io引脚
}
//********************
void ds1302_writedata(uchar addr,uchar data_){
	
	CE = 0;		nop();	
	SCLK = 0;	nop();	
	CE = 1;		nop();	//使能片选信号
	ds1302_writebyte((addr<<1)|0x80);	//方便后面写入
	ds1302_writebyte(data_);
	CE = 0;		nop();//传送数据结束

}
//*************************
uchar ds1302_readbyte(){
	uint i;
	uchar data_ = 0;
	uint t = 0x01;	 
	for(i=0;i<7;i++){	 //c51好像不支持直接在for循环里面直接定义变量

		if(SCIO){

			data_ = data_ | t;	//低位在前，逐位读取,刚开始不对，估计是这个的问题
		}				
		t<<=1;
		DOWN();
	}
	 return data_;
}


//************************
uchar ds1302_readdata(uchar addr){

	uchar data_ = 0;

	CE = 0;	 	nop();
	SCLK = 0;  nop();
	CE = 1;	  nop();
	ds1302_writebyte((addr<<1)|0x81);
	data_ = ds1302_readbyte();
	CE = 0;	   nop();
	SCLK = 1;  nop();
	SCIO = 0;  nop();
	SCIO = 1;  nop();

	return data_;
}

/*
有时候设置完时间发现再按下设置按键后，又回到原来的时间，根本没有按照设置的时间来，这个时候就要检查一下备用电源的接触问题
还有就是有没有在中断函数里面写入初始化函数，因为通过初始化操作把设置好的时间再次写入寄存器。
还有一个问题就是每次断电后重新启动时，发现每次都是回到原来设置的时间，这是因为代码问题，每次上电都是重新运行程序，
重新进行1302的初始化，重新写入初始化时间的，所以每次都是原来的时间。
解决方法：第一次下载程序的时候写入初始化，然后在主函数里删除初始化，到现在实验没有问题。还有方法就是下面加上的初始化判断。

*/
void ds1302_init(){

	 uchar i;
	 CE = 0;   //初始化引脚
	 SCLK = 0; 

	 i  = ds1302_readdata(0x00);  //读取秒寄存器,
	 											
	 if((i & 0x80 != 0)){			//通过判断秒寄存器是否还有数据来决定下次上电的时候是否初始化时间，就是掉电保护

	 	ds1302_writedata(7,0x00); //撤销写保护，允许写入数据

		for(i = 0;i<7;i++){

			ds1302_writedata(i,init_time[i]);
		}
	 }
	 	ds1302_writedata(7,0x80);//打开写保护功能，防止干扰造成的数据写入。	
}

//**************
void ds1302_readtime(){	   //读取时间
	  uint i;
	  for(i = 0;i<7;i++){

	  	   init_time[i] = ds1302_readdata(i);
	  }
}

