
#include "main.h"


int main()
{		
	TIME2_UART_Init();

	TIME0_PWM_Init();
	
	//初始化完成后发送提示
	UART_send_string("everything is OK.");
	UART_send_string("be careful.");
	//刚开机要确保电机不转，因为比较危险，当检测到蓝牙连接成功后，给出指示灯提示，并发出连接成功的提示
	
	//一直循环检测串口发送过来的命令
	while(1)
	{
		UART_resieve_analyse();
	}
}

