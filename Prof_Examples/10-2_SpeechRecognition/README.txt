/*
Libreria adaptada por: Holguer A. Becerra.
Tutorial Escrito por : Holguer A. Becerra. 
Email: Holguer.becerra@upb.edu.co, Hbecerra@ece.ubc.ca, Hbecerradaza@triumf.ca, Adrizcorp@gmail.com

Agradecimientos: 
*/


Pasos para compilar PocketSphinx para ARM-FPGA SoC:

Requisitos, tener en el sistema instalado 

-Quartus Version 15.0
-Eclipse ARM DS-5.0.

Pasos:

1) Descargar el PocketSphinx y sphinxbase desde el GitHub
	git clone https://github.com/Amponti/SpeechRecognition_DE1-SOC/tree/master/PocketSphinx_Prof/ARM_SOC_POCKETSPHINX
	
2) Crear Un proyecto llamado "PocketARMSOCSphinx" en el DS-5, GCC 4.x Arm-Linux-gnueabi(DS-5 built in)

3) Agregar en Propiedades->C/C++ Build->Settings->GCC C Compiler 4 ==> Includes ==> Include paths
los siguientes directorios o las rutas donde se encuentran las librerias del sistema ARM-SOC

"C:\altera\15.0\embedded\ip\altera\hps\altera_hps\hwlib\include"
"C:\altera\15.0\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av\socal"

4) Agregar en Propiedades->C/C++ Build->Settings->GCC C Linker 4 ==> Miscellaneous ==> Linker Flags:

-lm -lpthread

5) Copie las carpetas siguientes en la carpeta del proyecto Eclipse creado.
	include/
	libpocketsphinx/
	sphinxbase/
	
6) copie el archivo Test_programs/batch.c en la carpeta del proyecto eclipse

7) Compilar el proyecto en el DS-5

8) Descargar el modelo de voz en español
	git clone https://github.com/Amponti/SpeechRecognition_DE1-SOC/tree/master/PocketSphinx_Prof/Modelo_De_VoZ_Spanish

9) Ahora copie el archivo ejecutable generado "PocketARMSOCSphinx", en una USB con los archivos ordenados de la siguiente manera
	
	USB:
		voxforge-es-0.2/
		pruebas/
		results/
		PocketARMSOCSphinx

10) usando compandos en el Shell de el ARM usando putty, registre las variables

	ACOU=voxforge-es-0.2/model_parameters/voxforge_es_sphinx.cd_ptm_3000/
	DICT=voxforge-es-0.2/etc/voxforge_es_sphinx1.dic
	LANG=voxforge-es-0.2/etc/voxforge_es_sphinx.transcription.test.lm
	OUTDIR=results

11) Ejecute la aplicacion de la siguiente manera

	#Procesamiento batch de varios archivos wav, usando el modelo del lenguaje.
	./PocketARMSOCSphinx -adcin yes -hmm $ACOU -lm $LANG -dict $DICT -ctl pruebas/grabaciones.txt -cepext .wav -cepdir pruebas -hyp $OUTDIR/salida-con-lm.txt
	
	#Procesamiento batch de varios archivos wav, usando una gramática específica.
	./PocketARMSOCSphinx -adcin yes -hmm $ACOU -jsgf pruebas/gramatica-hola-mundo -dict $DICT -ctl pruebas/grabaciones.txt -cepext .wav -cepdir pruebas -backtrace yes -hyp $OUTDIR/salida-con-gramatica.txt
	
	#Idem pero generando lattices.
	./PocketARMSOCSphinx -adcin yes -hmm $ACOU -lm $LANG -dict $DICT -ctl pruebas/grabaciones.txt -cepext .wav -cepdir pruebas -hyp $OUTDIR/salida-con-lm.txt -outlatdir $OUTDIR/lattices/
	
12) Ahora intente en vez de usar el batch.c use el continuos.c
	



	




