Comunicacion-Pc-Serial-PIC18f4550
=================================

El objetivo es establecer una comunicación entre el la PC y el PIC18f4550

Desarrollo:

Se utilizaron 3 componentes para establecer una comunicación entre ellos, 
Un PC utilizado como interfaz visual diseñado y programado mediante el lenguaje JAVA, 
Funcionando en la plataforma de escritorio con Sistema Operativo Windows XP. 

Mediante este primer componente se estableció una conexión de salida hacia un 
segundo componente utilizando el canal de comunicación USB(universal Serial Port), 
realizando una programación básica solamente para configurar la velocidad de 
transferencia de 9600 Baudios y realizando el debido manejo de los datos de salida, 
implementando la librería JPICUSB la cual se encarga del manejo del Puerto USB, 

En una pantalla lcd se mostrara el estado de un checkbox, 0 si no estaba seleccionado 
y un 1 si estaba seleccionado.
una vez programada la interfaz visual en el PC, el siguiente paso es Programar los 
PIC mediante el lenguaje C, como segundo componente del sistema se encuentra un 
PIC18F4550 lo llamaremos PICA, en este se codifico lo necesario para realizar el 
enlace de comunicación RS232, configurando en código la velocidad a 9600 Baudios, 
así como definir los Pines Correspondientes para el Receptor RX, y el Transmisor 
TX para así establecer el canal de comunicación para aceptar valores provenientes 
del PC, una vez obtenido el valor , se proceso, para así enviarlo hacia el tercer 
componente PICB Vía RS232, este programado de igual forma mediante el lenguaje C, 
este tercer componente requiere cumplir con la velocidad establecida de 9600 Baudios, 
pero en este caso solamente configurado el puerto RX para recibir información y 
desplegar el numero obtenido mediante LEDS integrados en la tablilla.
