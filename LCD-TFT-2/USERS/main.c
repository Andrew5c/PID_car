#include "MAIN.h"

//�����д�κ����ݣ����µ���ɫ���ǻ��������ҵĵ�һ��������棬���ǿ���������һֱ����⣬ԭ��������û��д��ȥ��ԭ��

//���ڲ���ĳ���������code�������rom�У���ʡram�ռ�

uchar init_time[] = {0x50,0x54,0x20,0x27,0x10,0x05,0x17}; //�� �� ʱ �� �� �� ��
//һֱ��ʾ��
uchar code love[] = {"I Love You"}; //��ͷ��40������
uchar code love_1[] = {"No ands,ifs or buts"};

//����ÿ����ʾ��ͬ�Ļ�
uchar code fresh[] = {"                  "};//��18���ո���ˢ�����µ�����
uchar code week_fresh[] = {"      "};//6���ֽ�ˢ�����Ͻ���������
uchar code birthday_remind[] = {"Happy Birthday^_^ "};//18
uchar code mon_remind[] = {"New Week,New Star!"}; //18,������ʾ�ڶ��仰��ʱ�����һ�ε�ˢ�����⣬
uchar code tues_remind[] = {"Believe In Yself!  "};//18//����Щ�����ĳ�18���ַ����Ͳ���ˢ�����Զ�����
uchar code wed_remind_1[] = {"  Sleep When Tired"};//18
uchar code wed_remind_2[] = {"Smile When Awake  "};
uchar code thurs_remind[] = {"With All My Heart "};//18
uchar code fri_remind[] = {"Take Care Of Yself"};
uchar code sat_remind[] = {"Missing You Now..."};
uchar code sun_remind[] = {"Be Happy Everyday!"};

static void display();//��ʾ����
static void show_week(uint week);//Ӣ����,����������ʾ
static void show_morning(uint hour);
uchar birthday;

struct my_time{

uint second;
uint minute;
uint hour;
uint date;
uint month;
uint week;
uint year;

}TIME;


void main(){
	  
	  //ds1302_init(); //��ʱ�Ѿ��ѳ�ʼ����ʱ��д����1302����
	  lcd_init();
	  int0_config();
	  lcd_clear(BACK_COLOR);//��Ҫ��ˢ��д��while���棬��Ȼ����˸
	  
	  while(1){

			if(set_flag==0){//����	  		
				ds1302_readtime();
				show_string(5,32,"    ");//ˢ����ʾ��	  
	  		}

			else{//�����ж�
				key_init();			
			}

		display();//��ʾ���ں�ʱ��
		Ds18b20ReadTemp();//��ʾ�¶�
	  }
}


//********�ܵ���ʾ����
static void display(){

	// ds1302_readtime();//��ȡ1302ʱ��

//**********��һ�С��� �� �� ��********
	 show_number(0+5,0,20,2);  //20**������
	 TIME.year = ((init_time[6]&0x70)>>4)*10 + (init_time[6]&0x0f);
	 show_number(16+5,0,TIME.year,2);

	 show_char(32+5,0,'-');

	 TIME.month = ((init_time[4]&0x70)>>4)*10 + (init_time[4]&0x0f);
	 show_number(40+5,0,TIME.month,2);//month

	 show_char(56+5,0,'-');

	 TIME.date = ((init_time[3]&0x70)>>4)*10 + (init_time[3]&0x0f);
	 show_number(62+5,0,TIME.date,2);//date

	 //��������
	 //
	 if((TIME.month==11)&&(TIME.date==4)){
	 		birthday = 1;	 
	 }
	 else 	birthday = 0;

//*********��һ�������ʾ���ڣ�Ӣ��***
	 TIME.week = ((init_time[5]&0x70)>>4)*10 + (init_time[5]&0x0f);
	 show_week(TIME.week);//����������ʾӢ��

//******�ڶ���*******
	 TIME.hour = ((init_time[2]&0x70)>>4)*10 + (init_time[2]&0x0f);
	 show_number(0+5,16,TIME.hour,2);
	 show_morning(TIME.hour);//����ʱ����ʾ�ʺ���

	 show_char(16+5,16,':');

	 TIME.minute = ((init_time[1]&0x70)>>4)*10 + (init_time[1]&0x0f);
	 show_number(24+5,16,TIME.minute,2);	 

	 show_char(40+5,16,':');

	 TIME.second = ((init_time[0]&0x70)>>4)*10 + (init_time[0]&0x0f);
	 show_number(48+5,16,TIME.second,2);

//***********������*****
	 show_string(40,32,love);

//**********������
	 show_string(0,48,love_1);

}


//����������ʾӢ��
static void show_week(uint week){

	if(birthday == 1){//��������

	 	  show_string(5,64,"LiLi              "); //5��
		  show_string(5,80,birthday_remind);	 //6��
	}

	else
	{

	show_string(5,64,"    ");	//������ˢ���������µ�lili����

	switch(week){							
	
		case 1:
			//show_string(102+5,0,week_fresh);
			show_string(102+5,0,"Mon!");
			show_string(5,80,mon_remind);break;
		case 2:
			//show_string(102+5,0,week_fresh);
			show_string(102+5,0,"Tues!");
			//show_string(5,80,fresh);
			show_string(5,80,tues_remind);break;
		case 3:
			//show_string(102+5,0,week_fresh);
			show_string(102+5,0,"Wed! ");
			show_string(5,80,wed_remind_1);
			show_string(16,96,wed_remind_2);break;	//��������ʾ����
		case 4:
			//show_string(102+5,0,week_fresh);
			show_string(102+5,0,"Thur!");
			show_string(5,80,thurs_remind);   //������ʱˢ��ǰһ�����µ�
			show_string(5,96,fresh);break;
		case 5:
			show_string(102+5,0,"Fri!  ");
			//show_string(5,80,fresh);
			show_string(5,80,fri_remind);break;
		case 6:
			//show_string(102+5,0,week_fresh);						
			show_string(102+5,0,"Sat!");
			//show_string(5,80,fresh);
			show_string(5,80,sat_remind);break;
		case 7:
			//show_string(102+5,0,week_fresh);
			show_string(102+5,0,"Sun!");
			//show_string(5,80,fresh);
			show_string(5,80,sun_remind);break;
		default: 
			break;
	
	}
	}
}

//*****����ʱ����ʾ�ʺ���****
static void show_morning(uint hour){

		switch(hour){

		   case 0:
		   case 1:
		   case 2:
		   case 3:
		   case 4:
		   case 5:
		   		show_string(0+5,112,"Deep Night!^_^    ");break; //�賿

		   case 6:
		   case 7:
		   case 8:
		   case 9:
		   case 10:
		   case 11:
				 show_string(0+5,112,"Good Morning!^_^  ");break;//�糿

		   case 12:
		   case 13:
		   case 14:
		   case 15:
		   case 16:
		   case 17:
				  show_string(0+5,112,"Good Afternoon!^_^");break;//����

		   case 18:
		   case 19:
		   case 20:
		   case 21:
		   case 22:
		   		   show_string(0+5,112,"Good Evening!^_^    ");break;//����
		
		   default:
		   		  show_string(0+5,112,"Time To Sleep!^_^ ");break;//˯��	
		}
}


