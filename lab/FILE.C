#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<dos.h>

#include<stdio.h>
void main()
{
	FILE *fin,*fout;
	int c;int ch;
	clrscr();
	fout=fopen("NEW.bmp","w");
       if(!(fin = fopen("TX_Image.bmp","r")))
       {
       printf("error");
       getch();
       exit(1);
       }
	printf("Printing the file \n");
	while((ch = fgetc(fin)) != EOF)
	{

		printf("%d\t", ch);

	fprintf(fout,"%c",ch);
	}
	ch=-1;
	fprintf(fout,"%d",ch);
	fclose(fout);
	printf("End \n");
	getch();
fclose(fin);
}
