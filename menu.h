#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct Text{
    int x;
    int y;
    SDL_Color c;
    const char* message;
    int size;
};

struct Text text;

