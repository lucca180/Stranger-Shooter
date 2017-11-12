/*
 * funcoes.h
 * 
 * 2017 Lucca, Julia e Paulo
 * 
 */

#ifndef FUNCOES_H
#define FUNCOES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include "globais.h"
#include "defs.h"

//Inicia SDL e cria window
int init();

//Carrega media
int loadMedia(SDL_Surface* *imagem);

//Libera media e desliga SDL
void closing();

//Carrega uma imagem
SDL_Surface* loadPNG( char *path ); // Tem Transparencia

SDL_Surface* loadSurface( char *path ); //N tem transparencia

Sprite createSprite(int x, int y, SDL_Surface* loaded);

int draw(Sprite p);

int collided(Sprite a, Sprite b);

int collided_circle(Sprite circle1, Sprite circle2);

int theGame(int tela);

int buttonClick (Sprite p, SDL_Event* e);

//Sprite criaMatriz(int l, int a);

//void desenhaMatriz(Sprite v);

#endif
