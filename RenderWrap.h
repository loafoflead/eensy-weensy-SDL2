#ifndef RENDER_WRAP_H
#define RENDER_WRAP_H

#include "SDL2/SDL.h"

SDL_Renderer* renderer;

typedef struct SDL_Drawable {
	SDL_Texture* texture;
	SDL_Rect rect;
} SDL_Drawable ;

/// @NOTE: init and exit funcs 

int init_img(SDL_Renderer* renderer);
void quit_img();

float lerp_float(float a, float b, float f);

/** @note: rendering **/

void draw_drawable(SDL_Drawable* db);
SDL_Drawable* load_image_drawable(const char* filename);

SDL_Texture* load_image(const char *filename);

void free_drawable(SDL_Drawable* db); /// @warn: only use this function on a pointer, don't reference an instance 

/**
	@NOTE: Point manipulation funcs 
*/

void pt_plus(SDL_Point pt1, SDL_Point pt2);
void pt_minus(SDL_Point pt1, SDL_Point pt2);

float dist_pt(SDL_Point a, SDL_Point b);

/// @misc

void tell_rect(SDL_Rect* rect); /* give basic debug info on an sdl_rect */

#endif