#include<conio.h>
#include<stdio.h>

void main()
{int j=0,i;
clrscr();
unsigned char ch=0;
	for(i=0;i<8;i++)
       {

	j=j^1;
	if(j)
	//read cts
	//printf("%d",c);
	ch=(0x01<<i)|ch;
	printf("j is %d ch is %d\n",j,ch);

	}
	printf("character is %d",ch);
	      getch();
	}
