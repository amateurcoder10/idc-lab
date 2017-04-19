//#include<unistd.h>		    // Duplex RS232  without rx and tx
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
	char ch,MCR,MSR;//0BIT IS DTR AND 1ST BIT IS RTS
       //	char rx_ch=0;
	int i,j;
	FILE *fin;
	fin = fopen("input.txt","r");
	clrscr();
	outportb(PORT+1,0); // Disable interrupts
	outportb(PORT+2,0); // Disable FIFO registers
	outportb(PORT+4,0x00); // Setting RTS line low

		//Transmission
		while(!kbhit());
			 printf("beginning transmission of input.txt\n");
			while((ch =fgetc(fin)) != EOF)
			{
			//printf("txing %c\n",ch);
			delay(10);
			for(i=0;i<8;i++) // Bit by bit transmission
			{
				if((ch & 0x01) == 1)
				{
				       MCR=0x03;
				       outportb(PORT+4,0x02); //send data using RTS RTS high =1
				     // printf("TX: 1");
				}
				else{
				       MCR=0x01;
				       outportb(PORT+4,0x00);  // RTS low =0
				      //	printf("TX: 0");
				}
				ch = ch >> 1; //Shift to get the next bit

				outportb(PORT+4,MCR);//clock high
				delay(1);
				MCR=MCR & 0xFE;
				outportb(PORT+4,MCR);//clock low
				delay(1);
			}
		}

	printf("transmission done.exiting\n");
	delay(100000);
}