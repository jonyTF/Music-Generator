#ifndef SOUND_H
#define SOUND_H

#include "LSDL.h"

#define SILENCE 0
#define BEEP 1

bool loadSound();
void playSound( int type, int ms );
void freeSound();

#endif
