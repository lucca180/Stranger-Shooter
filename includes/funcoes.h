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
#include <stdlib.h>
#include <time.h>

#include "globais.h"
#include "defs.h"

// ----- SDL ----- //
int init();
int loadMedia(SDL_Surface* *imagem);
void closing();
SDL_Surface* loadPNG( char *path ); // Tem Transparencia
SDL_Surface* loadSurface( char *path ); //N tem transparencia


// ------ SPRITES (IMAGENS) --------- //
Sprite createSprite(int x, int y, SDL_Surface* loaded);
int draw(Sprite p);


// ------ COLISAO ---------- //
int collided(Sprite a, Sprite b);
int collided_circle(Sprite circle1, Sprite circle2);
int colideCheck(Matrix m, Sprite* ball);

// ------ O JOGO ----- //
int theGame(int tela);

// ---------- EVENTOS ------- //
int buttonClick (Sprite p, SDL_Event* e);
int ballTraject(Sprite *ball, SDL_Event* e);

void moveBola(Sprite *p);

// --------- DESESPERO ------- //
Matrix matrix_create(int width, int height);
void matrix_destroy(Matrix* m);
Sprite* matrix_row(Matrix* m, int row);
Matrix criaMatriz (int l, int c, SDL_Surface* img[4]);
void desenhaMatriz(Matrix m);

#endif
