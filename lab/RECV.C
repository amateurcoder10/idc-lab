#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include<math.h>
#include<stdlib.h>
#include<bios.h>
#define PORT1 0x3F8  /* Port Address Goes Here */
#define INTVECT 0x0C /* Com Port's IRQ here (Must also change PIC setting) */

  /* Defines Serial Ports Base Address */
  /* COM1 0x3F8                        */
  /* COM2 0x2F8			       */
  /* COM3 0x3E8			       */
  /* COM4 0x2E8			       */

int j;
char ch,t[9],bit;

void main(void)
{
 int c,x=0;
 char co;
 outportb(PORT1 + 1 , 0x00);  /* 8 Bits, No Parity, 1 Stop Bit */
 outportb(PORT1 + 2 , 0x00);  /* FIFO Control Register */
 outportb(PORT1 + 4 , 0x00);  /* Turn on DTR, RTS, and OUT2 */
	/*printf("\nLine status %d",inportb(PORT1+5));
	printf("\nModem status %d",inportb(PORT1+4));
	printf("\nLine control %d",inport(PORT1+3));
	printf("\nIER %d",inport(PORT1+1));
	printf("\nIIR %d",inport(PORT1+2));*/


					 /* COM1 (IRQ4) - 0xEF  */
					 /* COM2 (IRQ3) - 0xF7  */
					 /* COM3 (IRQ4) - 0xEF  */
					 /* COM4 (IRQ3) - 0xF7  */

// outportb(PORT1 + 1 , 0x01);  /* Interrupt when data received */

 printf("\nSample Comm's Program. Press ESC to quit \n");
    do{ //transmitt
     if (kbhit()){
		c = getch();
		itoa(c,t,2); //convert to binary
		printf("\nt=%s",t);
		outportb(PORT1+4,0x02);
		delay(30);
		for (j=0;j<8;j++)
			{
			 bit=t[j];
			if (bit=='1')
				{
				outportb(PORT1+4,0x02);
				}
			else if (bit=='0')
				{
				outportb(PORT1+4,0x00);
				}
			}
			outportb(PORT1+4,0x00);
			delay(30);
		}
	  if((inportb(PORT1+6)))
	    {
	for (j=0;j<8;j++)
		{  //printf("here1") ;
	       //	printf("ip=%x",inportb(PORT1+6));
		if((inportb(PORT1+6)&0x10)==16)
			{
			// printf("here") ;
			co=co+pow(2,j);
			x=1;
			}
			delay(31);

		}
		}
		 if(x==1)
		 {
	       //	printf("Attention Train arriving : \n%c",co);
		x=0;

		 }
   }while(c!=27)  ;



}
