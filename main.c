/*
 * main.c
 * 
 * 2017 Lucca, Julia e Paulo
 * 
 * 
 */

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "includes/defs.h"
#include "includes/globais.h"
#include "includes/funcoes.h"
#include "includes/telas.h"


int main( int argc, char* args[] ) {
    //Inicie SDL e crie janela
    if( !init() ) {
        printf( "Failed to initialize!\n" );
    }
    else {
            //Main loop flag
            int quit = false;

            //Event handler
            SDL_Event e;

            //While application is running
            while( !quit ) {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 ) {
                    //User requests quit
                    if( e.type == SDL_QUIT ) {
                        quit = true;
                    }
                }
				
				theGame(gTela);
                //Update A surface
                SDL_UpdateWindowSurface( gWindow );
            }
        }

    //Free resources e closing SDL
    closing();

    return 0;
}
