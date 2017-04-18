#include<stdio.h>
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
{long int c,d;

outportb(PORT+1,0); // Disable interrupts
outportb(PORT+2,0); // Disable FIFO registers
outportb(PORT+4,0x00); // Setting RTS line low

while(1)
{outportb(PORT+4,0x01);
for(c=1;c<=2;c++)
{}
outportb(PORT+4,0x00);
for(c=1;c<=2;c++)
{}
}
}