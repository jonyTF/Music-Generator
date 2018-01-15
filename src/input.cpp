#include "../include/input.h"
#include "../include/sound.h"
#include <list>

//TODO: instead, just start SDL_Timer when space is pressed, then stop when it is released
//      start it when it is released, then stop when it is started. This way, i can get the durations
//      between space presses, and the rhythm will be more accurate.

bool gSpaceDown = false;
bool gStart = false; //Whether user has started inputting rhythm
bool gPlayInput = false; //whether to play the input

const int NUM_MEASURES = 4;
const int BEATS_PER_MEASURE = 4;
const int NOTES_PER_BEAT = 64;
int gBPM = 120.f;
int gSpacePresses[ NUM_MEASURES * NOTES_PER_BEAT * BEATS_PER_MEASURE] = { 0 }; //shortest note is 64th note //array of 1s and 0s, 1 being on, 0 being off
Uint32 gCurrentTime = 0;
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
                    spaceDown();
                    break;

                case SDLK_q:
                    printf( "paly\n" );
                    //startPlayingInput();
                    break;

                case SDLK_w:
                    printf( "stop\n" );
                    inputDone();
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
                    spaceUp();
                    break;

                default:
                    break;
            }
        }
    }

    return false;
}

Uint32 gTimerStart = 0;
std::list<Uint32> gInput; //might want to change the name of this

void spaceDown()
{
    if ( !gSpaceDown )
    {
        gSpaceDown = true;
        if ( !gStart )
        {
            gStart = true;
        }
        else
        {
            Uint32 timePassed = SDL_GetTicks() - gTimerStart;

            gInput.push_back( timePassed );
        }

        gTimerStart = SDL_GetTicks();
    }
}

void spaceUp()
{
    if ( gSpaceDown )
    {
        gSpaceDown = false;
        Uint32 timePassed = SDL_GetTicks() - gTimerStart;

        gInput.push_back( timePassed );

        gTimerStart = SDL_GetTicks();
    }
}

void inputDone()
{
    printf( "[" );

    for ( Uint32 i : gInput )
    {
        printf( "%d, ", i );
    }

    printf( "]\n" );
}


/*
void storeInput()
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

            Uint32 noteLength = round( ( 60.f * 1000.f ) / gBPM / NOTES_PER_BEAT ); //in ms
            if ( gCurrentTime >= noteLength )
            {
                //printf( "Current Time : %d, vs noteLength : %d\n", gCurrentTime, noteLength );
                gSpacePresses[ gCurrentNote ] = gSpaceDown ? BEEP : SILENCE;
                //gCurrentTime = 0;
                gCurrentTime -= noteLength; //this should compensate for frame lag
                gCurrentNote++;
            }
        }
        else
        {
            gStart = false;
            gCurrentNote = 0;
            printf( "done\n" );

            printf( "[" );
            for ( int i = 0; i < sizeof( gSpacePresses ) / sizeof( gSpacePresses[0] ); i++ )
            {
                printf( " %d, ", gSpacePresses[ i ] );
            }
            printf( "]\n" );

        }

    }
}

void startPlayingInput()
{
    gPlayInput = true;
    for ( int i = 0; i < sizeof( gSpacePresses ) / sizeof( gSpacePresses[0] ); i++ )
    {

        playSound( gSpacePresses[ i ], ( int )( ( 60.f * 1000.f ) / gBPM / NOTES_PER_BEAT ) );
    }
}

void playInput()
{
    if ( gPlayInput )
    {
        if ( gCurrentNote < sizeof( gSpacePresses ) / sizeof( gSpacePresses[0] ) )
        {
            Uint32 noteLength = round( ( 60.f * 1000.f ) / gBPM / NOTES_PER_BEAT ); //in ms
            if ( gSpacePresses[ gCurrentNote ] == BEEP )
            {
                Uint32 totalLength = noteLength;
                for ( int i = gCurrentNote + 1; i < sizeof( gSpacePresses ) / sizeof( gSpacePresses[0] ); i++ )
                {
                    //ATTENTION: NEED TO MAKE A CASE IF the for loop meets the i < spacepress length condition
                    if ( gSpacePresses[ i ] == BEEP )
                    {
                        totalLength += noteLength;
                    }
                    else
                    {
                        gCurrentNote = i - 1; // minus one because gCurrentNote++ at the end
                        break;
                    }
                }
                noteLength = totalLength;
            }
            playSound( gSpacePresses[ gCurrentNote ], noteLength );
            gCurrentNote++;
        }
        else
        {
            gPlayInput = false;
            gCurrentNote = 0;
        }
    }
}
*/
