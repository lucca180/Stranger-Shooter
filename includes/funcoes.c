/*
 * funcoes.c
 * 
 *  2017 Lucca, Julia e Paulo
 * 
 */


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "globais.h"
#include "defs.h"
#include "funcoes.h"
#include "telas.h"

// ----- Sprites ------- //

Sprite createSprite(int x, int y, SDL_Surface* loaded){
	Sprite p;
	
	p.x = x;
	p.y = y;
	
	p.iShow = 1;
	
	p.image = loaded;
	p.width = loaded->w;
	p.height = loaded->h;
	
	return p;
}

int draw(Sprite p){
	if(p.iShow){
		if((p.y + p.height > 0) && (p.y < SCREEN_HEIGHT)){
			SDL_Rect dstRect;
			
			dstRect.x = p.x;
			dstRect.y = p.y;
			
			SDL_BlitSurface( p.image, NULL, gScreenSurface, &dstRect );	
			
			return true;
		}
	}
	return false;
}


// -------- Collision Functions ----------- //

int collided(Sprite rect1, Sprite rect2){
	if (rect1.x < rect2.x + rect2.width &&
		rect1.x + rect1.width > rect2.x &&
		rect1.y < rect2.y + rect2.height &&
		rect1.height + rect1.y > rect2.y) {
			return true;
	}
	
	return false;	
}

int collided_circle(Sprite circle1, Sprite circle2){
	
	float circle1r = circle1.height/2;
	float circle2r = circle2.height/2;
	
	float dx = circle1.x - circle2.x;
	float dy = circle1.y - circle2.y;
	float distance = sqrt(dx * dx + dy * dy);

	if (distance < circle1r + circle2r) {
		return true;
	}
	
	return false;
}

int colideCheck(Matrix m, Sprite* ball){
	int r, c;
	
	if(moveBall){
		for (r=0; r < m.height; ++r){ 
			Sprite* row = matrix_row(&m, r);
			for (c=0; c < m.width; ++c)
				if(collided_circle(row[c], *ball)){
					moveBall = false;
					if(row[c].image == ball->image){ 
						ball->iShow = 0; 
						row[c].iShow = 0;
					}
					return true;
				}
		}
	}
    return false;
}

// ------------ Buttons Functions ----------------- //

int buttonClick (Sprite p, SDL_Event* e){
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_BUTTON_LEFT || e->type == SDL_MOUSEBUTTONUP ) {
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		int inside = true;

		//Mouse is left of the button
		if( x < p.x ) {
			inside = false;
		}
		//Mouse is right of the button
		else if( x > p.x + p.width ) {
			inside = false;
		}
		//Mouse above the button
		else if( y < p.y ) {
			inside = false;
		}
		//Mouse below the button
		else if( y > p.y + p.height ) {
			inside = false;
		}

		//Mouse is outside button
		if( !inside ) {
			//botao->mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else {
			//Set mouse over sprite
			switch( e->type ) {
				//case SDL_MOUSEMOTION:
				//botao->mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				//break;
			
				//case SDL_BUTTON_LEFT:
				//botao->mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				//break;
				
				case SDL_MOUSEBUTTONUP:
				return true;
				break;
			}
		}
	}
	return false;
}

// -------- Balls Functions -------- //

int ballTraject (Sprite *ball, SDL_Event* e){
	int Mouse_x, Mouse_y;
	float Mouse_hip;
	
	if (!moveBall) {
		if(e->button.button == SDL_BUTTON_LEFT){
			moveBall = true;	
			SDL_GetMouseState (&Mouse_x, &Mouse_y);
			Mouse_x = (Mouse_x - SCREEN_WIDTH/2);
			Mouse_y = (SCREEN_HEIGHT - ball->height/2 - Mouse_y);
			if (Mouse_y<=30) {
				moveBall = false;
			}
			Mouse_hip = sqrt(Mouse_x*Mouse_x + Mouse_y*Mouse_y);
			
			ball->stepX = (Mouse_x/Mouse_hip)*10;
			ball->stepY = -(Mouse_y/Mouse_hip)*10;
		}
	}
	return 0;
}

