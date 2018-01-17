#include "../include/sound.h"
#include <windows.h>

Mix_Chunk* gBeepSound = NULL;
Mix_Chunk* gSilence = NULL;

bool loadSound()
{
    bool success = true;

    gBeepSound = Mix_LoadWAV( "sound/beep.wav" ); //doesn't work if you don't run it from in the bin directory
    if ( gBeepSound == NULL )
    {
        printf( "Could not load beep.wav. Error: %s\n", Mix_GetError() );
        success = false;
    }

    gSilence = Mix_LoadWAV( "sound/silence.wav" ); //doesn't work if you don't run it from in the bin directory
    if ( gSilence == NULL )
    {
        printf( "Could not load silence.wav. Error: %s\n", Mix_GetError() );
        success = false;
    }

    return success;
}

void playSound( int type, Uint32 ms )
{
    printf( "play sound for %d milliseconds\n", ms );
    if ( type == BEEP )
    {
        Mix_PlayChannelTimed( 1, gBeepSound, -1, ms );
    }
    else if ( type == SILENCE )
    {
        Mix_PlayChannelTimed( 1, gSilence, -1, ms );
    }

    Sleep( ms );
}

void freeSound()
{
    Mix_FreeChunk( gBeepSound );
    gBeepSound = NULL;
}
