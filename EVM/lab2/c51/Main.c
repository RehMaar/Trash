#include <reg51.h> 

int_0() interrupt 0
{
 P3 ++;
}

int_2() interrupt 2
{
 P3--;
}

main()
{
 P3=0;
 EX0=1;
 EX1=1;
 IT0=1;
 IT1=1;
 EA=1;
 while(1);
}
