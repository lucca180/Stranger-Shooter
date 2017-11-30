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

int goTo = 1; //Vai Para a Tela

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
	static Sprite bg, logo, filter, btnPlay, btnPlacar, btnOp, btnSair;
	static Mix_Music* music1;
	static SDL_Surface* images[6];
	int surfaceN = 6;
	
	// Eventos da Tela
	SDL_Event e;

	while( SDL_PollEvent( &e ) != 0 ) {
		if( e.type == SDL_QUIT ) {
			quit = true;
		}
		
		if (buttonClick(btnPlay, &e)) goTo = 2;
	}
	
	// Resto
	
	if (!mLoad){
		
		SDL_Surface* strangerbg = loadSurface("img/bg.png"); *(images+0) = strangerbg;
		SDL_Surface* logoimg = loadPNG("img/logo2.png"); *(images+1) = logoimg;
		SDL_Surface* filterimg = loadPNG("img/filter2.png"); *(images+2) = filterimg;
		SDL_Surface* btnPlayimg = loadPNG("img/btn_play.png"); *(images+3) = btnPlayimg;
		SDL_Surface* btnPlacarimg = loadPNG("img/btn_placar.png"); *(images+4) = btnPlacarimg;
		SDL_Surface* btnOpimg = loadPNG("img/btn_op.png"); *(images+5) = btnOpimg;
		SDL_Surface* btnSairimg = loadPNG("img/btn_sair.png"); *(images+6) = btnSairimg;
		
		bg = createSprite(0, 0, strangerbg);
		filter = createSprite(0,(SCREEN_HEIGHT-filterimg->h), filterimg);
		logo = createSprite((SCREEN_WIDTH-logoimg->w)/2,10, logoimg);
		
		btnPlay = createSprite(logo.x/1.5,SCREEN_HEIGHT/2.3, btnPlayimg);
		btnPlacar = createSprite((logo.x+logo.width)-btnPlay.width/1.5,SCREEN_HEIGHT/2.3, btnPlacarimg);
		btnOp = createSprite(logo.x/1.5,SCREEN_HEIGHT/1.7, btnOpimg);
		btnSair = createSprite((logo.x+logo.width)-btnPlay.width/1.5,SCREEN_HEIGHT/1.7, btnSairimg);
		
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
		Mix_AllocateChannels(16);

		music1 = Mix_LoadMUS("stmusic.mp3");
		if (!music1) {
			printf("Mus: SDL error=%s\n", SDL_GetError());
		}
		mLoad = 1;
		Mix_PlayMusic(music1, -1);
	}
		
		draw(bg);
		
		draw(btnPlay);
		draw(btnPlacar);
		draw(btnOp);
		draw(btnSair);
		
		particlesDrop(&filter);
		draw(logo);
	
	if(goTo != gTela){ //Limpa as Imagens
		int i;
		for(i=0; i <= surfaceN; i++ ) SDL_FreeSurface( images[i] );
		gTela = goTo;
		mLoad = 0;
		
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
						gTela = 1;
						goTo = 1;
                    }
                    break;
				case SDL_MOUSEBUTTONDOWN: /*JUBS OBS: tudo float ou vaiu dar merda*/
					ballTraject(&ball, &e);
					break;
            }
        }
        
	if (!mLoad){
		SDL_Surface* strangerbg = loadSurface("img/bg.png");
		SDL_Surface* filterimg = loadPNG("img/filter2.png");
		
		SDL_Surface* ballimg[4];
		ballimg[0] = loadPNG("img/ball_red.png");
		ballimg[1] = loadPNG("img/ball_blue.png");
		ballimg[2] = loadPNG("img/ball_pink.png");
		ballimg[3] = loadPNG("img/ball_green.png");
		
		
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
