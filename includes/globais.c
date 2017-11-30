/*
 * Globais.c
 * 
 * 2017 Lucca, Julia e Paulo
 * 
 */

#include "globais.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;

const int true = 1;
const int false = 0;

int quit = 0;

SDL_Window* gWindow = NULL;
    
SDL_Surface* gScreenSurface = NULL;


int moveBall = 0;

/* Telas
	
	- Tela 1 => Menu Principal
	- Tela 2 => Tela de Jogo
 */
 
int gTela = 1;

