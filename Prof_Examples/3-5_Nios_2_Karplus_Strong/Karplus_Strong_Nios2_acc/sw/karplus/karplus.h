/*
 * karplus.h
 *
 *  Created on: Jun 10, 2016
 *      Author: Holguer
 */

#ifndef KARPLUS_H_
#define KARPLUS_H_


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //unix standard
#include <io.h> // I/O Access
#include <system.h>

#define TIME 3
#define HIGH_E_0 143
#define B_0 156
#define G_0 197
#define D_0 263
#define A_0 351
#define LOW_E_0 469

void init_karplus();
void set_karplus_frequency(int frecuencia);
void play_tone(int nota,int time_ms);
void inject_noise();

#endif /* KARPLUS_H_ */
