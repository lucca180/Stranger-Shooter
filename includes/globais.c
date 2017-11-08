/*
 * Globais.c
 * 
 * 2017 Lucca, Julia e Paulo
 * 
 */

#include "globais.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;

const int false = 0;
const int true = 1;

SDL_Window* gWindow = NULL;
    
SDL_Surface* gScreenSurface = NULL;



/* Telas
	
	- Tela 1 => Menu Principal
 
 */
 
int gTela = 1;

