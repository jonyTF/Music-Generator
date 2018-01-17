#ifndef INPUT_H
#define INPUT_H

#include "LSDL.h"

bool handleEvents( SDL_Event e ); //returns whether or not to quit
void storeInput(); //stores the space presses. takes in the time between each frame
void startPlayingInput();
int playInput( void* data );
void spaceDown();
void spaceUp();
void inputDone();
void quantizeInput();
void closeInput();

#endif
