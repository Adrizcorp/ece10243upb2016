En este laboratorio vamos a aprender c�mo funciona y c�mo programar el
microcontrolador PicoCtrl, y as� aprender c�mo funciona un
microcontrolador.
En cualquier momento, si algo no est� claro o si necesita ayuda, no dude
en ped�rmela.
Baje el archivo "PicoCtrl_Verilog.zip" del sitio Web. Abra el proyecto
"PicoCtrl.ise", y abra los archivos Verilog "picoctrl_Verilog.v" y
"PicoCtrl_rom32_instructions.v", y mire como est�n conectados los dos en
el m�dulo principal "Top_Level_Template_ver1.v". Abra tambi�n el archivo
"opcodes.v" (no est� en el proyecto pero s� est� en el archivo ZIP).
Compile el proyecto y cargue la tarjeta. Mire lo que hacen los LEDs.
Deben hacer el siguiente recorrido con 0.5 segundos entre cada posici�n:
XXX0 000X
XX0X 00X0
X0XX 0X00
0XXX X000
X0XX 0X00
XX0X 00X0
XXX0 000X
y as� sucesivamente, cuando "X" significa encendido y "0" significa
apagado.
El clave de comprender c�mo funciona el c�digo es ver qu� hay en el
programa (���s�, es un programa!!!) en el ROM de las instrucciones, es
decir "PicoCtrl_rom32_instructions.v", y c�mo �ste controla el
microcontrolador PicoCtrl. Nosotros vamos a mirar este c�digo junto.
Ahora su meta es cambiar el programa para que los LEDs hagan lo que
hicieron en Laboratorio 1 pero ahora con 0.5 segundos entre cada
posici�n, es decir, hay que cambiar el c�digo de
PicoCtrl_rom32_instructions.v para que los LEDs hagan lo siguiente:
0000 000X
0000 00X0
0000 0X00
0000 X000
000X 0000
00X0 0000
0X00 0000
X000 0000
0X00 0000
00X0 0000
000X 0000
0000 X000
0000 0X00
0000 00X0
0000 000X