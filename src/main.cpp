#include "../include/LSDL.h"
#include "../include/input.h"
#include "../include/sound.h"

bool init();
bool loadMedia();
void close();
void render();

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

int main( int argc, char* argv[] )
{
    if ( !init() )
    {
        printf( "Could not initialize.\n" );
    }
    else
    {
        if ( !loadSound() )
        {
            printf( "Could not load sound.\n" );
        }
        else
        {
            bool quit = false;
            SDL_Event e;

            while ( !quit )
            {
                if ( handleEvents( e ) )
                {
                    quit = true;
                }

                //storeInput();

                render();
            }
        }
    }

    return 0;
}

bool init()
{
    bool success = true;

    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "Could not initialize SDL. Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow( "Music Generator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if ( gWindow == NULL )
        {
            printf( "Could not create window. Error: %s\n", SDL_GetError );
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if ( gRenderer == NULL )
            {
                printf( "Could not create renderer. Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );

                //init audio mixer
                if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_Mixer Could not initialize. Error: %s\n", Mix_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}

void close()
{
    freeSound();
    closeInput();

    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gRenderer = NULL;
    gWindow = NULL;

    Mix_Quit();
    SDL_Quit();
}

void render()
{
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );

    SDL_RenderClear( gRenderer );

    SDL_RenderPresent( gRenderer );
}
