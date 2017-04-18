#include<stdio.h>
#include<dos.h>
#include<conio.h>
#include <limits.h>

#define P1 0x3F8
#define RTS 0x02
#define DELCTS 0x01

void charToBin (unsigned char c,char *bin)
{
    //char bin[CHAR_BIT + 1] = {0};
    int i;

    for ( i = CHAR_BIT - 1; i >= 0; i-- )
    {
	bin[i] = (c % 2) + '0';
	c /= 2;
    }
    bin[CHAR_BIT] = '\0';
//    printf("\nbin = %s",bin);
    //return bin;
}


int main()
{
int cur_rts;
int x = 1,i = 0,bit = 0;
char exitCh;
int newch = 0;
int count=0;

/* FILE READ*/
	FILE *fs, *ft ;
	char ch ;
	char bin[CHAR_BIT + 1];
	clrscr();

	fs = fopen ("temp.txt", "r" ) ;
	if ( fs == NULL )
	{
	       puts ("Cannot open source file") ;
	       return 0;
	}


cur_rts = RTS;

outportb(P1+4,0x00);

inportb(P1+6);
inportb(P1+6);
while(!(inportb(P1+6)&0x01));
outportb(P1+4,cur_rts);
//printf("\nWriting, CHAR_BIT = %d",CHAR_BIT);

ch = fgetc ( fs ) ;
charToBin(ch,bin);

//printf("First character read = %c, bin[i] = %s\n",ch,bin);
while(1)
{
	if(x || newch == 1)
    {
//	 printf("\nDELTA CTS IS 1");
	 newch = 0;

//       printf("Before Check\n");
       if ( ch == EOF )
	      break ;
       else
       {

	   if(i != CHAR_BIT)
	   {
//		printf("\nbin[i] = %d",bin[i]);
		if(bin[i] == 48)
			bit = 0x00;
		else
			bit = 0x01;


	       if(cur_rts&RTS)
	       {
		    outportb(P1+4,0x02|bit);
//		    printf("Write %d, i = %d\n",bit,i);
	       }
	       else
	       {
		    outportb(P1+4,0x00|bit);
//		    printf("Write %d, i = %d\n",bit,i);
	       }
	       i++;
//	       printf("Inside IF");
	   }
	   else
	   {
	       ch = fgetc ( fs ) ;
	       bin[0] = '\0';
	       charToBin(ch,bin);
//	       printf("\nCharacter read = %c, bin[i] = %s\n",ch,bin);
	       newch = 1;
	       i = 0;
//	       printf("Inside ELSE");
	   }
       }
	  if(!newch)
	  {
//		printf("\nCHECKING RTS");
		if(cur_rts&RTS)
			cur_rts=0x00;
		else
			cur_rts=RTS;

//		printf("\nNegated RTS %d",cur_rts);
	   }
	}

	x=inportb(P1+6)&0x01;
//	if((exitCh = getch()) == 27)
//	break;
}
fclose(fs);

if(cur_rts&RTS)
	outportb(P1+4,0x02);
else
	outportb(P1+4,0x00);

printf("File transfer done");
return 0;
}

