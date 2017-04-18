#include<stdio.h>
#include<dos.h>
#include<conio.h>
#include <limits.h>
#include<math.h>
#include<string.h>

#define P1 0x3F8
#define RTS 0x02
#define DSR 0x20
#define DELCTS 0x01

char binToChar(char *bitArray)
{
	int decimal = 0;
	int i, digit;
//	printf("\nBitArray = %s",bitArray);
	for(i = CHAR_BIT-1; i >= 0; i--)
	{
		digit =(int)bitArray[i];
		/* where, say, substring(11011, 2) returns 0 */

		if(digit == 1)
			decimal += pow(2,CHAR_BIT - 1 - i);
//		printf("\ndec = %d, bit = %d, i = %d",decimal,bitArray[i],i);
	}
//	printf("\nDecimal = %d",decimal);
	return (char)decimal;
}


int main()
{
int CUR_DSR,CUR_RTS;
int del=1;
int i = 0;
char bitArray[CHAR_BIT+1],letter;
int iBitArray;
FILE *file;
FILE *fp1;
clrscr();

//fp1=fopen("peeyush1.txt","w");
//fclose(fp1);

CUR_RTS = RTS;
inportb(P1+6);

outportb(P1+4,0x00);
outportb(P1+4,RTS); //Raise CTS at receiver so as to set DeltaCTS at sender
printf("\nSignalling Transmitter to send data : %d",CUR_RTS);

while(!(inportb(P1+6)&DELCTS));

printf("\nReading i = %d",i);

while(1)
{

	if(del)
	{
//	  printf("\nDELTA CTS IS ONE, i = %d",i);
	  CUR_DSR = inportb(P1+6)&DSR;

      // form an array of bits
	      if(i != CHAR_BIT)
		{

			if(CUR_DSR)
			{
				bitArray[i] =  1;
//				printf("\n1 , i = %d",i);
			}
			else
			{
				bitArray[i] =  0;
//				printf("\n0 , i = %d",i);
			}

			i++;
		}
		else
		{
			bitArray[i] = '\0';
//			for(i=0;i<CHAR_BIT;i++)
//				printf("\n%d",bitArray[i]);
//			printf("\nWrite to File, bitArray = %s\n",bitArray);
	// Open file in append mode
			file = fopen("C:\\TC\\76.txt","a"); /* apend file*/
			if (file == NULL)
			{
				puts ("Cannot open source file") ;
				return 0;
			}

			letter = binToChar(bitArray);
			fputc(letter,file);
			fclose(file);
//			printf("File close, letter = %c\n",letter);
			bitArray[0] = '\0';
			bitArray[0] = CUR_DSR;
			i = 1;

		}
	  // Negate RTS so as to set DelataCTS at sender
	  if(CUR_RTS&RTS)
		CUR_RTS = 0x00;
	  else
		CUR_RTS = RTS;

	  outportb(P1+4,CUR_RTS);// Signal transmitter for next data
//	  printf("\nRTS Negated : %d",CUR_RTS);
	}
	del = inportb(P1+6)&DELCTS;
//	printf("\nEND");
}
//fclose(file);
return 0;
}
