
#include <18F4550.h>
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN
#use delay(clock=48000000)


#build(reset=0x800)
#build(interrupt=0x808)
#org 0x0000, 0x07ff void bootloader() {}

#define USB_HID_DEVICE FALSE // deshabilitamos el uso de las directivas HID
#define USB_EP1_TX_ENABLE USB_ENABLE_BULK // turn on EP1(EndPoint1) for IN bulk/interrupt transfers
#define USB_EP1_RX_ENABLE USB_ENABLE_BULK // turn on EP1(EndPoint1) for OUT bulk/interrupt transfers
#define USB_EP1_TX_SIZE 32 // size to allocate for the tx endpoint 1 buffer
#define USB_EP1_RX_SIZE 32 // size to allocate for the rx endpoint 1 buffer


#include <pic18_usb.h> // Microchip PIC18Fxx5x Hardware layer for CCS's PIC USB driver
#include "header.h" // Configuración del USB y los descriptores para este dispositivo

#include <usb.c> // handles usb setup tokens and get descriptor reports
#include "LCD416.c"
#define ComandoPC DatosBuffer[0]
#define ParametroPC DatosBuffer[1]
#define TIPO_COMANDO 88
#define LCD_ENABLE_PIN PIN_D1
#define LCD_RS_PIN PIN_D0
const int8 TamBuffer = 32; //Longitud del Buffer de lectura en el puerto USB.

int8 DatosBuffer[TamBuffer];//arreglo de 32 bytes

void main(void) {

  lcd_init();//inicializamos el lcd
  
   setup_adc_ports(AN0|VSS_VDD);
   setup_adc(ADC_CLOCK_DIV_8);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_ccp1(CCP_OFF);
   setup_comparator(NC_NC_NC_NC);
 
   set_tris_d(0x00);
   lcd_gotoxy(1,1) ;
   delay_ms(500);
 
   usb_init(); //inicializamos el USB
   usb_task(); //Se encarga de mantener el  sentido de la comunicación, llama a usb_detach() yusb_attach() cuando se necesita
   usb_wait_for_enumeration(); // Esperamos hasta que el PicUSB sea configurado por el host
   enable_interrupts(global); // Habilitamos todas las interrupciones
 
 while (TRUE){
    if(usb_enumerated()){ //si el PicUSB está configurado
      if (usb_kbhit(1)){//Verifica si se han recibido datos provenientes del PC
      
         usb_get_packet(1, DatosBuffer, TamBuffer); //cogemos el paquete de tamaño 32 bytes(TamBuffer) del EndPoint 1 y Toma los dos bytes 
                                       //que llegan y los guarda en DatosBuffer,y luego son guardos en ComandoPC y ParametroPC respectivamente
        
         if(ComandoPC==TIPO_COMANDO){ //Verifica si el byte 0 (RecCommad) que llega es igual a TIPO_COMANDO = 88
         printf(LCD_PUTC,"%d",ParametroPC);     //imprimimos en el lcd el valor de ParametroPC desde el byte 1 (DatosBuffer)
         delay_ms(1000);
         lcd_gotoxy(1,1) ;
         
        }
      }
    }
  }
}
