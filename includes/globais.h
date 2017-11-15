/*
 * Globais.h
 * 
 * Copyright 2016 Adriano Cruz <adriano@nce.ufrj.br>
 * 
 */

#ifndef GLOBAIS_H
#define GLOBAIS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const int false;
extern const int true;

extern int quit;

extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface;

extern int gTela;

extern int moveBall;
#endif
