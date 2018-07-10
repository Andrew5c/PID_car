
/*******************************************************
	task1 : LED0每  1s改变一次状态
	task2 ：LED1每0.7s改变一次状态
	task3 ：LED2每0.4s改变一次状态
	task4 ：LED3每0.2s改变一次状态
*******************************************************/
//第一次使用操作系统，在这个程序上面使用操作系统实在是没有必要，只是为了体验一下
//虽然看了很多关于分时操作系统的好处，但是还是得自己在实际工程中才能体会到他的好处
//使用前勾选target选项卡中的operating system里面的rtx51tiny选项，表示当前使用tiny系统

#include "rtx51tny.h" //tiny系统的头文件
#include "reg52.h"

sbit LED0 = P2^0; 
sbit LED1 = P2^1; 
sbit LED2 = P2^2; 
sbit LED3 = P2^3; 

sbit key4 = P3^3; //按下按键，灭

void init() _task_ 0{  //负责系统的初始化，tiny系统总是从这个函数开始执行，没有main函数

	LED0 = 1;
	LED1 = 1;
	LED2 = 1;
	LED3 = 1;

	os_create_task(1); //创建5个任务
	os_create_task(2);
	os_create_task(3);
	os_create_task(4);
	os_create_task(5);

	os_delete_task(0);	//删除自己，使task0退出任务链表 
}


void job1() _task_ 1{

	while(1){

		 LED0 = !LED0;
		 os_wait(K_TMO,10,0);//延时，CPU暂时去执行别的程序，等时间到了再回来执行，	
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



