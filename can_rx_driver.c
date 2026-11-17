1 #include <LPC21xx.H>
  2 #include "header.h"
  3 
  4 #define TCS ((C1GSR >> 3) & 1)
  5 void can1_init(void)
  6 {
  7     VPBDIV = 1;
  8           PINSEL1|=0x00040000;
  9     C1MOD = 1;
 10     AFMR = 2;
 11         C1BTR = 0x001C001D;  // 125 Kbps if PCLK = 60 MHz
 12         C1MOD = 0;
 13 }
 14 
 15 #define RBS (C1GSR & 1)
 16 int can1_rx(CAN1 *ptr)
 17 {
 18     if(RBS == 0)
 19         return 0;
 20     ptr->id = C1RID;
 21     ptr->dlc = (C1RFS >> 16) & 0x0F;
 22     ptr->rtr = (C1RFS >> 30) & 1;
 23     ptr->ff = (C1RFS >> 31) & 1;
 24 
 25     if(ptr->rtr == 0)
 26     {
 27         ptr->byteA = C1RDA;
 28         ptr->byteB = C1RDB;
 29     }
 30     C1CMR = 0x04;
 31         return 1;
 32 }
 33 

