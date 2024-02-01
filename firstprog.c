#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "first.h"

/*typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
} App;

App app;*/

struct Bombardier{
    int x;
    int y;
    int dx;
    int dy;
    int health;
    //SDL_Texture* texture;
    //struct Bombardier* next;
};

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

int size = 10;

int main(int argc, char *argv[])
{
    struct ship bullet;
	memset(&app, 0, sizeof(App));
	memset(&player, 0, sizeof(struct ship));
    memset(&bullet, 0, sizeof(struct ship));
	init();
	//atexit(free(&app));

	player.x = 620;
	player.y = 650;
	player.texture = loadtexture("ship6_0.png");

    bullet.texture = loadtexture("laserBullet.png");

    SDL_Texture* enemyTexture = loadtexture("craft.png"); 

    //bombardier->texture = enemyTexture;

    struct bombardier bober;
    bober.x;


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
}