void moveBola(Sprite *p) {
	if(moveBall && (p->y >= 0)){
		p->x += p->stepX;
		p->y += p->stepY;
		
		if ( (p->x + p->width > SCREEN_WIDTH) ||
			 (p->x < 0) ) {
			p->stepX = -p->stepX;
			p->x += p->stepX; 
		}
		if ( (p->y + p->height > SCREEN_HEIGHT)) {
			p->stepY = -p->stepY;
			p->y += p->stepY;
		}
		
		else if (p->y <= 0) moveBall = false;
	}
}
// ----------- Desespero de Matriz ------------ // 

	// i Was Truly Desperate https://stackoverflow.com/a/29982192
	
Matrix matrix_create(int width, int height){
    Matrix new_matrix;
    new_matrix.width = width;
    new_matrix.height = height;
    new_matrix.ptr = malloc(width * height * sizeof(Sprite));
    return new_matrix;
}

void matrix_destroy(Matrix* m){
    free(m->ptr);
}

Sprite* matrix_row(Matrix* m, int row){
    return m->ptr + row * m->width;
}
	// Fim do desespero
	
Matrix criaMatriz (int i, int j, SDL_Surface* img[4]){
	int c, r, x;
	Matrix m = matrix_create(i, j);
	srand( (unsigned)time(NULL) );
	printf("%d\n", rand());
	for (r=0; r <= m.height-1; ++r){
        Sprite* row = matrix_row(&m, r);
   
        for (c=0; c < m.width; ++c){
            x = rand() % 4;
            row[c] = createSprite(img[x]->w*c,img[x]->h*r,img[x]);
		}
    }
	return m;
}

void desenhaMatriz(Matrix m){
	int r, c;

	for (r=0; r < m.height; ++r){ 
        Sprite* row = matrix_row(&m, r);
        for (c=0; c < m.width; ++c)
            draw(row[c]);
    }
    
}


// -- The Game -> Funcao Principal ( e sim, vc acaba de perder o Jogo ) -- //

int theGame (int tela){
	if(tela == 1) menuPrincipal();
	if(tela == 2) gameLoop();
	else {
		puts("Código de Tela Inválido");
		return 1;}
	
	return 0;
}


// -------- FUNCOES DO SDL -> FAVOR NAO ALTERAR ------------ //

int init() {
    //flag de inicializacao
    int success = true;

    //Inicie SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else {
        //Crie janela
        gWindow = SDL_CreateWindow( "Stranger Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL ) {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else {
            //Inicie a carga da imagem
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            }
            else {
                //Pegue a superficie da janela
                gScreenSurface = SDL_GetWindowSurface( gWindow );
            }
        }
    }
    return success;
}

int loadMedia(SDL_Surface* *imagem)
{
    //flag de carga 
    int success = true;

    //Carregue a superficie PNG
    *imagem = loadSurface( "./loaded.png" );
    if( imagem == NULL ) {
        printf( "Failed to load PNG image!\n" );
        success = false;
    }
    
    return success;
}

void closing() {
    //libere a imagem carregada
    //SDL_FreeSurface( gPNGSurface );
    //gPNGSurface = NULL;

    //Destrua janela
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL
    IMG_Quit();
    SDL_Quit();
}

SDL_Surface* loadPNG( char *path ) {
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL ) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }
    else {
        SDL_SetSurfaceBlendMode(loadedSurface, SDL_BLENDMODE_BLEND);
    }
    return loadedSurface;
}

SDL_Surface* loadSurface( char *path ) {
    //A imagem final apos ser otimizada
    SDL_Surface* optimizedSurface = NULL;

    //Carregue a imagem no caminho especificado em path
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL ) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }
    else {
        //Converte a superficie para o formato da tela.
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
        if( optimizedSurface == NULL ) {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
        }

        //Libera a superficie velha
        SDL_FreeSurface( loadedSurface );
    }
    return optimizedSurface;
}
