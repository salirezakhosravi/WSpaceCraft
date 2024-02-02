#include <stdio.h>
#include <SDL2/SDL.h>
#include "menu.h"

typedef struct {
    int x;
    int y;
    SDL_Color c;
    const char* message;
    int size;
} Text;

Text box;
box.x;