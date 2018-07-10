
#include "main.h"


/*10us*/
 void delay_10us(uint x)//12MHZ
{
	uint y;
	for(y=x;y>0;y--){

	   _nop_();
	   _nop_();
	   _nop_();
	   _nop_();
	   _nop_();
	   _nop_();	
	}
} 

#if 0
/*1ms*/
 void delay_1ms(uint x) //ÑÓÊ±XºÁÃë
{
	uint y,z;

	for(z=x;z>0;z--)
		for(y=114;y>0;y--);
}


/*500ms*/
void delay_500ms(uint x)
{	
	unsigned char i,j,k,l;

	for(l=x;l>0;l--)
		for(i=15;i>0;i--)
		     for(j=202;j>0;j--)
		         for(k=81;k>0;k--);
}

#endif


//========================
//END OF FILE
//========================

