
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#define PORT1 0x3F8
/* Defines Serial Ports Base Address */
/* COM1 0x3F8 */
/* COM2 0x2F8 */
/* COM3 0x3E8 */
/* COM4 0x2E8 */
void main(void)
{
int c;
int ch;
outportb(PORT1 + 1 , 0); /* Turn off interrupts - Port1 */

/* PORT 1 - Communication Settings */
outportb(PORT1 + 3 , 0x80); /* SET DLAB ON */
outportb(PORT1 + 0 , 0x03); /* Set Baud rate - Divisor Latch Low Byte */
/* Default 0x03 = 38,400 BPS */
/* 0x01 = 115,200 BPS */
/* 0x02 = 56,700 BPS */
/* 0x06 = 19,200 BPS */
/* 0x0C = 9,600 BPS */
/* 0x18 = 4,800 BPS */
/* 0x30 = 2,400 BPS */
outportb(PORT1 + 1 , 0x00); /* Set Baud rate - Divisor Latch High Byte */
outportb(PORT1 + 3 , 0x03); /* 8 Bits, No Parity, 1 Stop Bit */
outportb(PORT1 + 2 , 0xC7); /* FIFO Control Register */
outportb(PORT1 + 4 , 0x0B); /* Turn on DTR, RTS, and OUT2 */
printf("\nSample Comm's Program. Press ESC to quit \n");
do { c = inportb(PORT1 + 5); /* Check to see if char has been */
/* received. */
if (c & 1) {ch = inportb(PORT1); /* If so, then get Char */
printf("%c",ch);} /* Print Char to Screen */
if (kbhit()){ch = getch(); /* If key pressed, get Char */
outportb(PORT1, ch);
printf("%c",ch);} /* Send Char to Serial Port */
} while (ch !=27); /* Quit when ESC (ASC 27) is pressed */
}