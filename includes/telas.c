/*
 * telas.c
 * 
 * 2017 Lucca
 * 
 * 
 * 
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string.h>

#include "globais.h"
#include "defs.h"
#include "funcoes.h"
#include "telas.h"

void menuPrincipal (void){
	static int mLoad = 0;
	static Sprite bg, logo, filter;
	
	if (!mLoad){

	
		Mix_Music* music;
		SDL_Surface* strangerbg = loadSurface("img/bg.png");
		SDL_Surface* logoimg = loadPNG("img/logo.png");
		SDL_Surface* filterimg = loadPNG("img/filter2.png");
		
		//SDL_SetSurfaceBlendMode(filterimg, SDL_BLENDMODE_ADD);
		//SDL_SetColorKey( logoimg, SDL_TRUE, SDL_MapRGB( filterimg->format, 0, 0, 0 ));
		
		bg = createSprite(0, 0, strangerbg);
		logo = createSprite((SCREEN_WIDTH-logoimg->w)/2,0, logoimg);
		filter = createSprite(0,0, filterimg);
		
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
		Mix_AllocateChannels(16);
		
		music = Mix_LoadMUS("stmusic.mp3");
		if (!music) {
			printf("Mus: SDL error=%s\n", SDL_GetError());
		}
		mLoad = 1;
		//Mix_PlayMusic(music, -1);
	}
	
	draw(bg);
	draw(filter);
	//draw(logo);
	
}
