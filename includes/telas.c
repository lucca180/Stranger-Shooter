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

void particlesDrop(Sprite *p){
	p->y += 1;
	if ((p->y + p->height > 0) && (p->y < 0)){
		draw(*p);
	}
	
	if (p->y >= -5){
		p->y = SCREEN_HEIGHT-p->height;
	}
	
}

// -------- Menu Principal -------- //

void upsideDown(Sprite *p, Sprite *g){
	if (p->y + p->height > 0) p->y -= 1;
	else{
		if (g->y > 0) g->y -= 1;}
}

void menuPrincipal (void){
	static int mLoad = 0;
	static int upside = 0;
	static int upsideLoad = 0;
	
	static Sprite fakebg, bg, bg_ultra, logo, filter, btnPlay;
	
	static Mix_Music* music1;
	static Mix_Music* music2;
	
	// Eventos da Tela
	SDL_Event e;

	while( SDL_PollEvent( &e ) != 0 ) {
		if( e.type == SDL_QUIT ) {
			quit = true;
		}
		
		if (buttonClick(fakebg, &e)) upside = 1;
	}
	
	// Resto
	
	if (!mLoad){
		
		SDL_Surface* strangerbg = loadSurface("img/bg.png");
		SDL_Surface* fakebgimg = loadSurface("img/fake/bg.png");
		SDL_Surface* bgUltraimg = loadSurface("img/bg_ultra.png");
		SDL_Surface* logoimg = loadPNG("img/logo2.png");
		SDL_Surface* filterimg = loadPNG("img/filter2.png");
		SDL_Surface* btnPlayimg = loadPNG("img/btn_play.png");
		
		bg = createSprite(0, strangerbg->h, strangerbg);
		fakebg = createSprite(0, 0, fakebgimg);
		filter = createSprite(0,(SCREEN_HEIGHT-filterimg->h), filterimg);
		logo = createSprite((SCREEN_WIDTH-logoimg->w)/2,10, logoimg);
		btnPlay = createSprite(SCREEN_WIDTH/2,SCREEN_HEIGHT/2, btnPlayimg);
		bg_ultra = createSprite(0, 0, bgUltraimg);
		
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
		Mix_AllocateChannels(16);
		
		music1 = Mix_LoadMUS("musicFake.mp3");
		music2 = Mix_LoadMUS("stmusic.mp3");
		if (!music1 || !music2) {
			printf("Mus: SDL error=%s\n", SDL_GetError());
		}
		mLoad = 1;
		Mix_PlayMusic(music1, -1);
	}
	
	draw(bg_ultra);
	draw(fakebg);
	
	if(upside){
		if(!upsideLoad){
		Mix_PauseMusic();
		Mix_FreeMusic(music1);
		Mix_PlayMusic(music2, 0);
		upsideLoad = 1;}
		
		upsideDown(&fakebg, &bg);
		draw(bg);
		if(bg.y <= 0){
			draw(btnPlay);
			particlesDrop(&filter);
			draw(logo);
		}
	}
	
}

// -------- Tela de Jogo -------- //

void gameLoop (void){
	static int mLoad = 0;
	static Sprite bg, filter, ball;
	static Matrix bolas;
	
	// Eventos da Tela
	SDL_Event e;

	 while( SDL_PollEvent( &e ) != 0 ) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_ESCAPE) {
                        quit = true;
                    }
                    break;
				case SDL_MOUSEBUTTONDOWN: /*JUBS OBS: tudo float ou vaiu dar merda*/
					ballTraject(&ball, &e);
					break;
            }
        }
        
	if (!mLoad){
		SDL_Surface* strangerbg = loadSurface("img/bg.png");
		SDL_Surface* ballimg[4];
		ballimg[0] = loadPNG("img/ball_red.png");
		ballimg[1] = loadPNG("img/ball_blue.png");
		ballimg[2] = loadPNG("img/ball_pink.png");
		ballimg[3] = loadPNG("img/ball_green.png");
		SDL_Surface* filterimg = loadPNG("img/filter2.png");
		
		bg = createSprite(0, 0, strangerbg);
		ball = createSprite((SCREEN_WIDTH - ballimg[0]->w)/2, (SCREEN_HEIGHT - ballimg[0]->h), ballimg[0]);
		filter = createSprite(0,(SCREEN_HEIGHT-filterimg->h), filterimg);
		
		bolas = criaMatriz(24,1,ballimg);
		
		mLoad = true;
	}
	
	draw(bg);
	desenhaMatriz(bolas);
	draw(ball);
	particlesDrop(&filter);
	
	colideCheck(bolas, &ball);
	
	moveBola(&ball); 
}
