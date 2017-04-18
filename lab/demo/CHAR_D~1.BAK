// Duplex RS232  without rx and tx
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
	int i,j,c=0;
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
			if(ch == 27) // Exit the program if ESC is pressed
			exit(0);
			printf("%c",ch); //Display character
			outportb(PORT+4,0x01); // Start bit 1 on DTR
			delay(10);
			for(i=0;i<8;i++) // Bit by bit transmission
			{
				if((ch & 0x01) == 1)
					outportb(PORT+4,0x03); //send data using RTS RTS high =1
				else
					outportb(PORT+4,0x01);  // RTS low =0
				ch = ch >> 1; //Shift to get the next bit
				delay(10);
			}
			outportb(PORT+4,0x00); // Set RTS  low after a byte
		      //delay(30);
		}
			//receive part
		if(inportb(PORT+6)&0x20) // MSR : Recieve start bit on DSR
		{
			delay(10);
			for(i=0;i<8;i++)  // Bit by bit
			{
				if((inportb(PORT+6)&0x10) == 0x10) //receive bits from CTS
				c+= pow(2,i);
				delay(11);
			}

			printf("%c",c);
		      //	delay(30);
			c= 0;
		}


	}
}