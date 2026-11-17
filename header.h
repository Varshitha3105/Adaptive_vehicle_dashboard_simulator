1 typedef unsigned char u8;
  2 typedef signed char s8;
  3 typedef unsigned int u32;
  4 typedef signed int s32;
  5 
  6 
  7 //extern void delay_sec(unsigned int sec);
  8 extern void delay_us(unsigned int us);
  9 //extern void delay_ms(unsigned int ms);                        
 10 extern void uart0_init(unsigned int baud);
 11 extern void uart0_tx(unsigned char data);
 12 extern unsigned char uart0_rx(void);
 13 extern void uart0_tx_string(char*ptr);
 14 extern void uart0_rx_string(char*prt,int len);
 15 extern void uart0_integer(int num);
 16 extern void adc_init(void);
 17 extern int adc_read(unsigned int ch_num);
 18 extern int adc_speed_read(unsigned int ch_num);
 19 typedef struct CAN1_MSG
 20 {
 21     u32 id;
 22     u32 byteA;
 23     u32 byteB;
 24     u8 rtr;
 25     u8 dlc;
 26     u8 ff;
 27 } CAN1;
 28 extern void can1_init(void);
 29 extern void can1_tx(CAN1 v);
 30 
 31 extern void can1_init(void);
 32 extern int can1_rx(CAN1 *ptr);
 33 
 34 
 35 
 36 
 37 //ext_int_functions
 38 
 39
 40 extern void config_ext_int0(void);
 41 extern void ext_int0_handler(void)__irq;
 42 extern void config_vic_for_ext_int0(void);
 43 
 44 extern void config_ext_int1(void);
 45 extern void ext_int1_handler(void)__irq;
 46 extern void config_vic_for_ext_int1(void);
 47 
 48 extern void config_ext_int2(void);
 49 extern void ext_int2_handler(void)__irq;
 50 extern void config_vic_for_ext_int2(void);
 51 
 52 
 53 
 54
 55 

