
//==================
//PID.H
//==================


#ifndef __PID_H
#define	__PID_H


//����������б����������ڵ���
#define PID_DEBUG  1


//PID������Ҫ�Ĳ���
typedef struct pid
{
	 float ref;	 	//ϵͳ�����������趨ֵ 
	 float fdb; 	//ϵͳ���������ķ���ֵ�����Ǵ�����ʵ�ʲ�����ֵ
	 
	 float T;		//��ɢ��ϵͳ�Ĳ�������
	 
	 float KP;		//����ϵ��
	 float KI;		//����ϵ��,= KP*T/Ti
	 float KD;		//΢��ϵ��,= KP*Td/T
	 	 
	 float a0; 		//�������������������
	 float a1;
	 float a2;
	 
	 float error;	//��ǰƫ��			e��k��
	 float error_1; //ǰһ����ƫ��		e��k-1��
	 float error_2; //ǰǰһ����ƫ��	e��k-2��
	 
	 float output;  //pid�����������
	 float output_1;//pid��ǰһ�����
	 
	 float out_max; //�������
	 float out_min; //�������
		 
}PID_value;					 //����һ��PID_value���ͣ�	��ʱPID_valueΪһ���������ͱ�ʶ������������Ϊ�ṹ��

/*
//����pid�������ĳ�ʼֵ��ȫ��0�Ļ�������memset()����
//#define PID_DEFAULTS  {0, 0, \
//	0, 0, 0, \
//	0.0002, \
//	0, 0, 0, \
//	0, 0, 0, \
//	0, 0, 0, 0}
*/


//pid��������
void PID_operation(PID_value *p);
void PID_out(float *real_distance);

float constrain_float(float amt, float low, float high);	//�������޷�
//int constrain_int16(int amt, int low, int high);			//�������޷�

#endif

//========================
//END OF FILE
//========================
