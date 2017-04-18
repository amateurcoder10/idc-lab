
#include<bios.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<dos.h>

#define PORT 0x3F8 // Base address


void main()
{
	char c;
	int i,j,i,ch=0;
	clrscr();

	outportb(PORT+1,0); // Disable interrupts
	outportb(PORT+2,0); // Disable FIFO registers
	outportb(PORT+4,0x00); // Setting RTS line low

	while(1)
	{

	

		//receive part
		if(inportb(PORT+6)&0x20) // start bit
		{
			delay(20); //delay to sync
			for(i=0;i<8;i++)  // take in every bit
			{
				if((inportb(PORT+6)&0x10) == 16)
				ch += pow(2,i);
				delay(21);
			}
			printf("%c",ch);
			ch = 0;
		}
	}
}