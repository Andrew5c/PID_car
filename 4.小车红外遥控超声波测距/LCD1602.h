#ifndef  __LCD1602_H_
#define  __LCD1602_H_
#include "stm32f10x.h"

void LCD1602Init(void);
unsigned char LcdWriteString(unsigned char x, unsigned char y, unsigned char *cn);
void ShowEnString(unsigned int x,unsigned int y,unsigned char *str);
void LcdClearScreen(void);
void LCD1602WriteCommand(char comm);
void LCD1602WriteDistance(unsigned int distance);
#endif

