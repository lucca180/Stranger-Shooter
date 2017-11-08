/*
 * defs.h
 * 
 * 2017 Lucca, Julia e Paulo
 * 
 */

#ifndef DEFS_H
#define DEFS_H

typedef struct _SPRITE{
	int x;
	int y;
	int height;
	int width;
	
	SDL_Surface* image;
	
} Sprite;

#endif

