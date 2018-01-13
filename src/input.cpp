#include "../include/input.h"
#include "../include/sound.h"

bool gSpaceDown = false;
bool gStart = false; //Whether user has started inputting rhythm

const int NUM_MEASURES = 4;
const int BEATS_PER_MEASURE = 4;
const int NOTES_PER_BEAT = 64;
int gBPM = 120.f;
int gSpacePresses[ NUM_MEASURES * NOTES_PER_BEAT * BEATS_PER_MEASURE] = { 0 }; //shortest note is 64th note //array of 1s and 0s, 1 being on, 0 being off
float gCurrentTime = 0;
unsigned int gCurrentNote = 0;

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

                case SDLK_q:
                    printf( "paly\n" );
                    playInput();
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

void storeInput( float time )
{
    //printf( "Current Time: %f\n", gCurrentTime );
    //printf( "Current Note: %d\n", gCurrentNote );
    //printf( "Size of gSpacePresses: %d\n", sizeof( gSpacePresses ) );
    if ( !gStart )
    {
        if ( gSpaceDown )
        {
            gStart = true;
        }
    }
    else
    {
        if ( gCurrentNote < sizeof( gSpacePresses ) / sizeof( gSpacePresses[0] ) )
        {
            gCurrentTime += time; //gCurrentTime is in milliseconds

            float noteLength = ( 60.f * 1000.f ) / gBPM / NOTES_PER_BEAT;
            if ( gCurrentTime >= noteLength )
            {
                printf( "Current Time : %f, vs noteLength : %f\n", gCurrentTime, noteLength );
                gSpacePresses[ gCurrentNote ] = gSpaceDown ? BEEP : SILENCE;
                gCurrentTime = 0;
                gCurrentNote++;
            }
        }
        else
        {
            printf( "done\n" );
            /*
            printf( "[" );
            for ( int i = 0; i < sizeof( gSpacePresses ) / sizeof( gSpacePresses[0] ); i++ )
            {
                printf( " %d, ", gSpacePresses[ i ] );
            }
            printf( "]\n" );
            */
        }

    }
}

void playInput()
{
    for ( int i = 0; i < sizeof( gSpacePresses ) / sizeof( gSpacePresses[0] ); i++ )
    {
        playSound( gSpacePresses[ i ], ( int )( ( 60.f * 1000.f ) / gBPM / NOTES_PER_BEAT ) );
    }
}
