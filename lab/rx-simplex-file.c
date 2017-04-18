//simplex receiving program for file
#include<bios.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<dos.h>

#define PORT 0x3F8 // Base address
#define d 100

void main()
{
	char c;
	int i,j,ch=0;
	FILE *fout;
	clrscr();

	outportb(PORT+1,0); // Disable interrupts
	outportb(PORT+2,0); // Disable FIFO registers
	outportb(PORT+4,0x00); // Setting RTS line low

	fout=fopen("D:\outfinal.txt","w");
	while(1)
	{
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
printf("Done receiving");
fclose(fout);
getch();
}