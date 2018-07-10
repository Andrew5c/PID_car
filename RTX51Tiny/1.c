
/*******************************************************
	task1 : LED0ÿ  1s�ı�һ��״̬
	task2 ��LED1ÿ0.7s�ı�һ��״̬
	task3 ��LED2ÿ0.4s�ı�һ��״̬
	task4 ��LED3ÿ0.2s�ı�һ��״̬
*******************************************************/
//��һ��ʹ�ò���ϵͳ���������������ʹ�ò���ϵͳʵ����û�б�Ҫ��ֻ��Ϊ������һ��
//��Ȼ���˺ܶ���ڷ�ʱ����ϵͳ�ĺô������ǻ��ǵ��Լ���ʵ�ʹ����в�����ᵽ���ĺô�
//ʹ��ǰ��ѡtargetѡ��е�operating system�����rtx51tinyѡ���ʾ��ǰʹ��tinyϵͳ

#include "rtx51tny.h" //tinyϵͳ��ͷ�ļ�
#include "reg52.h"

sbit LED0 = P2^0; 
sbit LED1 = P2^1; 
sbit LED2 = P2^2; 
sbit LED3 = P2^3; 

sbit key4 = P3^3; //���°�������

void init() _task_ 0{  //����ϵͳ�ĳ�ʼ����tinyϵͳ���Ǵ����������ʼִ�У�û��main����

	LED0 = 1;
	LED1 = 1;
	LED2 = 1;
	LED3 = 1;

	os_create_task(1); //����5������
	os_create_task(2);
	os_create_task(3);
	os_create_task(4);
	os_create_task(5);

	os_delete_task(0);	//ɾ���Լ���ʹtask0�˳��������� 
}


void job1() _task_ 1{

	while(1){

		 LED0 = !LED0;
		 os_wait(K_TMO,10,0);//��ʱ��CPU��ʱȥִ�б�ĳ��򣬵�ʱ�䵽���ٻ���ִ�У�	
	}
}

void job2() _task_ 2{

		while(1){

		 LED1 = !LED1;
		 os_wait(K_TMO,8,0);
	
	}
}


void job3() _task_ 3{

	   	while(1){

		 LED2 = !LED2;
		 os_wait(K_TMO,6,0);
	
	}
}


void job4() _task_ 4{

	  	while(1){

		 LED3 = !LED3;
		 os_wait(K_TMO,4,0);
	
	}


}

void job5() _task_ 5{

	while(1){

		  if(key4==0){
		  		LED2 = 1;
				LED3 = 1;
				os_delete_task(3);
				os_delete_task(4);				
		  
		  }	
	}
}



