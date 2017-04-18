//#include<unistd.h>				// Duplex RS232  without rx and tx
#include<bios.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<time.h>
#include<dos.h>
#define PORT 0x3F8 // Port address
void main()
{
	char ch,MCR;//0BIT IS DTR AND 1ST BIT IS RTS
	char rx_ch=0;
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
			if(ch == 27) // Exit the program if ESC is pressed
			exit(0);
			//if(ch == '0')

			printf("tx %c\n",ch); //Display character
			//outportb(PORT+4,0x01); // DTR is clock and RTS is data
			delay(1);
			for(i=0;i<8;i++) // Bit by bit transmission
			{
				if((ch & 0x01) == 1)
				{
				       MCR=0x03;
				       outportb(PORT+4,0x02); //send data using RTS RTS high =1
				      printf("TX: 1");
				}
				else{
				       MCR=0x01;
				       outportb(PORT+4,0x00);  // RTS low =0
					printf("TX: 0");
				}
				ch = ch >> 1; //Shift to get the next bit
				//delay(100);
				outportb(PORT+4,MCR);//clock high


				delay(1);
				MCR=MCR & 0xFE;
					if(inportb(PORT+6) & 0x10 == 0x10)
					{
				       printf("RX : 1\n");
					rx_ch+=pow(2,i);
					}
					else
					{printf("RX : 0\n");
					}
				outportb(PORT+4,MCR);//clock low
				delay(1);
			}
			//outportb(PORT+4,0x00); // Set RTS  low after a byte
		     // delay(30);
		     printf("rx %c\n",rx_ch);
		     rx_ch=0;
		}
       //	 outportb(PORT+4,0X00);

	}
}