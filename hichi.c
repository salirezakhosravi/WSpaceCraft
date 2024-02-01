/*
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define WIDTH 1280
#define HEIGHT 720

//IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
    int health;
    SDL_Texture * texture;
} ship;

ship player;

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

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "menu.h"

/*typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
} App;

App app;*/

/*#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

int main(int argc, char *argv[])
{
    ship bullet;
	memset(&app, 0, sizeof(App));
	memset(&player, 0, sizeof(ship));
    memset(&bullet, 0, sizeof(ship));
	init();
	//atexit(free(&app));

	player.x = 620;
	player.y = 650;
	player.texture = loadtexture("ship6_0.png");

    bullet.texture = loadtexture("laserBullet.png");


	while (1)
	{
		prepareScene();

		doInput();

        //player.x = player.dx;
        //player.y = player.dy;

        if(app.up){
            player.y -=4;
        }
        if(app.down){
            player.y +=4;
        }
        if(app.left){
            player.x -=4;
        }
        if(app.right){
            player.x +=4;
        }
        if(app.fire && bullet.health==0){
            bullet.x = player.x;
            bullet.y = player.y;
            bullet.dy = 55;
            bullet.dx = 0;
            bullet.health = 1;
        }

        bullet.y -= bullet.dy;
        bullet.x += bullet.dx;

        if(bullet.y < 0){
            bullet.health = 0;
        }

		blit(player.texture, player.x, player.y);

        if(bullet.health > 0){
            blit(bullet.texture, bullet.x, bullet.y);
        }

		presentScene();

		SDL_Delay(16);
	}
	//free(&app);
	//free(&player);
	return 0;
}*/



















/*#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define WIDTH 1280
#define HEIGHT 720
#define MAX_KEYBOARD_KEYS 350
#define PLAYER_SPEED 50
#define PLAYER_BULLET_SPEED 16

//IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

typedef struct{
    void (*logic)(void);
    void (*draw)(void);
} Delegate;

struct ship{
    float x;
    float y;
    int w;
    int h;
    float dx;
    float dy;
    int health;
    int reload;
    SDL_Texture * texture;
    struct ship* next;
};


typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
    Delegate delegate;
    int keyboard[MAX_KEYBOARD_KEYS];
} App;

App app;

typedef struct{
    struct ship fighterhead, *fightertail;
    struct ship bullethead, *bullettail;
} Stage;

Stage stage;

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
    if((event->repeat = 0) && ((int)event->keysym.scancode < MAX_KEYBOARD_KEYS)){
        app.keyboard[(int)event->keysym.scancode] = 1;
    }
}

void dokeyup(SDL_KeyboardEvent * event){
    if((event->repeat = 0) && ((int)event->keysym.scancode < MAX_KEYBOARD_KEYS)){
        app.keyboard[(int)event->keysym.scancode] = 0;
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

SDL_Texture* bulletTexture;

struct ship* player;

static void initPlayer(){
    player = (struct ship *) malloc(sizeof(struct ship));
    memset(player,0,sizeof(struct ship));
    stage.fightertail->next = player;
    stage.fightertail = player;

    player->x = 620;
    player->y = 650;
    player->texture = loadtexture("ship6_0.png");
    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

static void fireBullet(void){
    struct ship* bullet;
    bullet = (struct ship *) malloc(sizeof(struct ship));
    memset(bullet, 0, sizeof(struct ship));
    stage.bullettail->next = bullet;
    stage.bullettail = bullet;

    bullet->x = player->x;
    bullet->y = player->y;
    bullet->dy = -PLAYER_BULLET_SPEED;
    bullet->health = 1;
    bullet->texture = bulletTexture;
    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
    bullet->y -= (player->h / 2) - (bullet->h / 2);
    player->reload = 8; 
}

static void doPlayer(void){
    player->dx = player->dy = 0;
    if(player->reload > 0){
        player->reload--;
    }
    if(app.keyboard[SDL_SCANCODE_UP]){
        player->dy = -PLAYER_SPEED;
    }
    if(app.keyboard[SDL_SCANCODE_DOWN]){
        player->dy = PLAYER_SPEED;
    }
    if(app.keyboard[SDL_SCANCODE_RIGHT]){
        player->dx = PLAYER_SPEED;
    }
    if(app.keyboard[SDL_SCANCODE_LEFT]){
        player->dx = -PLAYER_SPEED;
    }
    if(app.keyboard[SDL_SCANCODE_SPACE] && player->reload == 0){
        fireBullet();
    }

    player->x += player->dx;
    player->y += player->dy;
}

static void doBullets(void){
    struct ship* current, *prev;
    prev = &stage.bullethead;

    for(current = stage.bullethead.next; current != NULL; current = current->next){
        current->x += current->dx;
        current->y -= current->dy;

        if(current->y < 0){
            if(current == stage.bullettail){
                stage.bullettail = prev;
            }
            prev->next = current->next;
            free(current);
            current = prev;
        }
        prev = current;
    }
}

static void logic(void){
    doPlayer();
    doBullets();
}

static void drawplayer(void){
    blit(player->texture, player->x, player->y);
}

static void drawbullets(void){
    struct ship* shot;
    for(shot = stage.bullethead.next; shot != NULL; shot = shot->next){
        blit(shot->texture, shot->x, shot->y);
    }
}

static void draw(void){
    drawplayer();
    drawbullets();
}

void initstage(void){
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    memset(&stage, 0 , sizeof(stage));
    stage.fightertail = &stage.fighterhead;
    stage.bullettail = &stage.bullethead;
    initPlayer();
    bulletTexture = loadtexture("laserBullet.png");
}



#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "menu.h"

/*typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
} App;

App app;*/

/*static void capFrameRate(long int *num, float *remainder){
    long int wait, frametime;
    wait = 16 + *remainder;
    *remainder -= (int) * remainder;
    frametime = SDL_GetTicks() - *num;
    wait -= frametime;
    if(wait < 1){
        wait = 1;
    }

    SDL_Delay(wait);
    *remainder += 0.667;
    *num = SDL_GetTicks();
}

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

int main(int argc, char *argv[]){
    long int num;
    float remainder;
    memset(&app, 0, sizeof(App));
    
    init();

    initstage();

    num = SDL_GetTicks();
    remainder = 0;
    while(true){
        prepareScene();
        doInput();
        app.delegate.logic();
        app.delegate.draw();
        presentScene();
        capFrameRate(&num, &remainder);
    }
    return 0;
}*/