#ifndef SOUND_H
#define SOUND_H

#include <windows.h>

#include "LSDL.h"

#define SILENCE 0
#define BEEP 1

bool loadSound();
void playSound( int type, Uint32 ms );
void freeSound();

#endif
