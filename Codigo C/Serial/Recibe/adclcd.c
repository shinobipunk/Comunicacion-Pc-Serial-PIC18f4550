#include "adclcd.h"
int sre = 0; 
//Variables para desplegar el dato recibido 
#use rs232(baud=9600, xmit=pin_c6,rcv=pin_c7,parity=N)
//Directiva para el uso del puerto serie 


#build(reset=0x800)
#build(interrupt=0x808)
#org 0x0000, 0x07ff void bootloader() {}


#int_RDA 
RDA_isr() //Vector de subrutina de servicio
{ sre = getc ();
//Guarda el valor del dato recibido 
return sre;
//Regresa el valor del dato recibido 
} 
void main() 
{ 
setup_adc_ports(NO_ANALOGS|VSS_VDD); 
//setup_adc(ADC_OFF|ADC_TAD_MUL_0); 
setup_psp(PSP_DISABLED); 
setup_spi(FALSE); setup_wdt(WDT_OFF); 
setup_timer_0(RTCC_INTERNAL); 
setup_timer_1(T1_DISABLED); 
setup_timer_2(T2_DISABLED,0,1); 
setup_comparator(NC_NC_NC_NC); 
setup_vref(FALSE); enable_interrupts(INT_RDA); enable_interrupts(GLOBAL); 
setup_oscillator(OSC_8MHZ|OSC_TIMER1|OSC_31250|OSC_PLL_OFF); 

set_uart_speed (9600); //Configura la velocidad de transferencia 
set_tris_d (0x00); //Configura el puerto D como salida 
printf("Conexion Exitosa"); //Envia una cadena de caracteres para comprobar conexion 

while (1) { 
   output_D(sre); // Se pone en 1 el bit 7 del puerto D para el control de los displays
   delay_ms(25); //Retardo de 25 mS 
  
} 
}
