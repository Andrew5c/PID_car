//========================
//uart.h
//========================

#ifndef __UART_H
#define	__UART_H

/**********Ϊ������������λ����Э�鶨��ı���****************************/
//cupΪС��ģʽ�洢��Ҳ�����ڴ洢��ʱ�򣬵�λ������0�ֽڣ���λ��1�ֽ�
#define BYTE0(dwTemp)       (*(char *)(&dwTemp))	 //ȡ��int�ͱ����ĵ��ֽ�
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))	 //	ȡ�洢�ڴ˱�����һ�ڴ��ֽڵ����ݣ����ֽ�
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))


void uart_init();  //���ڳ�ʼ��
void uart_send_char(unsigned char _data);	 //����һ���ַ�
void uart_send_string(unsigned char *_data,unsigned char cnt);	//�����ַ���
void uart_send_senser(void);   //6050���ݴ��������λ��Э�鷢�͸���λ��


#endif


//========================
//END OF FILE
//========================
