
 #include "total.h"

//*******************
void ds1302_writebyte(uchar byte){
	uint i;
	uint t = 0x01;
	for(i=0;i<8;i++){
		SCIO = byte & t;		
		t<<=1;
		DOWN();	   //�½������һ��λ�Ĳ���
	}
	SCIO = 1;//ȷ���ͷ�io����
}
//********************
void ds1302_writedata(uchar addr,uchar data_){
	
	CE = 0;		nop();	
	SCLK = 0;	nop();	
	CE = 1;		nop();	//ʹ��Ƭѡ�ź�
	ds1302_writebyte((addr<<1)|0x80);	//�������д��
	ds1302_writebyte(data_);
	CE = 0;		nop();//�������ݽ���

}
//*************************
uchar ds1302_readbyte(){
	uint i;
	uchar data_ = 0;
	uint t = 0x01;	 
	for(i=0;i<7;i++){	 //c51����֧��ֱ����forѭ������ֱ�Ӷ������

		if(SCIO){

			data_ = data_ | t;	//��λ��ǰ����λ��ȡ,�տ�ʼ���ԣ����������������
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
	 CE = 0;   //��ʼ������
	 SCLK = 0; 
	 i  = ds1302_readdata(0x00);  //��ȡ��Ĵ���,�������λ
	 if((i & 0x80 != 0)){

	 	ds1302_writedata(7,0x00); //����д����������д������
		for(i = 0;i<7;i++){

			ds1302_writedata(i,init_time[i]);
		}
	 }	
}

//**************
void ds1302_readtime(){	   //��ȡʱ��
	  uint i;
	  for(i = 0;i<7;i++){

	  	   init_time[i] = ds1302_readdata(i);
	  }
}

