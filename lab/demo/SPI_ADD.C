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
	char ch,a,b,MCR;//0BIT IS DTR AND 1ST BIT IS RTS
	char rx_ch;
	int i,j;
	clrscr();
	outportb(PORT+1,0); // Disable interrupts
	outportb(PORT+2,0); // Disable FIFO registers
	outportb(PORT+4,0x00); // Setting RTS line low
	while(1)
	{
		if(kbhit())
		{
			ch = getch();
			if(ch == 27) // Exit the program if ESC is pressed
			exit(0);

		ch=43;rx_ch=0;
		delay(1);
			for(i=0;i<8;i++) // Bit by bit transmission
			{
				if((ch & 0x01) == 1)
				{
				       MCR=0x03;
				       outportb(PORT+4,0x02); //send data using RTS RTS high =1
				      // printf("1");
				}
				else{
				       MCR=0x01;
				       outportb(PORT+4,0x00);  // RTS low =0
					//printf("0");
				}

				ch = ch >> 1; //Shift to get the next bit//Transmission
			      //	delay(0.000001);
				outportb(PORT+4,MCR);
				delay(1);
				MCR=MCR & 0xFE;
				outportb(PORT+4,MCR);
				delay(1);

			 }
		 printf("enter two numbers\n");
		 scanf("%c %c",&a,&b);
		 fflush(stdin);

			ch = a;
			delay(1);
			for(i=0;i<8;i++) // Bit by bit transmission
			{
				if((ch & 0x01) == 1)
				{
				       MCR=0x03;
				       outportb(PORT+4,0x02); //send data using RTS RTS high =1
				      // printf("1");
				}
				else{
				       MCR=0x01;
				       outportb(PORT+4,0x00);  // RTS low =0
					//printf("0");
				}
				ch = ch >> 1; //Shift to get the next bit

			       //	delay(0.000001);
				outportb(PORT+4,MCR);
				delay(1);
				MCR=MCR & 0xFE;
				outportb(PORT+4,MCR);
				delay(1);}

			ch = b;
			delay(1);
			for(i=0;i<8;i++) // Bit by bit transmission
			{
				if((ch & 0x01) == 1)
				{
				       MCR=0x03;
				       outportb(PORT+4,0x02); //send data using RTS RTS high =1
				      // printf("1");
				}
				else{
				       MCR=0x01;
				       outportb(PORT+4,0x00);  // RTS low =0
					//printf("0");
				}
				ch = ch >> 1; //Shift to get the next bit

			      //	delay(0.000001);
				outportb(PORT+4,MCR);
				delay(1);
				MCR=MCR & 0xFE;
				outportb(PORT+4,MCR);
				delay(1);
			}
			ch=61;
			delay(1);
			for(i=0;i<8;i++) // Bit by bit transmission
			{
				if((ch & 0x01) == 1)
				{
				       MCR=0x03;
				       outportb(PORT+4,0x02); //send data using RTS RTS high =1
				      // printf("1");
				}
				else{
				       MCR=0x01;
				       outportb(PORT+4,0x00);  // RTS low =0
					//printf("0");
				}
				ch = ch >> 1; //Shift to get the next bit

				//delay(1);
				outportb(PORT+4,MCR);
				delay(1);
				MCR=MCR & 0xFE;
				outportb(PORT+4,MCR);
				delay(1);


			}

			ch='U';

				delay(1);
			for(i=0;i<8;i++) // Bit by bit transmission
			{
				if((ch & 0x01) == 1)
				{
				       MCR=0x03;
				       outportb(PORT+4,0x02); //send data using RTS RTS high =1
				      // printf("1");
				}
				else{
				       MCR=0x01;
				       outportb(PORT+4,0x00);  // RTS low =0
					//printf("0");
				}
				ch = ch >> 1; //Shift to get the next bit

			    //	delay(1);
				outportb(PORT+4,MCR);
				delay(1);
				MCR=MCR & 0xFE;
				outportb(PORT+4,MCR);
				delay(1);
					if((inportb(PORT+6) & 0x10) == 0x10)
					{
				      // printf("RX : 1\n");
					rx_ch+=pow(2,i);
					}
					else
					{//printf("RX : 0\n");
					}

					}

			printf("sum is %c\n",rx_ch-'0');
			//outportb(PORT+4,0x00); // Set RTS  low after a byte
		     // delay(30);
		}
       //	 outportb(PORT+4,0X00);

		}
}