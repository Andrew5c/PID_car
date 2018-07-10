
#include "MAIN.h"

uchar i;
uchar set_flag;
uchar chose_flag;


void set_remind(uchar flag){

		switch(flag){
		case 0:
		  	show_string(0+5,32,"miao");break;//作为提示当前设置位数
		case 1:
			show_string(0+5,32,"    ");
		  	show_string(0+5,32,"fen");break;//一开始都忘记加break了，一按按键他全部循环一次！！！低级错误！
		case 2:
		  	show_string(0+5,32,"shi");break;
		case 3:
			show_string(0+5,32,"   ");
		  	show_string(0+5,32,"ri");break;	//注意这里显示的字符比上一个少一个，需要刷新上面的
	    case 4:
		  	show_string(0+5,32,"yue");break;
		case 0+5:
		  	show_string(0+5,32,"zhou");break;
		case 6:
		  	show_string(0+5,32,"nian");break;
		default:
			break;		
		}
}


//*********中断配置*****
void int0_config(){

   IT0 = 1;//跳变沿触发方式，1为低电平触发
   EX0 = 1;//打开中断允许
   EA = 1;//打开总中断

}

//**********中断进入函数******
/*
在中断里写函数的时候，遇到了这个错误，*** WARNING L15: MULTIPLE CALL TO SEGMENT
查资料才知道这个错误还挺重要的，可能在主函数和中断函数里面同时调用了一个相同的函数，使函数发生了从入，
尽管这样出现错误的概率很低，但是一旦出现错误，将会是很讨厌的错误，
解决方法：1、可以定义两个功能相同的函数，在中断和主函数里面分别调用，但是需要很多额外重复函数;
2、在中断函数里面设置一个标志，然后在主循环里面调用该函数
*/
void int0() interrupt 0{

	 delayms(5);
	 if(k3_set==0){

		 set_flag = ~set_flag;
		 chose_flag = 0;
		 ds1302_init();//如果没有这句的话，设置完后又会回到原来的数字

   }
}

//*********按键循环*********
void key_init(){
 
	  	if(k1_chose==0){

			delayms(5);
			if(k1_chose==0){

				chose_flag++;
				set_remind(chose_flag);//提示当前设置位数

				if(chose_flag>=7)
					chose_flag=0;			
			}
			
			while((i<5)&&(k1_chose==0)){
				 delayms(5);
				 i++;			
			}
			 i = 0;
			 //set_remind(chose_flag);//提醒当前设置的位数		
		}

		if(k2_plus==0){

		   delayms(5);
		   if(k2_plus==0){
		   
		   		init_time[chose_flag]++;
				
				if((init_time[chose_flag]&0x0f) > 9){// 转换为BCD码				
				   init_time[chose_flag] = init_time[chose_flag] + 6;
				}

		   		if((chose_flag<2)&&(init_time[chose_flag]>=0x61)){				
				   init_time[chose_flag] = 0;//second and minute 
				}

				if((chose_flag==2)&&(init_time[chose_flag]>=0x24)){				
				   init_time[chose_flag] = 0;//hour
				}

				if((chose_flag==3)&&(init_time[chose_flag]>=0x32)){				
				   init_time[chose_flag] = 1;//date
				}

				if((chose_flag==4)&&(init_time[chose_flag]>=0x13)){				
				   init_time[chose_flag] = 1;//month
				}

				if((chose_flag==5)&&(init_time[chose_flag]>=0x08)){				
				   init_time[chose_flag] = 1;//week
				}

				while((i<5)&&(k2_plus==0)){
				
					delayms(5);
					i++;		
				}
				i = 0;
		   }		
		}
}

