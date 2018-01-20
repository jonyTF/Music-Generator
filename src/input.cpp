#include "../include/input.h"
#include "../include/sound.h"

//TODO: instead, just start SDL_Timer when space is pressed, then stop when it is released
//      start it when it is released, then stop when it is started. This way, i can get the durations
//      between space presses, and the rhythm will be more accurate.

bool gSpaceDown = false; //needed so that I know when space is actually pressed/lifted, instead of what happens when you hold it down
bool gStart = false; //Whether user has started inputting rhythm

int gNotesPerBeat = 64;
int gBPM = 120;
int gCurrentSound = BEEP;

Uint32 gTimerStart = 0;
std::vector<Uint32> gInput; //might want to change the name of this

SDL_Thread* playInputThread = NULL;

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
                    startPlayingInput();
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

    for ( int i = 0; i < gInput.size(); i++ )
    {
        printf( "%d, ", gInput[ i ] );
    }

    printf( "]\n" );
}

void startPlayingInput()
{
    quantizeInput();
    playInputThread = SDL_CreateThread( playInput, "playInputThread", ( void* )NULL );
}

int playInput( void* data )
{
    srand(time( NULL ));

    for ( int i = 0; i < gInput.size(); i++ )
    {
        if ( i % 2 == 0 )
            playSound( BEEP, gInput[ i ] );
        else
            playSound( SILENCE, gInput[ i ] );
    }

    printf( "done.\n" );

    return 0;
}

void quantizeInput()
{
    float noteLength = ( 60.f * 1000.f ) / gBPM / gNotesPerBeat; //in ms

    for ( int i = 0; i < gInput.size(); i++ )
    {
        gInput[ i ] = noteLength * ceil( gInput[ i ] / noteLength ); //set the length of the note to a quantized version

    }
}

void closeInput()
{
    SDL_WaitThread( playInputThread, NULL );
}
