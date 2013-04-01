#include "adclcd.h"
#include "LCD416.c"
#define LCD_ENABLE_PIN PIN_D1
#define LCD_RS_PIN PIN_D0

#fuses xt,nomclr,noprotect,nolvp
#use rs232(uart1,baud=9600,xmit=PIN_C6,bits=8,parity=N)
#use standard_io(d)


#use fast_io(b)                     
#use fast_io(a)

#build(reset=0x800)
#build(interrupt=0x808)
#org 0x0000, 0x07ff void bootloader() {}

int boton, x ;
void main()
{
   lcd_init();
  set_uart_speed(9600);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_ccp1(CCP_OFF);
   setup_comparator(NC_NC_NC_NC);
   lcd_gotoxy(1,1) ;
   delay_ms(1000);
   x = 1;
   while(true)
   {     
   
   boton = input( PIN_B5 );
     
     if (boton==0){
             putc(x); 
             printf(LCD_PUTC,"%d",x);    
        delay_ms(1000);
         lcd_gotoxy(1,1) ;
   x++;
   delay_ms(2000);
   
     }
            
   }
}


