#include "general.h"
#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"


void go_to(int x, int y) {
	printf("\033[%d;%dH", x, y);
	fflush(stdout);
}

void toggle_bool(SDL_bool* boolean) {
	if ((*boolean) == 0) {
		*boolean = 1;
	}
	else {
		*boolean = 0;
	}
}

int sizeof_arr(void* array) {
	return( sizeof(array) / sizeof((*array)));
}

void repeat_func(int times, void* function, void* arg) {
	/*for (int i = 0; i < times; i ++) {
		(*function)(arg);
	}*/
}