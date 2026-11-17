1 #include<lpc21xx.h>
  2 void uart0_init(unsigned int baud)
  3 {
  4 int pclk,result=0;
  5 int a[]={15,60,30,0,15};^M
  6 VPBDIV=1;
  7 pclk=a[VPBDIV]*1000000;
  8 result=pclk/(16*baud);
  9 PINSEL0|=0x05;
 10 U0LCR=0x83;
 11 U0DLL=(result&0xff);
 12 U0DLM=(result>>8)&0xff;
 13 U0LCR=0x03;
 14 }
 15 
 16 // transmit data
 17 #define THRE ((U0LSR>>5)&1)
 18 void uart0_tx(unsigned char data)
 19 {
 20 U0THR=data;
 21 while(THRE==0);^M
 22 
 23 }
 24 
 25 //Receive data
 26 #define RDR (U0LSR&1)
 27 unsigned char uart0_rx()
 28 {
 29 while(RDR==0);
 30 return U0RBR;
 31 }
 32 
 33 //tx_string
 34 void uart0_tx_string(char*ptr)
 35 {
 36 while(*ptr!=0)
 37 {
 38 uart0_tx(*ptr);
 39 ptr++;
 40 }
 41 }
 42 
 43 //rx_strig
 44 void uart0_rx_string(char*ptr,int len)
 45 {
 46 int i;
 47 for(i=0;i<len;i++)
 48 {
 49 while(RDR==0);
 50 ptr[i]=U0RBR;
 51 if(ptr[i]=='\r')
 52 break;
 53 }
 54 ptr[i]='\0';
 55 }
 56 
 57 //integer function
 58 void uart0_integer(int num)
 59 {
 60 int a[10],i=0;
 61 if(num==0)
 62 {
 63 uart0_tx('0');^M
 64 return;
 65 }
 66 if(num<0)
 67 {
 68 num=-num;
 69 uart0_tx('-');
 70 }
 71 while(num>0)
 72 {
 73 a[i]=num%10+48;
 74 num=num/10;
 75 i++;
 76 }
 77 for(i=i-1;i>=0;i--)
 78 {
 79 uart0_tx(a[i]);
 80 }
 81 }

