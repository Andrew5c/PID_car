
#ifndef UART_H
#define UART_H


extern unsigned char CMD_RX_Buffer[20];

void TIME2_UART_Init(void);
//void uart_send_char(unsigned char _data);
void UART_send_string(unsigned char *TX_str);
void UART_resieve_analyse(void);

#endif


