/*
 * telas.h
 * 
 * 2017 Lucca, Julia e Paulo
 * 
 */

#ifndef TELAS_H
#define TELAS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string.h>

#include "globais.h"
#include "defs.h"


void menuPrincipal (void);

void particlesDrop(Sprite *p);
void upsideDown(Sprite *p, Sprite *g);
#endif
