#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
#include<bios.h>
#include<math.h>

#define PORT 0x3F8  //Intializing Base port address
#define DELAY 30    // delay

void main()
{
 char MSR;
 int i;
 char charr;
 char end=1;
outportb(PORT+1,0x00);  //Disable interrupt
outportb(PORT+2,0x00); //disable FIFO register
outportb(PORT+4,0x00); //Setting RTS line low


 while(end)
 {
  charr=0;
  MSR = inportb(PORT+6);//wait for cts// printf("in while");
printf("%c",MSR);
  if(MSR & 0x10 == 0x10)
  {
 printf("HERE");
 delay(10*DELAY);
/*    for(i=0;i<=7;i++)
    {
    delay(DELAY);

    MSR = inportb(PORT + 6);//


     if(MSR & 0x20 == 0x20)//check dsr
     charr = charr | (0x01 << i);
     printf("%d ",charr);
     }*/
    }
if(charr == 27)
{
end = 0;
break;
}
// printf("%c",charr);
   }

printf("Press any key");
getch();
}