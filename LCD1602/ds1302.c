
 #include "total.h"

//*******************
void ds1302_writebyte(uchar byte){
	uint i;
	uint t = 0x01;
	for(i=0;i<8;i++){
		SCIO = byte & t;		
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

	CE = 0;	 nop();
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

//*********************
void init_ds1302(){

	 uchar i;
	 CE = 0;   //初始化引脚
	 SCLK = 0; 
	 i  = ds1302_readdata(0x00);  //读取秒寄存器,秒在最低位
	 if((i & 0x80 != 0)){

	 	ds1302_writedata(7,0x00); //撤销写保护，允许写入数据
		for(i = 0;i<7;i++){

			ds1302_writedata(i,init_time[i]);
		}
	 }	
}

//**************
void ds1302_readtime(){	   //读取时间
	  uint i;
	  for(i = 0;i<7;i++){

	  	   init_time[i] = ds1302_readdata(i);
	  }
}

