#ifndef GENERAL__H
#define GENERAL__H value

#include "SDL2/SDL.h"

void toggle_bool(SDL_bool* );
int sizeof_arr(void* array);
void repeat_func(int times, void* function, void* arg);

void go_to(int x, int y);

#endif