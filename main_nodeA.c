 #include<lpc21xx.h>
  2 #include<stdio.h>
  3 #include "header.h"
  4 
  5 /*
  6 led1 - 0.4
  7 led2 - 0.5
  8 led3 - 0.6
  9 extint0 - p0.16
 10 extint1 - p0.14
 11 extint2 - p0.15
 12 adc(ch_num) - 2
 13 trigger p0.17
 14 echo p0.18
 15 pot -0.28
 16 */
 17 
 18 extern int Left_indicator;
 19 extern int Right_indicator;
 20 extern int Headlight;
 21 
 22 //int Left_indicator = 0;
 23 //int Right_indicator = 0;
 24 //int Headlight = 0;
 25 
 26 #define LED1 (1<<4)
 27  #define LED2 (1<<5)
 28  #define LED3 (1<<6)
 29 
 30 u32 ultrasonic_read(void)
 31 {
 32 u32 time;
 33 IOCLR0=(1<<17);
 34 delay_us(2);
 35 IOSET0=(1<<17);
 36 delay_us(10);
 37 IOCLR0=(1<<17);
 38 //while(!((IOPIN0>>18)&1));
 39 T0PR=60-1;
 40 T0TCR=2;
 41 //T0TCR=1;
 42 //while(((IOPIN0>>18)&1));
 43 T0TCR=0;
 44 time=T0TC;
 45 return (u32)((time*0.0343)/2);
 46 }
 47 CAN1 tx;
 48 
 49 int main()
 50 {
 51         CAN1 tx;
 52         unsigned int adc_value;
 53         int speed;
 54         //float Vout;
 55         //char a[50];
 56   int temperature;
 57 
 58         IODIR0 |= LED1|LED2|LED3|(1<<17);
 59 //      IODIR0 &= ((1<<16)|(1<<14)|(1<<15)|(1<<18));
 60      // IODIR0&=(1<<18);
 61         IOSET0 = LED1|LED2|LED3;
 62 
 63 can1_init();
 64 
 65 adc_init();
 66 //oncfig_ext_int0();
 67 //config_vic_for_ext_int0();
 68 //
 69 //config_ext_int1();
 70 //config_vic_for_ext_int1();
 71 //
 72 //config_ext_int2();
 73 config_vic_for_ext_int2();
 74 
 75 uart0_init(9600);
 76 uart0_tx_string("Vehicle Monitoring System Started\r\n");
 77 while(1)
 78 {
 79 
 80 
 81 adc_value = adc_read(1);
 82 speed=(adc_value*180)/1023; 
 83 uart0_tx_string("\r\n speed:");
 84
 85 adc_value = adc_read(2);
 86 temperature=(adc_value*3.3*100)/1023;
 87 uart0_tx_string("\r\n temperature:");
 88 
 89 tx.id = 0x101;
 90 tx.dlc = 5;
 91 tx.rtr = 0;
 92 tx.ff = 0;
 93 
 94 /* Pack five data bytes */
 95 
 96 tx.byteA = ((unsigned int)speed & 0xFF)
 97          | (((unsigned int)temperature & 0xFF) << 8)
 98          | (((unsigned int)Left_indicator & 0x01) << 14)
 99          | (((unsigned int)Right_indicator & 0x01) << 15)
100                  | (((unsigned int)ultrasonic_read()& 0x3ff)<<18)
101                  |  (((unsigned int)Headlight & 0x01)<<16);
102 //0tx.byteA=100;
103 tx.byteB=0;
104 
105 /* Transmit CAN message */
106                                  uart0_tx_string("\r\nSending CAN message...");
107 
108 can1_tx(tx);
109                                  uart0_tx_string("\r\nCAN transmission completed");
110 
111 //sprintf(a,"\r\n adc_value=%u Vout=%.2f speed=%d kmph temperature=%d Left=%d Right=%d Headlight=%d",adc_value,Vout,speed,temperature,Left_indicator,Right_indicator,Headlight);
112 //uart0_tx_string(a);
113 //delay(500);   
114
115 }
116 }

