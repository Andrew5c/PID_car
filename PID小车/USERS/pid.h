
//==================
//PID.H
//==================


#ifndef __PID_H
#define	__PID_H


//条件编译的判别条件，用于调试
#define PID_DEBUG  1


//PID计算需要的参数
typedef struct pid
{
	 float ref;	 	//系统待调节量的设定值 
	 float fdb; 	//系统待调节量的反馈值，就是传感器实际测量的值
	 
	 float T;		//离散化系统的采样周期
	 
	 float KP;		//比例系数
	 float KI;		//积分系数,= KP*T/Ti
	 float KD;		//微分系数,= KP*Td/T
	 	 
	 float a0; 		//变量代替三项的运算结果
	 float a1;
	 float a2;
	 
	 float error;	//当前偏差			e（k）
	 float error_1; //前一步的偏差		e（k-1）
	 float error_2; //前前一步的偏差	e（k-2）
	 
	 float output;  //pid控制器的输出
	 float output_1;//pid的前一步输出
	 
	 float out_max; //输出上限
	 float out_min; //输出下限
		 
}PID_value;					 //定义一个PID_value类型，	此时PID_value为一个数据类型标识符，数据类型为结构体

/*
//定义pid控制器的初始值，全是0的话可以用memset()函数
//#define PID_DEFAULTS  {0, 0, \
//	0, 0, 0, \
//	0.0002, \
//	0, 0, 0, \
//	0, 0, 0, \
//	0, 0, 0, 0}
*/


//pid函数声明
void PID_operation(PID_value *p);
void PID_out(float *real_distance);

float constrain_float(float amt, float low, float high);	//浮点数限幅
//int constrain_int16(int amt, int low, int high);			//整型数限幅

#endif

//========================
//END OF FILE
//========================
