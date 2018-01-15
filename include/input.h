#ifndef INPUT_H
#define INPUT_H

#include "LSDL.h"

bool handleEvents( SDL_Event e ); //returns whether or not to quit
void storeInput(); //stores the space presses. takes in the time between each frame
void startPlayingInput();
void playInput();
void spaceDown();
void spaceUp();
void inputDone();

#endif
