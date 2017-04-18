//duplex receiving program for file
#include<bios.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<dos.h>

#define PORT 0x3F8 // Base address
#define Dbyte 20
#define Dbit 10

void main()
{	char ch;
	int cha =0;
	int i,j;
	int flagin=0;
	int flagout=0;
	FILE *fin,*fout;
	clrscr();
	printf("OK");
	outportb(PORT+1,0); // Disable interrupts
	outportb(PORT+2,0); // Disable FIFO registers
	outportb(PORT+4,0x00); // Setting RTS line low

	fin = fopen("input2.txt","r");
	fout=fopen("C:\idc\outfinal.txt","w");
		printf("Press a key to begin");
	while(!kbhit());
	while(1)
		{

		//Transmission
		if(!flagout)
		{
	       //	printf("In transmision \n");
		if((ch =fgetc(fin)) != EOF)
		{

			printf("TX : %c\n",ch);
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
		else
		flagout=1;
		}
		//Rx
		if(!flagin)
		{

		if(inportb(PORT+6)&0x20) // start bit
		{
		 //	printf("In recep \n");
			delay(20); //delay to sync
			for(i=0;i<8;i++)  // take in every bit
			{
				if((inportb(PORT+6)&0x10) == 16)
				cha += pow(2,i);
				delay(10.1);
			}if(cha=='\0') flagin=1;
			fprintf(fout,"%c",cha);
		       delay(20);
		      printf("RX: %c\n",cha);

			cha=0;
		}
		}








		if(flagin&&flagout) break;
		}

ch = '\0';
outportb(PORT+4,0x201); // Start bit
delay(Dbyte);
for(i=0;i<8;i++) // Bitwise transmission
{if((ch & 0x01) == 1)
outportb(PORT+4,0x03);
else outportb(PORT+4,0x01);
ch = ch >> 1;
delay(Dbit);
}
outportb(PORT+4,0x00); // Setting RTS  low
printf("File Transmission done");
fclose(fin);
fprintf(fout,"%c",'\0');
printf("Done receiving");
fclose(fout);
getch();
sleep(5000);
}