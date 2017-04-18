// Transmitter simplex.c
#include<bios.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<dos.h>

#define PORT 0x3F8 // Port address


void main()
{
	char ch;
	int i,j;
	clrscr();

	outportb(PORT+1,0); // Disable interrupts
	outportb(PORT+2,0); // Disable FIFO registers
	outportb(PORT+4,0x00); // Setting RTS line low

	while(1)
	{

		//Transmission
		if(kbhit())
		{
			ch = getch();

			printf("%c",ch);
			outportb(PORT+4,0x01); // Start bit 
			delay(20);
			for(i=0;i<8;i++) // Bitwise transmission
			{
				if((ch & 0x01) == 1)
				outportb(PORT+4,0x03);
				else outportb(PORT+4,0x01);
				ch = ch >> 1;
				delay(20);
				//outportb(PORT + 4 ,0x00);
			      
				//	printf("%d",i);
				//delay(30);
			}
			outportb(PORT+4,0x00); // Setting RTS  low
		}

		
	}
}