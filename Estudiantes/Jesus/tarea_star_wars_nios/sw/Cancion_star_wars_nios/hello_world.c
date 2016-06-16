

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //unix standard
#include <io.h> // I/O Access
#include <system.h>

#define do 95565
#define re 85129
#define mi 75842
#define fa 71585
#define sol 63775
#define sols 60230
#define la 56817
#define las 54935
#define si 50619
#define doh 47791
#define dosh 45116
#define reh 37935
#define resh 40191
#define mih 37935
#define fah 35815
#define fash 33782
#define solh 31886
#define solsh 30119
#define lah 28408
#define silence 1


void play_tone(int nota, int time_ms){
	IOWR(DIV_FREQ_BASE,0,nota);
	usleep(time_ms*1000);
}

int main()
{
	play_tone(la, 500);
	play_tone(la, 500);
	play_tone(la, 500);
	play_tone(fa, 350);
	play_tone(doh, 150);

	play_tone(la, 500);
	play_tone(fa, 350);
	play_tone(doh, 150);
	play_tone(la, 1000);
	//first bi

	play_tone(mih, 500);
	play_tone(mih, 500);
	play_tone(mih, 500);
	play_tone(fah, 350);
	play_tone(doh, 150);

	play_tone(sols, 500);
	play_tone(fa, 350);
	play_tone(doh, 150);
	play_tone(la, 1000);
	//second b..

	play_tone(lah, 500);
	play_tone(la, 350);
	play_tone(la, 150);
	play_tone(lah, 500);
	play_tone(solsh, 250);
	play_tone(solh, 250);

	play_tone(fash, 125);
	play_tone(fah, 125);
	play_tone(fash, 250);
	play_tone(silence,250);
	play_tone(las, 250);
	play_tone(resh, 500);
	play_tone(reh, 250);
	play_tone(dosh, 250);
	//start of the interesting bit

	play_tone(doh, 125);
	play_tone(si, 125);
	play_tone(doh, 250);
	play_tone(silence,250);
	play_tone(fa, 125);
	play_tone(sols, 500);
	play_tone(fa, 375);
	play_tone(la, 125);

	play_tone(doh, 500);
	play_tone(la, 375);
	play_tone(doh, 125);
	play_tone(mih, 1000);
	//more interesting stuff (this doesn't quite get it right somehow)

	play_tone(lah, 500);
	play_tone(la, 350);
	play_tone(la, 150);
	play_tone(lah, 500);
	play_tone(solsh, 250);
	play_tone(solh, 250);

	play_tone(fash, 125);
	play_tone(fah, 125);
	play_tone(fash, 250);
	play_tone(silence,250);
	play_tone(las, 250);
	play_tone(resh, 500);
	play_tone(reh, 250);
	play_tone(dosh, 250);
	//repeat... repeat

	play_tone(doh, 125);
	play_tone(si, 125);
	play_tone(doh, 250);
	play_tone(silence,250);
	play_tone(fa, 250);
	play_tone(sols, 500);
	play_tone(fa, 375);
	play_tone(doh, 125);

	play_tone(la, 500);
	play_tone(fa, 375);
	play_tone(do, 125);
	play_tone(la, 1000);
	play_tone(silence,400);


  return 0;
}


