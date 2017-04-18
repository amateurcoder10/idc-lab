//Transmitting a file without RX and TX   Demo Duplex not accurate and relaiable
#include<bios.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<dos.h>
#define Dbyte 20
 /*DByte delay at 20ms and
 DBit delay at 10ms in Tx and 10.1ms in Rx
 Total speed is 120ms for a character Transmission 67bps and 8bytes per sec*/

#define Dbit 10
#define PORT 0x3F8 // Port address
void main()
{
	char ch;
	int i,j;
	FILE *fin,*fout;
	clrscr();

	outportb(PORT+1,0); // Disable interrupts
	outportb(PORT+2,0); // Disable FIFO registers
	outportb(PORT+4,0x00); // Setting RTS line low
	fin = fopen("input.txt","r");
	fout=fopen("C:\Idc\outfinal.txt","w");
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
		       //	delay(Dbyte); // Setting RTS  low

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
				delay(10.1);
			}if(ch=='\0')break;
			fprintf(fout,"%c",ch);
		       delay(20);
		      printf("%c",ch);

			ch=0;
		}
		}
		fprintf(fout,"%c",'\0');

	break;
	}
printf("File Transmission done\n");
printf("Harry: Done receiving");
fclose(fout);
fclose(fin);
getch();
}