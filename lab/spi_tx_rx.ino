#include <SPI.h>

//char buf [100];
volatile byte pos=0,i=0;
volatile boolean process_it,add;
const char p[15] = "Hello Master";
int add_out;
int num[2];
void setup (void)
{
  Serial.begin (9600);   // debugging
  
  // turn on SPI in slave mode
  SPCR |= bit (SPE);

  // turn on interrupts
  SPCR |= _BV(SPIE);
  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(LSBFIRST);
  
  // get ready for an interrupt 
  pos = 0;   // buffer empty
  process_it = false;

  // now turn on interrupts
  SPI.attachInterrupt();

}  // end of setup


// SPI interrupt routine
ISR (SPI_STC_vect)
{
char c = SPDR;  // grab byte from SPI Data Register

if(c=='+')
{
 add=true;
 Serial.println(c);
//  Serial.println(add);
 
}
else if(c=='=')
{
  Serial.println(c);
  add_out=num[0]+num[1];
  SPDR=add_out;
  Serial.println(add_out);
}
else if(c=='0')
{
 //   for (const char * p = "Hello, world!\n" ; c = *p; p++)
    //SPI.transfer (c);
 Serial.print("Slave sending out..  ");
 Serial.println(p[pos]);
   // Serial.println('U');
    SPDR=p[pos];
  // SPDR='U';
    process_it=true;
}
else if(add==true)
{
  num[i]=c;
   Serial.println(num[i]);
  i++;
  if(i>1)
  {
    i=0;
    add=false;
  }
}
else
{
Serial.print("Slave Receiving...  ");
Serial.println(c);
}
//SPDR='U';//char d= SPI.transfer('U');
//Serial.println("out" + d);
      
}  // end of interrupt routine SPI_STC_vect

// main loop - wait for flag set in interrupt routine
void loop (void)
{
  if (process_it)
    {
      if(pos>11)
      pos=0;
      else
     pos++;
    process_it = false;
    }  // end of flag set
    //else{

    //  SPDR = 'U';
      //delay(1);
   // }
    
}  // end of loop
