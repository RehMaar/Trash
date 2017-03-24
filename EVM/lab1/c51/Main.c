#include <reg51.h> 

unsigned char t=0;

int_0() interrupt 3 {
	t++; 
	TH1 = 0x3C; 		         
	TL1 = 0xAF + TL1;
}

main() {
		P3=0;
		P1=0;
		P0=0;
		TMOD = 0x10;
		TH1 = 0x3C; 		        
		TL1 = 0xAF;
		ET1 = 1;
		TR1 = 1;
		EA  = 1;
		while(1) {
				if (t==20) {
					t=0; 
					P1++;
				}
				if (P1==60) {
					P1=0; 
					P0++;
				}
		}
}
