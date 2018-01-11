#ifndef SOUND_H
#define SOUND_H

#include "LSDL.h"

#define BEEP 1
#define SILENCE 0

bool loadSound();
void playSound( int type, int ms );
void freeSound();

#endif
