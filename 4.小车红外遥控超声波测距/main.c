/********************************* 深圳市航太电子有限公司 *******************************
* 实 验 名 ：小车红外遥控+超声波测距实验
* 实验说明 ：使用红外小车来控制小车运动,并LCD显示前方的距离
* 实验平台 ：航太ARM单片机开发板
* 连接方式 ：请参考interface.h文件
* 注    意 ：指令必须连续发送才会使小车动作，若停止发送指令，则小车会停止
* 作    者 ：航太电子产品研发部    QQ ：1909197536
* 店    铺 ：http://shop120013844.taobao.com/
****************************************************************************************/
#include "stm32f10x.h"
#include "interface.h"
#include "LCD1602.h"
#include "IRCtrol.h"
#include "motor.h"
#include "UltrasonicCtrol.h"

//全局变量定义
unsigned int speed_count=0;//占空比计数器 50次一周期
char front_left_speed_duty=SPEED_DUTY;
char front_right_speed_duty=SPEED_DUTY;
char behind_left_speed_duty=SPEED_DUTY;
char behind_right_speed_duty=SPEED_DUTY;

unsigned char tick_5ms = 0;//5ms计数器，作为主函数的基本周期
unsigned char tick_1ms = 0;//1ms计数器，作为电机的基本计数器
unsigned char tick_200ms = 0;//刷新显示

char ctrl_comm = 'S';//控制指令
unsigned char continue_time=0;

void InitIO()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE , ENABLE);//使能LED使用的GPIO时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
 GPIO_Init(GPIOE , &GPIO_InitStructure);//将使用LED灯相关的GPIO初始化
 GPIO_SetBits(GPIOE , GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);//关闭所有的ＬＥＤ指示灯
}

int main(void)
{
	delay_init();
	LCD1602Init();
	IRCtrolInit();
	TIM2_Init();
	MotorInit();
	UltraSoundInit();
	ServoInit();
 InitIO();

 while(1)
 {	 
	 		if(tick_5ms >= 5)
		{
			tick_5ms = 0;
			tick_200ms++;
			if(tick_200ms >= 40)
			{
				tick_200ms = 0;
				LEDToggle(GPIO_Pin_8);
				LCD1602WriteDistance(distance_cm);//更新距离
			}
			continue_time--;//200ms 无接收指令就停车
			if(continue_time == 0)
			{
				continue_time = 1;
				CarStop();
			}
			//do something
			Distance();//计算距离
			if(ir_rec_flag == 1)//接收到红外信号
			{
				ir_rec_flag = 0;
				switch(ctrl_comm)
				{
					case COMM_UP:    CarGo();break;
					case COMM_DOWN:  CarBack();break;
					case COMM_LEFT:  CarLeft();break;
					case COMM_RIGHT: CarRight();break;
					case COMM_STOP:  CarStop();break;
					default : break;
				}
				LCD1602WriteCommand(ctrl_comm);
			}
		}
		
 }
}

