1 #include<lpc21xx.h>
  2 void delay_ms(unsigned int ms)
  3 {
  4         T0PR=15000-1;
  5         T0PC=T0TC=0;
  6         T0TCR=0x02;
  7         T0TCR=0x01;
  8         while(T0TC<ms);
  9         T0TCR=0x00;
 10 }^M
 11 /*void delay_sec(unsigned int sec)
 12 {
 13         T0PR=15000000-1;
 14         T0PC=T0TC=0;
 15         T0TCR=0x02;
 16         T0TCR=0x01;
 17         while(T0TC<sec);
 18         T0TCR=0x00;
 19 } */^M
 20 ^M
 21 void delay_us(unsigned int us)
 22 {
 23         T0PR=60-1;
 24         T0PC=T0TC=0;
 25         T0TCR=0x02;
 26         T0TCR=0x01;
 27         while(T0TC<us);
 28         T0TCR=0x00;
 29 }
 30 

