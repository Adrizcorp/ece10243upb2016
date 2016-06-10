
1) Download and install the Arduino IDE for your operating system. Versions 1.6.4 or later. If you already have a recent version there's no need to reinstall the IDE. 

2) Start Arduino IDE. Select pull down menu File->Preferences 
Enter automatic installation URL in the field: 
Additional Boards Manager URLs 
http://www.nxlab.fer.hr/fpgarduino/package_f32c_core_index.json 

3) Select pull down menu Tools->Board->Boards Manager 
scroll down, find FPGArduino, click it and click "Install" 

4) Optionally you may need to install libusb using Zadig(http://zadig.akeo.ie/)

Luego

Seleccionar la tarjeta en Tools->boards-> DE0-NANO
y seleccionar la arquitectura MIPS y programar por medio del cable serial conectado

y en Tools->boot-programmer-> ujtag(FPGAarduino)