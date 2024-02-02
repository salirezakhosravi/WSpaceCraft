#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <time.h>
#include "first.h"

int main()
{
    time_t t = time(NULL);
    srand(t);
    struct Enemy doshman;
    struct Enemy mine;
    memset(&doshman, 0, sizeof(struct Enemy));
    memset(&mine, 0, sizeof(struct Enemy));
    doshman.x = (rand() % 2) * WIDTH;
    doshman.y = 0;
    doshman.dx = 2;
    doshman.dy = 1;
    int x1 = doshman.x;

    mine.y = 0;
    mine.x = rand() % WIDTH;
    mine.dx = 0;
    mine.dy = 4;

    struct ship bullet;
    struct ship bomb;
    bomb.dy = 20;
    bomb.dx = 0;
	memset(&game, 0, sizeof(game));
	memset(&player, 0, sizeof(struct ship));
    memset(&bullet, 0, sizeof(struct ship));
    memset(&bomb, 0, sizeof(struct ship));

	init();

	player.x = 620;
	player.y = 650;

	player.texture = loadtexture("ship6_0.png");

    bullet.texture = loadtexture("laserBullet.png");

    bomb.texture = loadtexture("bomb.png"); 

    doshman.texture = loadtexture("images.png");

    mine.texture = loadtexture("alien2_2.png");

	while(1){
		prepare();

		input();

        if(game.up){
            player.y -=4;
            if(player.y <= 0)
                player.y +=4;
        }
        if(game.down){
            player.y +=4;
            if(player.y >= 660)
                player.y -=4;
        }
        if(game.left){
            player.x -=4;
            if(player.x <= 0)
                player.x +=4;
        }
        if(game.right){
            player.x +=4;
            if(player.x >= 1181)
                player.x -=4;
        }
        if(game.fire && bullet.health==0){
            bullet.x = player.x + 6;
            bullet.y = player.y;
            bullet.dy = 100;
            bullet.dx = 0;
            bullet.health = 1;
        }

        bullet.y -= bullet.dy;

        if(bullet.y < -100){
            bullet.health = 0;
        }

		show(player.texture, player.x, player.y);

        if(bullet.health > 0){
            show(bullet.texture, bullet.x, bullet.y);
        }

        if(x1 == 0){
            doshman.x += doshman.dx;
        }
        else if(x1 == WIDTH){
            doshman.x -= doshman.dx;
        }
        doshman.y += doshman.dy;
        if(doshman.y == 200){
            doshman.dy = 0;
        }
        show(doshman.texture, doshman.x, doshman.y);

        mine.y += mine.dy;

        show(mine.texture, mine.x, mine.y);

        if(doshman.x % 10 == 0){
            bomb.x = doshman.x;
            bomb.y = doshman.y;
        }

        show(bomb.texture, bomb.y, bomb.x);

        bomb.y += bomb.dy;        

		update();

		SDL_Delay(16);
	}
	return 0;
}