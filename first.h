
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define WIDTH 1280
#define HEIGHT 720

struct ship{ 
    int x;
    int y;
    int dx;
    int dy;
    int health;
    SDL_Texture * texture;
};

struct ship player;

//struct ship* bombardier;

typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
    int up;
    int down;
    int left;
    int right;
    int fire;
} Game;

Game game;

struct Enemy{
    int x;
    int y;
    int dx;
    int dy;
    int health;
    SDL_Texture* texture;
    //struct Bombardier * next;
};

void init(void){
    int rendererflags, windowflags;
    rendererflags = SDL_RENDERER_ACCELERATED;
    windowflags = 0;
    if(SDL_Init(SDL_INIT_VIDEO < 0)){
        printf("ERROR %s\n", SDL_GetError());
        exit(-1);
    }
    game.window = SDL_CreateWindow("<---My first game--->", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, windowflags);
    if(!game.window){
        printf("Failed! %s\n", SDL_GetError());
        exit(-1);
    }

    game.renderer = SDL_CreateRenderer(game.window, -1, rendererflags);
    if(!game.renderer){
        printf("ERROR ! %s\n", SDL_GetError());
        exit(-1);
    }

}

void keytrue(SDL_KeyboardEvent * event){
    if(event->repeat == 0){
        if(event->keysym.scancode == SDL_SCANCODE_SPACE){
            game.fire = 1;
        }
        if(event->keysym.scancode == SDL_SCANCODE_UP){
            game.up = 1;
        }
        if(event->keysym.scancode == SDL_SCANCODE_DOWN){
            game.down = 1;
        }
        if(event->keysym.scancode == SDL_SCANCODE_LEFT){
            game.left = 1;
        }
        if(event->keysym.scancode == SDL_SCANCODE_RIGHT){
            game.right = 1;
        }
    }
}

void keyfalse(SDL_KeyboardEvent * event){
    if(event->repeat == 0){
        if(event->keysym.scancode == SDL_SCANCODE_SPACE){
            game.fire = 0;
        }
        if(event->keysym.scancode == SDL_SCANCODE_UP){
            game.up = 0;
        }
        if(event->keysym.scancode == SDL_SCANCODE_DOWN){
            game.down = 0;
        }
        if(event->keysym.scancode == SDL_SCANCODE_LEFT){
            game.left = 0;
        }
        if(event->keysym.scancode == SDL_SCANCODE_RIGHT){
            game.right = 0;
        }
    }
}

void input(void){
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;
            case SDL_KEYDOWN:
                keytrue(&event.key);
                break;
            case SDL_KEYUP:
                keyfalse(&event.key);
                break;
			default:
				break;
		}
	}
}

void prepare(void){
	SDL_SetRenderDrawColor(game.renderer, 255, 255, 255, 255);
	SDL_RenderClear(game.renderer);
}

void update(void)
{
	SDL_RenderPresent(game.renderer);
}

SDL_Texture* loadtexture(char * filename){
    SDL_Texture * texture;
    texture = IMG_LoadTexture(game.renderer, filename);
    return texture;
}

void show(SDL_Texture* texture, int x, int y){
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(game.renderer, texture, NULL, &dest);
}

