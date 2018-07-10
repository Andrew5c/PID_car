
#include "MAIN.h"

uchar i;
uchar set_flag;
uchar chose_flag;


void set_remind(uchar flag){

		switch(flag){
		case 0:
		  	show_string(0+5,32,"miao");break;//��Ϊ��ʾ��ǰ����λ��
		case 1:
			show_string(0+5,32,"    ");
		  	show_string(0+5,32,"fen");break;//һ��ʼ�����Ǽ�break�ˣ�һ��������ȫ��ѭ��һ�Σ������ͼ�����
		case 2:
		  	show_string(0+5,32,"shi");break;
		case 3:
			show_string(0+5,32,"   ");
		  	show_string(0+5,32,"ri");break;	//ע��������ʾ���ַ�����һ����һ������Ҫˢ�������
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


//*********�ж�����*****
void int0_config(){

   IT0 = 1;//�����ش�����ʽ��1Ϊ�͵�ƽ����
   EX0 = 1;//���ж�����
   EA = 1;//�����ж�

}

//**********�жϽ��뺯��******
/*
���ж���д������ʱ���������������*** WARNING L15: MULTIPLE CALL TO SEGMENT
�����ϲ�֪���������ͦ��Ҫ�ģ����������������жϺ�������ͬʱ������һ����ͬ�ĺ�����ʹ���������˴��룬
�����������ִ���ĸ��ʺܵͣ�����һ�����ִ��󣬽����Ǻ�����Ĵ���
���������1�����Զ�������������ͬ�ĺ��������жϺ�����������ֱ���ã�������Ҫ�ܶ�����ظ�����;
2�����жϺ�����������һ����־��Ȼ������ѭ��������øú���
*/
void int0() interrupt 0{

	 delayms(5);
	 if(k3_set==0){

		 set_flag = ~set_flag;
		 chose_flag = 0;
		 ds1302_init();//���û�����Ļ�����������ֻ�ص�ԭ��������

   }
}

//*********����ѭ��*********
void key_init(){
 
	  	if(k1_chose==0){

			delayms(5);
			if(k1_chose==0){

				chose_flag++;
				set_remind(chose_flag);//��ʾ��ǰ����λ��

				if(chose_flag>=7)
					chose_flag=0;			
			}
			
			while((i<5)&&(k1_chose==0)){
				 delayms(5);
				 i++;			
			}
			 i = 0;
			 //set_remind(chose_flag);//���ѵ�ǰ���õ�λ��		
		}

		if(k2_plus==0){

		   delayms(5);
		   if(k2_plus==0){
		   
		   		init_time[chose_flag]++;
				
				if((init_time[chose_flag]&0x0f) > 9){// ת��ΪBCD��				
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

