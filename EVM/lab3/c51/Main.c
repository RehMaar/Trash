#include <reg51.h>
#define con (0x10000-10000)/256;
#define con2 (0x10000-10000)%256;
unsigned int  x, abs; 

void signal_handler() interrupt 0
{
    x = (TL1 + (TH1<<8))*2;
	TL1 = 0;
	TH1 = 0;
}


void time_handler() interrupt 1
{
	TL0 = con2;
	TH0 = con;
   	P3 ^= 0x7F;
}

void main()
{ 
	
	TR0 = 1;	
	IT0 = 1;
	TMOD = 0x91;
	TR1 = 1;	
	ET0 = 1;	
	EX0 = 1;	
	EA = 1;		
	for(;;);
}
