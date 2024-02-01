
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define WIDTH 1280
#define HEIGHT 720

//IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

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
} App;

App app;

struct Bombardier{
    int x;
    int y;
    int dx;
    int dy;
    int health;
    //SDL_Texture* texture;
    //struct Bombardier* next;
};

void init(void){
    int rendererflags, windowflags;
    rendererflags = SDL_RENDERER_ACCELERATED;
    windowflags = 0;
    if(SDL_Init(SDL_INIT_VIDEO < 0)){
        printf("ERROR %s\n", SDL_GetError());
        exit(-1);
    }
    app.window = SDL_CreateWindow("<---My first game--->", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, windowflags);
    if(!app.window){
        printf("Failed! %s\n", SDL_GetError());
        exit(-1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app.renderer = SDL_CreateRenderer(app.window, -1, rendererflags);
    if(!app.renderer){
        printf("ERROR ! %s\n", SDL_GetError());
        exit(-1);
    }

}

void dokeydown(SDL_KeyboardEvent * event){
    if(event->repeat == 0){
        if(event->keysym.scancode == SDL_SCANCODE_SPACE){
            app.fire = 1;
        }
        if(event->keysym.scancode == SDL_SCANCODE_UP){
            app.up = 1;
        }
        if(event->keysym.scancode == SDL_SCANCODE_DOWN){
            app.down = 1;
        }
        if(event->keysym.scancode == SDL_SCANCODE_LEFT){
            app.left = 1;
        }
        if(event->keysym.scancode == SDL_SCANCODE_RIGHT){
            app.right = 1;
        }
    }
}

void dokeyup(SDL_KeyboardEvent * event){
    if(event->repeat == 0){
        if(event->keysym.scancode == SDL_SCANCODE_SPACE){
            app.fire = 0;
        }
        if(event->keysym.scancode == SDL_SCANCODE_UP){
            app.up = 0;
        }
        if(event->keysym.scancode == SDL_SCANCODE_DOWN){
            app.down = 0;
        }
        if(event->keysym.scancode == SDL_SCANCODE_LEFT){
            app.left = 0;
        }
        if(event->keysym.scancode == SDL_SCANCODE_RIGHT){
            app.right = 0;
        }
    }
}

void doInput(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;
            case SDL_KEYDOWN:
                dokeydown(&event.key);
                break;
            case SDL_KEYUP:
                dokeyup(&event.key);
                break;
			default:
				break;
		}
	}
}

void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
	SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
	SDL_RenderPresent(app.renderer);
}

SDL_Texture* loadtexture(char * filename){
    SDL_Texture * texture;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    texture = IMG_LoadTexture(app.renderer, filename);
    return texture;
}

void blit(SDL_Texture* texture, int x0, int y0){
    SDL_Rect dest;
    dest.x = x0;
    dest.y = y0;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);

}

