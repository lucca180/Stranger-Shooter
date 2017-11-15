/*
 * defs.h
 * 
 * 2017 Lucca, Julia e Paulo
 * 
 */

#ifndef DEFS_H
#define DEFS_H

typedef int bool;

typedef struct _SPRITE{
	float x;
	float y;
	
	int iShow;
	
	int height;
	int width;
	
	float stepX;
	float stepY;
	
	SDL_Surface* image;
	
	
} Sprite;

typedef struct _MATRIX{
    int width;
    int height;
    Sprite* ptr;
} Matrix;

#endif

