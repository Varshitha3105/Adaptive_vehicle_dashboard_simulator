1 #include <LPC21xx.H>
  2 #include "header.h"
  3 
  4 #define TCS ((C1GSR >> 3) & 1)
  5 void can1_init(void)
  6 {
  7     VPBDIV = 1;
  8 
  9     /* Configure CAN1 TX and RX pins */
 10     PINSEL1|=0X00040000;
 11 
 12     C1MOD = 1;
 13     AFMR = 2;
 14 
 15     C1BTR = 0x001C001D;  // 125 Kbps if PCLK = 60 MHz
 16 
 17     C1MOD = 0;
 18 }
 19 
 20 void can1_tx(CAN1 v)
 21 {
 22 uart0_tx_string("\r\ntx start");
 23     C1TID1 = v.id;
 24 
 25     C1TFI1 = (v.dlc << 16);
 26 
 27    // if(v.ff == 1)
 28        // C1TFI1 |= (1U << 31);
 29 
 30     if(v.rtr == 1)
 31         C1TFI1 |= (1U << 30);
 32     else
 33     {
 34         C1TDA1 = v.byteA;
 35         C1TDB1 = v.byteB;
 36     }
 37 
 38     C1CMR = 0x21;
 39 
 40     while(TCS == 0);^M
 41         uart0_tx_string("\r\ntx end");
 42 }

