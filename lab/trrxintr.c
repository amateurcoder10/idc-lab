#include <dos.h>
#include <stdio.h>
#include <conio.h>
#define PORT1 0x3F8 /* Port Address Goes Here */

#define INTVECT 0x0C /* Com Port's IRQ here */

int bufferin = 0;
int bufferout = 0;
char ch;
char buffer[1025];
void interrupt (*oldport1isr)();
void interrupt PORT1INT() /* Interrupt Service Routine (ISR) for PORT1 */
{
int c;
do { c = inportb(PORT1 + 5);
if (c & 1) {buffer[bufferin] = inportb(PORT1);

bufferin++;
if (bufferin == 1024) bufferin = 0;}
}while (c & 1);
outportb(0x20,0x20);
}
void main(void)
{
int c;
outportb(PORT1 + 1 , 0); /* Turn off interrupts - Port1 */
oldport1isr = getvect(INTVECT); /* Save old Interrupt Vector for */
/* later recovery */
setvect(INTVECT, PORT1INT); /* Set Interrupt Vector Entry */

outportb(PORT1 + 3 , 0x80); /* SET DLAB ON */
outportb(PORT1 + 0 , 0x03); /* Set Baud rate - Divisor Latch Low Byte */

outportb(PORT1 + 1 , 0x00); /* Set Baud rate - Divisor Latch High Byte */
outportb(PORT1 + 3 , 0x03); /* 8 Bits, No Parity, 1 Stop Bit */
outportb(PORT1 + 2 , 0xC7); /* FIFO Control Register */

outportb(PORT1 + 4 , 0x0B); /* Turn on DTR, RTS, and OUT2 */
outportb(0x21,(inportb(0x21) & 0xEF)); /* Set Programmable Interrupt */

outportb(PORT1 + 1 , 0x01); /* Interrupt when data received */
printf("\nSample Comm's Program. Press ESC to quit \n");
do {
if (bufferin != bufferout){ch = buffer[bufferout];
bufferout++;
if (bufferout == 1024) bufferout = 0;
printf("%c",ch);}
if (kbhit()){c = getch();
outportb(PORT1, c);}
} while (c !=27);
outportb(PORT1 + 1 , 0); /* Turn off interrupts - Port1 */
outportb(0x21,(inportb(0x21) | 0x10)); /* MASK IRQ using PIC */

setvect(INTVECT, oldport1isr); /* Restore old interrupt vector */
}