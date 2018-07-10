
#ifndef __TEMP_H_
#define __TEMP_H_


sbit DSPORT = P2^6;

void Delay1ms(unsigned int );
unsigned char Ds18b20Init();
void Ds18b20WriteByte(unsigned char com);
unsigned char Ds18b20ReadByte();
void  Ds18b20ChangTemp();
void  Ds18b20ReadTempCom();
void Ds18b20ReadTemp();

#endif


