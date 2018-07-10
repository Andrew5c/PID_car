
//=============
//PID.C
//=============

#include "main.h"


#define set_distance 20.00  //设定距离
#define allow_error 2.0	//死区，允许误差带,0.5太小，系统不稳定，一直在调节，2就太大，

extern float real_distance ;	  //实际距离，本体在主函数
extern PID_value  xdata  ASR;	  


/* ********************************************************
** 作者 ：Andrew
** 日期	：2018.3.8    
** 说明 ：
	1、进行PID运算，被PID_out函数调用
	2、使用了条件编译进行功能切换，节省计算时间
	   在校正PID参数的时候，将宏定义 PID_DEBUG 设为1；
	   校正完毕后，置0，直接把计算结果赋值给a
	3、形式和标准PID公式有所差别，但是实质都是一样的，减少了计算量                            
******************************************************** */
void PID_operation(PID_value *p)
{
	
	//使用条件编译进行功能切换
	#if (PID_DEBUG)
		
	float a0,a1,a2;
	
	//计算中间变量a0,a1,a2;
	a0 = p->KP + p->KI*p->T + p->KD/p->T ;
	a1 = p->KP + 2*p->KD/p->T ;
	a2 = p->KD/p->T ;
	//计算输出
	p->output = p->output_1 + a0*p->error - a1*p->error_1 + a2*p->error_2 ;
	
	#else
	//非调试状态下，直接给a赋值计算输出，减小计算量,因为一旦三个系数确定，T已知，即可自己计算出对应的a
	p->output = p->output_1 + p->a0*p->error - p->a1*p->error_1 + p->a2*p->error_2 ;
	
	#endif
	
	//输出限幅
	p->output = constrain_float(p->output,p->out_min,p->out_max);
	
	//为下次计算迭代
	//这里顺序千万不要搞错，不然输出占空比是错误的。
	p->output_1 = p->output;
	p->error_2 = p->error_1;
	p->error_1 = p->error;
	
}

/* ********************************************************
** 作者 ：Andrew
** 日期	：2018.3.8    
** 说明 ：
	1、PID输出函数，被主函数调用
	2、首先根据设定与实际的距离差，判断需要前进还是后退
	3、在误差为	 allow_error 之内，停车，防止小车一直在抖，毕竟超声波有误差。                        
******************************************************** */
void PID_out(float *real_distance)
{
	float xdata duty;					//接收PID运算结果的缓冲
	
	ASR.ref = set_distance;				//距离给定
	ASR.fdb = *real_distance;			//获取实际距离反馈，实际距离一直在不断刷新
	
	ASR.error = ASR.ref - ASR.fdb;		//偏差
	
	PID_operation(&ASR);				//进行PID运算
	
	duty = ASR.output;
	
	if(ASR.error > allow_error)			//偏差为正，设定值大于实际值，后退
	{
		left_go_back;
		right_go_back;
		Left_Forward_Duty = (int)Low_Speed + (int)duty;		//带符号数和无符号数运算会转换为无符号数
		Right_Forward_Duty = Left_Forward_Duty;				//速度一样
	}
	
	else if((-ASR.error) > allow_error)						//偏差为负，设定值小于实际值，前进
	{
		left_go_ahead;
		right_go_ahead;
		Left_Forward_Duty = (int)Low_Speed + (int)duty;
		Right_Forward_Duty = Left_Forward_Duty ;			//速度一样
	}
	
	else			//在误差范围内，停车
		car_stop();
		
}


//浮点数限幅,constrain ->约束，限制
//如果输入不是数字，则返回极端值的平均值
//isnan函数检测输入是否是数字，is not a number
float constrain_float(float amt, float low, float high) 
{
	return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
	
}

/*
//16位整型数限幅
int constrain_int16(int amt, int low, int high)
{
	return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}
*/

//========================
//END OF FILE
//========================
