En este laboratorio vamos a aprender cómo funciona y cómo programar el
microcontrolador PicoCtrl, y así aprender cómo funciona un
microcontrolador.
En cualquier momento, si algo no está claro o si necesita ayuda, no dude
en pedírmela.
Baje el archivo "PicoCtrl_Verilog.zip" del sitio Web. Abra el proyecto
"PicoCtrl.ise", y abra los archivos Verilog "picoctrl_Verilog.v" y
"PicoCtrl_rom32_instructions.v", y mire como están conectados los dos en
el módulo principal "Top_Level_Template_ver1.v". Abra también el archivo
"opcodes.v" (no está en el proyecto pero sí está en el archivo ZIP).
Compile el proyecto y cargue la tarjeta. Mire lo que hacen los LEDs.
Deben hacer el siguiente recorrido con 0.5 segundos entre cada posición:
XXX0 000X
XX0X 00X0
X0XX 0X00
0XXX X000
X0XX 0X00
XX0X 00X0
XXX0 000X
y así sucesivamente, cuando "X" significa encendido y "0" significa
apagado.
El clave de comprender cómo funciona el código es ver qué hay en el
programa (¡¡¡sí, es un programa!!!) en el ROM de las instrucciones, es
decir "PicoCtrl_rom32_instructions.v", y cómo éste controla el
microcontrolador PicoCtrl. Nosotros vamos a mirar este código junto.
Ahora su meta es cambiar el programa para que los LEDs hagan lo que
hicieron en Laboratorio 1 pero ahora con 0.5 segundos entre cada
posición, es decir, hay que cambiar el código de
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