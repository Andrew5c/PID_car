#include "MAIN.h"

//如果不写任何数据，留下的颜色就是花屏，在我的第一版程序里面，总是看到花屏，一直不理解，原来是数据没有写进去的原因。

//对于不变的常量，加上code，存放在rom中，节省ram空间

uchar init_time[] = {0x50,0x54,0x20,0x27,0x10,0x05,0x17}; //秒 分 时 日 月 周 年
//一直显示的
uchar code love[] = {"I Love You"}; //开头空40个像素
uchar code love_1[] = {"No ands,ifs or buts"};

//根据每周显示不同的话
uchar code fresh[] = {"                  "};//用18个空格来刷新留下的字体
uchar code week_fresh[] = {"      "};//6个字节刷新右上角星期区域
uchar code birthday_remind[] = {"Happy Birthday^_^ "};//18
uchar code mon_remind[] = {"New Week,New Star!"}; //18,考虑显示第二句话的时候对上一次的刷新问题，
uchar code tues_remind[] = {"Believe In Yself!  "};//18//把这些话都改成18个字符，就不用刷屏，自动覆盖
uchar code wed_remind_1[] = {"  Sleep When Tired"};//18
uchar code wed_remind_2[] = {"Smile When Awake  "};
uchar code thurs_remind[] = {"With All My Heart "};//18
uchar code fri_remind[] = {"Take Care Of Yself"};
uchar code sat_remind[] = {"Missing You Now..."};
uchar code sun_remind[] = {"Be Happy Everyday!"};

static void display();//显示函数
static void show_week(uint week);//英文周,包括了周提示
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
	  
	  //ds1302_init(); //此时已经把初始化的时间写在了1302里面
	  lcd_init();
	  int0_config();
	  lcd_clear(BACK_COLOR);//不要把刷屏写在while里面，不然会闪烁
	  
	  while(1){

			if(set_flag==0){//正常	  		
				ds1302_readtime();
				show_string(5,32,"    ");//刷新提示区	  
	  		}

			else{//进入中断
				key_init();			
			}

		display();//显示日期和时间
		Ds18b20ReadTemp();//显示温度
	  }
}


//********总的显示函数
static void display(){

	// ds1302_readtime();//读取1302时间

//**********第一行。年 月 日 周********
	 show_number(0+5,0,20,2);  //20**多少年
	 TIME.year = ((init_time[6]&0x70)>>4)*10 + (init_time[6]&0x0f);
	 show_number(16+5,0,TIME.year,2);

	 show_char(32+5,0,'-');

	 TIME.month = ((init_time[4]&0x70)>>4)*10 + (init_time[4]&0x0f);
	 show_number(40+5,0,TIME.month,2);//month

	 show_char(56+5,0,'-');

	 TIME.date = ((init_time[3]&0x70)>>4)*10 + (init_time[3]&0x0f);
	 show_number(62+5,0,TIME.date,2);//date

	 //生日提醒
	 //
	 if((TIME.month==11)&&(TIME.date==4)){
	 		birthday = 1;	 
	 }
	 else 	birthday = 0;

//*********第一行最后，显示星期，英文***
	 TIME.week = ((init_time[5]&0x70)>>4)*10 + (init_time[5]&0x0f);
	 show_week(TIME.week);//根据星期显示英文

//******第二行*******
	 TIME.hour = ((init_time[2]&0x70)>>4)*10 + (init_time[2]&0x0f);
	 show_number(0+5,16,TIME.hour,2);
	 show_morning(TIME.hour);//根据时段显示问候语

	 show_char(16+5,16,':');

	 TIME.minute = ((init_time[1]&0x70)>>4)*10 + (init_time[1]&0x0f);
	 show_number(24+5,16,TIME.minute,2);	 

	 show_char(40+5,16,':');

	 TIME.second = ((init_time[0]&0x70)>>4)*10 + (init_time[0]&0x0f);
	 show_number(48+5,16,TIME.second,2);

//***********第三行*****
	 show_string(40,32,love);

//**********第四行
	 show_string(0,48,love_1);

}


//根据星期显示英文
static void show_week(uint week){

	if(birthday == 1){//生日那天

	 	  show_string(5,64,"LiLi              "); //5行
		  show_string(5,80,birthday_remind);	 //6行
	}

	else
	{

	show_string(5,64,"    ");	//第五行刷新生日留下的lili字体

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
			show_string(16,96,wed_remind_2);break;	//星期三显示两行
		case 4:
			//show_string(102+5,0,week_fresh);
			show_string(102+5,0,"Thur!");
			show_string(5,80,thurs_remind);   //星期四时刷新前一天留下的
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

//*****根据时段显示问候语****
static void show_morning(uint hour){

		switch(hour){

		   case 0:
		   case 1:
		   case 2:
		   case 3:
		   case 4:
		   case 5:
		   		show_string(0+5,112,"Deep Night!^_^    ");break; //凌晨

		   case 6:
		   case 7:
		   case 8:
		   case 9:
		   case 10:
		   case 11:
				 show_string(0+5,112,"Good Morning!^_^  ");break;//早晨

		   case 12:
		   case 13:
		   case 14:
		   case 15:
		   case 16:
		   case 17:
				  show_string(0+5,112,"Good Afternoon!^_^");break;//中午

		   case 18:
		   case 19:
		   case 20:
		   case 21:
		   case 22:
		   		   show_string(0+5,112,"Good Evening!^_^    ");break;//晚上
		
		   default:
		   		  show_string(0+5,112,"Time To Sleep!^_^ ");break;//睡觉	
		}
}


