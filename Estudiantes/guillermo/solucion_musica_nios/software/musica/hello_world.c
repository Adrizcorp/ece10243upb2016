/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //unix standard
#include <io.h> // I/O Access
#include <system.h>
#define c4 95565
#define d4 85129
#define e4 75842
#define f4 71585
#define g4 63775
#define a4 56817
#define b4 50619
#define c5 47777
#define d5 42565
#define e5 37920
#define f5 35792
#define g5 31887
#define a5 28408
#define b5 25309
#define silence 1

void play_tone(int nota, int time_ms){
	IOWR(DIV_FREQ_BASE,0,nota);
	usleep(time_ms*1000);
}

int main()
{
  play_tone(b4,400);
  play_tone(c5,200);
  play_tone(d5,200);
  play_tone(d5,200);
  play_tone(c5,200);
  play_tone(b4,200);
  play_tone(a4,200);
  play_tone(g4,200);
  play_tone(g4,200);
  play_tone(a4,200);
  play_tone(b4,200);
  play_tone(b4,300);
  play_tone(a4,100);
  play_tone(a4,400);
  play_tone(b4,400);
  play_tone(c5,200);
  play_tone(d5,200);
  play_tone(d5,200);
  play_tone(c5,200);
  play_tone(b4,200);
  play_tone(a4,200);
  play_tone(g4,200);
  play_tone(g4,200);
  play_tone(a4,200);
  play_tone(b4,200);
  play_tone(a4,300);
  play_tone(g4,100);
  play_tone(g4,400);
  play_tone(silence,200);
  play_tone(a4,400);
  play_tone(b4,200);
  play_tone(g4,200);
  play_tone(a4,200);
  play_tone(b4,100);
  play_tone(c5,100);
  play_tone(b4,200);
  play_tone(g4,200);
  play_tone(a4,200);
  play_tone(b4,100);
  play_tone(c5,100);
  play_tone(b4,200);
  play_tone(a4,200);
  play_tone(g4,200);
  play_tone(a4,200);
  play_tone(d4,400);
  play_tone(b4,400);
  play_tone(c5,200);
  play_tone(d5,200);
  play_tone(d5,200);
  play_tone(c5,200);
  play_tone(b4,200);
  play_tone(a4,200);
  play_tone(g4,200);
  play_tone(g4,200);
  play_tone(a4,200);
  play_tone(b4,200);
  play_tone(a4,300);
  play_tone(g4,100);
  play_tone(g4,400);
  play_tone(silence,400);


  return 0;
}
