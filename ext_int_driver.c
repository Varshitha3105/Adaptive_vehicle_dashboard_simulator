  1 #include<lpc21xx.h>
  2 unsigned int Right_indicator=0,Left_indicator=0,Headlight=0;
  3  #define LED1 (1<<4)
  4  #define LED2 (1<<5)
  5  #define LED3 (1<<6)
  6 //void config_ext_int0(void)
  7 //{
  8 // PINSEL1|=1<<0;
  9 // EXTMODE|=0x07;
 10 // EXTPOLAR|=0;   
 11 //}
 12 
 13 void ext_int0_handler(void)__irq{
 14 IOSET0=LED1|LED2;
 15 Headlight^=1;
 16 delay_ms(600);
 17 if(Headlight)
 18 IOCLR0=LED3;
 19 else
 20 IOSET0=LED3;
 21 EXTINT=1<<0;
 22 VICVectAddr=0;
 23 }
 24 
 25 //void config_vic_for_ext_int0(void){
 26 ////VICIntSelect=0;
 27 //VICVectCntl0=14|1<<5;
 28 //VICVectAddr0=(unsigned int)ext_int0_handler;
 29 //VICIntEnable=1<<14;
 30 //}
 31 
 32 //left indicator
 33 
 34 
 35 //void config_ext_int1(void)
 36 //{
 37 // PINSEL0|=1<<29;
 38 // EXTMODE|=0x07;
 39 //EXTPOLAR|=0;   
 40 //}
 41 
 42 void ext_int1_handler(void)__irq{
 43 IOSET0=LED3|LED2;
 44 Left_indicator^=1;
 45 delay_ms(600);
 46 if(Left_indicator){
 47 IOCLR0=LED1;
 48 }
 49 else
 50 {
 51 IOSET0=LED1;
 52 }
 53 EXTINT=1<<1;
 54 VICVectAddr=0;
 55 }
 56 
 57 //void config_vic_for_ext_int1(void){
 58 ////VICIntSelect=0;
 59 //VICVectCntl1=15|1<<5;
 60 //VICVectAddr1=(unsigned int)ext_int1_handler;
 61 //VICIntEnable=1<<15;
 62 //
 63 //}
 64 
 65 //right indicator
 66 
 67 //void config_ext_int2(void)
 68 //{
 69 // PINSEL0|=(unsigned)1<<31;
 70 // EXTMODE|=0X07;
 71 // EXTPOLAR|=0;   
 72 //}
 73 
 74 void ext_int2_handler(void)__irq{
 75 IOSET0=LED1|LED3;
 76 Right_indicator^=1;
 77 delay_ms(600);
 78 if(Right_indicator)
 79 IOCLR0=LED2;
 80 else
 81 IOSET0=LED2;
 82 EXTINT=1<<2;
 83 VICVectAddr=0;
 84 }
 85 
 86 void config_vic_for_ext_int2(void){
 87 VICIntSelect=0;
 88 PINSEL1|=1;
 89 PINSEL0=0XA0000000;
 90 VICVectCntl0=14|1<<5;
 91 VICVectAddr0=(unsigned int)ext_int0_handler;
 92 VICVectCntl1=15|1<<5;
 93 VICVectAddr1=(unsigned int)ext_int1_handler;
 94 VICVectCntl2=16|1<<5;
 95 VICVectAddr2=(unsigned int)ext_int2_handler;
 96 VICIntEnable=7<<14;
 97 EXTMODE=7;

