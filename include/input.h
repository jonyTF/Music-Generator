#ifndef INPUT_H
#define INPUT_H

#include "LSDL.h"

bool handleEvents( SDL_Event e ); //returns whether or not to quit
void storeInput( Uint32 time ); //stores the space presses. takes in the time between each frame
void startPlayingInput();
void playInput();

#endif
