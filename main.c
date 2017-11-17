/*
 * 
 * main.c
 * 
 * 2017 - @Lucca Ricardo (117224925), Júlia Lima(117220751), Paulo Renato(117207703)
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
#include <stdlib.h>

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
           

            //Event handler
           // SDL_Event e;

            //While application is running
            while( !quit ) {
              
                SDL_FillRect( gScreenSurface, NULL, SDL_MapRGB( gScreenSurface->format, 0, 0, 0) );
				
				theGame(gTela);
                //Update A surface
                SDL_UpdateWindowSurface( gWindow );
               // SDL_Delay(5);
            }
        }

    //Free resources e closing SDL
    closing();

    return 0;
}
