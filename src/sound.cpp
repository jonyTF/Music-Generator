#include "../include/sound.h"

Mix_Chunk* gBeepSound = NULL;

bool loadSound()
{
    bool success = true;

    gBeepSound = Mix_LoadWAV( "../sound/beep.wav" );
    if ( gBeepSound == NULL )
    {
        printf( "Could not load beep.wav. Error: %s\n", Mix_GetError() );
        success = false;
    }

    return success;
}

void freeSound()
{
    Mix_FreeChunk( gBeepSound );
    gBeepSound = NULL;
}
