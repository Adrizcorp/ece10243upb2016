/*
 * karplus.h
 *
 *  Created on: 10/06/2016
 *      Author: Usuario
 */

#ifndef KARPLUS_H_
#define KARPLUS_H_


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //unix standard
#include <io.h> // I/O Access
#include <system.h>

#define TIME 3
#define HIGH_E_4 113
#define B_4 124
#define G_4 156
#define D_4 209
#define A_4 279
#define LOW_E_4 372
#define HIGH_E_0 143
#define B_0 156
#define G_0 197
#define D_0 263
#define A_0 351
#define LOW_E_0 469
#define HIGH_E_1 135
#define B_1 147
#define G_1 186
#define D_1 248
#define A_1 331
#define LOW_E_1 442
#define HIGH_E_2 127
#define B_2 139
#define G_2 175
#define D_2 234
#define A_2 313
#define LOW_E_2 417
#define HIGH_E_3 120
#define B_3 131
#define G_3 165
#define D_3 221
#define A_3 295
#define LOW_E_3 394
#define HIGH_E_5 107
#define B_5 117
#define G_5 147
#define D_5 197
#define A_5 263
#define LOW_E_5 351
#define HIGH_E_6 101
#define B_6 110
#define G_6 139
#define D_6 186
#define A_6 248
#define LOW_E_6 331
#define HIGH_E_7 95
#define B_7 104
#define G_7 131
#define D_7 176
#define A_7 234
#define LOW_E_7 313
#define HIGH_E_8 90
#define B_8 98
#define G_8 124
#define D_8 166
#define A_8 221
#define LOW_E_8 295
#define HIGH_E_9 85
#define B_9 93
#define G_9 117
#define D_9 156
#define A_9 209
#define LOW_E_9 279
#define HIGH_E_10 80
#define HIGH_E_11 75
#define HIGH_E_12 71
#define B_10 88
#define B_12 78
#define silence 1

void init_karplus();
void set_karplus_frequency(int frecuencia);
void play_tone(int nota, int time_ms);
void inject_noise();


#endif /* KARPLUS_H_ */
