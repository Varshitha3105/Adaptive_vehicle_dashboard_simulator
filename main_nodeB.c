 #include <LPC21xx.h>
  2 #include <stdio.h>
  3 #include "header.h"
  4 
  5 int main()
  6 {
  7 
  8     CAN1 rx;
  9 
 10     unsigned int speed, temperature , fuel;
 11     unsigned int Left_indicator, Right_indicator, Headlight;
 12     char a[150];
 13    
 14 
 15    can1_init();
 16    uart0_init(9600);
 17   //config_vic_for_ext_int2();
 18    uart0_tx_string("\r\nNode B Receiver Started\r\n");
 19 
 20 
 21     while(1)
 22     {
 23         if(Headlight==1)
 24         Headlight=0;
 25         if(Left_indicator==1)
 26         Left_indicator=0;
 27         if(Right_indicator==1)
 28         Right_indicator=0;
 29         if(can1_rx(&rx))
 30         {
 31             if(rx.id == 0x101 && rx.rtr == 0 && rx.dlc == 5)
 32             {
 33                 speed = rx.byteA & 0xFF;
 34                 temperature = (rx.byteA >> 8) & 0xFF;
 35                         fuel=(rx.byteA >>20 ) &0xFF;
 36                 Left_indicator = (rx.byteA >> 4) & 1;
 37                 Right_indicator = (rx.byteA >> 5) & 1;
 38                 Headlight = (rx.byteB>>6) & 1;
 39 
 40                 sprintf(a,
 41                     "\r\nSpeed = %d kmph"
 42                     "\r\nTemperature = %d C"
 43                                         "\r\nFuel = %d Ltr"
 44                     "\r\nLeft Indicator = %d"
 45                     "\r\nRight Indicator = %d"
 46                     "\r\nHeadlight = %d\r\n",
 47                     speed, temperature, fuel,
 48                     Left_indicator, Right_indicator, Headlight);
 49 
 50                 uart0_tx_string(a);
 51             }
 52         }
 53     }
 54 }

