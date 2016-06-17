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

#define C3 130
#define Db3 138
#define D3 146
#define Eb3 155
#define E3 164
#define F3 174
#define Gb3 185
#define G3 196
#define Ab3 207
#define A3 220
#define Bb3 233
#define B3 246

#define C4 95784.44
#define Db4 90251.70
#define D4 85323.23
#define Eb4 80384.85
#define E4 75986.84
#define F4 71632.23
#define Gb4 67749.67
#define G4 63774.51
#define Ab4 60239.96
#define A4 56817.18
#define Bb4 53647.06
#define B4 50708.93

#define C5 52347800.14
#define Db5 45954.88
#define D5 42588.43
#define Eb5 40191.92
#define E5 37935.26
#define F5 35815.61
#define Gb5 33828.49
#define G5 31927.48
#define Ab5 30119.48
#define A5 28408.09
#define Bb5 26823.03
#define B5 25328.28

#define C6 23899.57
#define Db6 22562.17
#define D6 21293.71
#define Eb6 20095.46
#define E6 18967.13
#define F6 17907.30
#define Gb6 16902.31
#define G6 15953.05
#define Ab6 15050.17
#define A6 14203.54
#define Bb6 13411.01
#define B6 12657.22

#define C7 2093
#define Db7 2217
#define D7 2349
#define Eb7 2489
#define E7 2637
#define F7 2794
#define Gb7 2960
#define G7 3136
#define Ab7 3322
#define A7 3520
#define Bb7 3729
#define B7 3951
#define silencie 1

void play_tone_tetris(int nota,int time_ms){

	IOWR(DIV_FREQ_BASE,0,nota);
	usleep(time_ms*1000);
}


int main()
{
	play_tone_tetris(E5, 125);
	play_tone_tetris(E6, 500);
	play_tone_tetris(B5, 250);
	play_tone_tetris(C6, 250);
	play_tone_tetris(D6, 250);
	play_tone_tetris(E6, 125);
	play_tone_tetris(D6, 125);
	play_tone_tetris(C6, 250);
	play_tone_tetris(B5, 250);
	play_tone_tetris(A5, 500);
	play_tone_tetris(A5, 250);
	play_tone_tetris(C6, 250);
	play_tone_tetris(E6, 500);
	play_tone_tetris(D6, 250);
	play_tone_tetris(C6, 250);
	play_tone_tetris(B5,750);
	play_tone_tetris(C6, 250);
	play_tone_tetris(D6, 500);
	play_tone_tetris(E6, 500);
	play_tone_tetris(C6, 500);
	play_tone_tetris(A5, 500);
	play_tone_tetris(A5, 500);
	usleep(250);
	play_tone_tetris(D6, 500);
	play_tone_tetris(F6, 250);
	play_tone_tetris(A6, 500);
	play_tone_tetris(G6, 250);
	play_tone_tetris(F6, 250);
	play_tone_tetris(E6, 750);
	play_tone_tetris(C6, 250);
	play_tone_tetris(E6, 500);
	play_tone_tetris(D6, 250);
	play_tone_tetris(C6, 250);
	play_tone_tetris(B5, 500);
	play_tone_tetris(B5, 250);
	play_tone_tetris(C6, 250);
	play_tone_tetris(D6, 500);
	play_tone_tetris(E6, 500);
	play_tone_tetris(C6, 500);
	play_tone_tetris(A5, 500);
	play_tone_tetris(A5, 500);
	usleep(500);
	play_tone_tetris(E6, 500);
	play_tone_tetris(B5, 250);
	play_tone_tetris(C6, 250);
	play_tone_tetris(D6, 250);
	play_tone_tetris(E6, 125);
	play_tone_tetris(D6, 125);
	play_tone_tetris(C6, 250);
	play_tone_tetris(B5, 250);
	play_tone_tetris(A5, 500);
	play_tone_tetris(A5, 250);
	play_tone_tetris(C6, 250);
	play_tone_tetris(E6, 500);
	play_tone_tetris(D6, 250);
	play_tone_tetris(C6, 250);
	play_tone_tetris(B5, 750);
	play_tone_tetris(C6, 250);
	play_tone_tetris(D6, 500);
	play_tone_tetris(E6, 500);
	play_tone_tetris(C6, 500);
	play_tone_tetris(A5, 500);
	play_tone_tetris(A5, 500);
	usleep(250);
	play_tone_tetris(D6, 500);
	play_tone_tetris(F6, 250);
	play_tone_tetris(A6, 500);
	play_tone_tetris(G6, 250);
	play_tone_tetris(F6, 250);
	play_tone_tetris(E6, 750);
	play_tone_tetris(C6, 250);
	play_tone_tetris(E6, 500);
	play_tone_tetris(D6, 250);
	play_tone_tetris(C6, 250);
	play_tone_tetris(B5, 500);
	play_tone_tetris(B5, 250);
	play_tone_tetris(C6, 250);
	play_tone_tetris(D6, 500);
	play_tone_tetris(E6, 500);
	play_tone_tetris(C6, 500);
	play_tone_tetris(A5, 500);
	play_tone_tetris(A5, 500);
	usleep(500);
	play_tone_tetris(E5, 1000);
	play_tone_tetris(C5, 1000);
	play_tone_tetris(D5, 1000);
	play_tone_tetris(B4, 1000);
	play_tone_tetris(C5, 1000);
	play_tone_tetris(A4, 1000);
	play_tone_tetris(Ab4, 1000);
	play_tone_tetris(B4, 1000);
	play_tone_tetris(E5, 1000);
	play_tone_tetris(C5, 1000);
	play_tone_tetris(D5, 1000);
	play_tone_tetris(B4, 1000);
	play_tone_tetris(C5, 500);
	play_tone_tetris(E5, 500);
	play_tone_tetris(A5, 1000);
	play_tone_tetris(A5, 2000);
	play_tone_tetris(E5, 1000);
	play_tone_tetris(C5, 1000);
	play_tone_tetris(D5, 1000);
	play_tone_tetris(B4, 1000);
	play_tone_tetris(C5, 1000);
	play_tone_tetris(A4, 1000);
	play_tone_tetris(Ab4, 1000);
	play_tone_tetris(B4, 1000);
	play_tone_tetris(E5, 1000);
	play_tone_tetris(C5, 1000);
	play_tone_tetris(D5, 1000);
	play_tone_tetris(B4, 1000);
	play_tone_tetris(C5, 500);
	play_tone_tetris(E5, 500);
	play_tone_tetris(A5, 1000);
	play_tone_tetris(Ab5, 2000);


  return 0;
}
