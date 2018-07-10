
//=============
//PID.C
//=============

#include "main.h"


#define set_distance 20.00  //�趨����
#define allow_error 2.0	//��������������,0.5̫С��ϵͳ���ȶ���һֱ�ڵ��ڣ�2��̫��

extern float real_distance ;	  //ʵ�ʾ��룬������������
extern PID_value  xdata  ASR;	  


/* ********************************************************
** ���� ��Andrew
** ����	��2018.3.8    
** ˵�� ��
	1������PID���㣬��PID_out��������
	2��ʹ��������������й����л�����ʡ����ʱ��
	   ��У��PID������ʱ�򣬽��궨�� PID_DEBUG ��Ϊ1��
	   У����Ϻ���0��ֱ�ӰѼ�������ֵ��a
	3����ʽ�ͱ�׼PID��ʽ������𣬵���ʵ�ʶ���һ���ģ������˼�����                            
******************************************************** */
void PID_operation(PID_value *p)
{
	
	//ʹ������������й����л�
	#if (PID_DEBUG)
		
	float a0,a1,a2;
	
	//�����м����a0,a1,a2;
	a0 = p->KP + p->KI*p->T + p->KD/p->T ;
	a1 = p->KP + 2*p->KD/p->T ;
	a2 = p->KD/p->T ;
	//�������
	p->output = p->output_1 + a0*p->error - a1*p->error_1 + a2*p->error_2 ;
	
	#else
	//�ǵ���״̬�£�ֱ�Ӹ�a��ֵ�����������С������,��Ϊһ������ϵ��ȷ����T��֪�������Լ��������Ӧ��a
	p->output = p->output_1 + p->a0*p->error - p->a1*p->error_1 + p->a2*p->error_2 ;
	
	#endif
	
	//����޷�
	p->output = constrain_float(p->output,p->out_min,p->out_max);
	
	//Ϊ�´μ������
	//����˳��ǧ��Ҫ�����Ȼ���ռ�ձ��Ǵ���ġ�
	p->output_1 = p->output;
	p->error_2 = p->error_1;
	p->error_1 = p->error;
	
}

/* ********************************************************
** ���� ��Andrew
** ����	��2018.3.8    
** ˵�� ��
	1��PID���������������������
	2�����ȸ����趨��ʵ�ʵľ����ж���Ҫǰ�����Ǻ���
	3�������Ϊ	 allow_error ֮�ڣ�ͣ������ֹС��һֱ�ڶ����Ͼ�����������                        
******************************************************** */
void PID_out(float *real_distance)
{
	float xdata duty;					//����PID�������Ļ���
	
	ASR.ref = set_distance;				//�������
	ASR.fdb = *real_distance;			//��ȡʵ�ʾ��뷴����ʵ�ʾ���һֱ�ڲ���ˢ��
	
	ASR.error = ASR.ref - ASR.fdb;		//ƫ��
	
	PID_operation(&ASR);				//����PID����
	
	duty = ASR.output;
	
	if(ASR.error > allow_error)			//ƫ��Ϊ�����趨ֵ����ʵ��ֵ������
	{
		left_go_back;
		right_go_back;
		Left_Forward_Duty = (int)Low_Speed + (int)duty;		//�����������޷����������ת��Ϊ�޷�����
		Right_Forward_Duty = Left_Forward_Duty;				//�ٶ�һ��
	}
	
	else if((-ASR.error) > allow_error)						//ƫ��Ϊ�����趨ֵС��ʵ��ֵ��ǰ��
	{
		left_go_ahead;
		right_go_ahead;
		Left_Forward_Duty = (int)Low_Speed + (int)duty;
		Right_Forward_Duty = Left_Forward_Duty ;			//�ٶ�һ��
	}
	
	else			//����Χ�ڣ�ͣ��
		car_stop();
		
}


//�������޷�,constrain ->Լ��������
//������벻�����֣��򷵻ؼ���ֵ��ƽ��ֵ
//isnan������������Ƿ������֣�is not a number
float constrain_float(float amt, float low, float high) 
{
	return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
	
}

/*
//16λ�������޷�
int constrain_int16(int amt, int low, int high)
{
	return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}
*/

//========================
//END OF FILE
//========================
