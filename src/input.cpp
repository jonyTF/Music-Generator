#include "../include/input.h"

bool gSpaceDown = false;
bool gStart = false; //Whether user has started inputting rhythm

int gNumMeasures = 8;
int gSpacePresses[ gNumMeasures * 64 ]; //shortest note is 64th note
//array of 1s and 0s, 1 being on, 0 being off

bool handleEvents( SDL_Event e )
{
    while ( SDL_PollEvent( &e ) != 0 )
    {
        if ( e.type == SDL_QUIT )
        {
            return true;
        }
        else if ( e.type == SDL_KEYDOWN )
        {
            switch ( e.key.keysym.sym )
            {
                case SDLK_SPACE:
                    gSpaceDown = true;
                    break;

                default:
                    break;
            }
        }
        else if ( e.type == SDL_KEYUP )
        {
            switch ( e.key.keysym.sym )
            {
                case SDLK_SPACE:
                    gSpaceDown = false;

                    break;

                default:
                    break;
            }
        }
    }

    return false;
}

void storeInput()
{
    if ( !gStart )
    {
        gStart = true;
    }
    else
    {

    }
}
