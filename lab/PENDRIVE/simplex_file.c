//Transmitting a file without RX and TX
#include<bios.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<dos.h>
#define Dbyte 20
#define Dbit 10
#define PORT 0x3F8 // Port address
void main()
{
	char ch;
	int i,j;
	FILE *fin;
	clrscr();

	outportb(PORT+1,0); // Disable interrupts
	outportb(PORT+2,0); // Disable FIFO registers
	outportb(PORT+4,0x00); // Setting RTS line low
	fin = fopen("input2.txt","r");
       //while(!kbhit());
	while(1)
	{
		printf("Press a key for file Transmission");
	       while(!kbhit());

		//Transmission
		while((ch =fgetc(fin)) != EOF)
		{

			//printf("%c",ch);
			outportb(PORT+4,0x01); // Start bit
			delay(Dbyte);
			for(i=0;i<8;i++) // Bitwise transmission
			{
				if((ch & 0x01) == 1)
				outportb(PORT+4,0x03);
				else outportb(PORT+4,0x01);
				ch = ch >> 1;
				delay(Dbit);

			}
			outportb(PORT+4,0x00);
			delay(Dbyte); // Setting RTS  low

		}
			ch = '\0';
			outportb(PORT+4,0x201); // Start bit
			delay(Dbyte);
			for(i=0;i<8;i++) // Bitwise transmission
			{
				if((ch & 0x01) == 1)
				outportb(PORT+4,0x03);
				else outportb(PORT+4,0x01);
				ch = ch >> 1;
				delay(Dbit);

			}
			outportb(PORT+4,0x00); // Setting RTS  low
	break;

	}
	printf("File Transmission done");
	fclose(fin);
}