#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#include "RenderWrap.h"
#include "general.h"



float lerp_float(float a, float b, float f) {
    return (a * (1.0f - f)) + (b * f);
}

void pt_plus(SDL_Point pt1, SDL_Point pt2) {
	pt1.x += pt2.x;
	pt1.y += pt2.y;
}

void pt_minus(SDL_Point pt1, SDL_Point pt2) {
	pt1.x -= pt2.x;
	pt1.y -= pt2.y;
}

float dist_pt(SDL_Point a, SDL_Point b) {
	float distance;
	distance = a.x - b.x;
	distance = distance * distance;
	distance += (a.y - b.y) * (a.y - b.y);
	distance = sqrt(distance);
	return distance;
}


void draw_drawable(SDL_Drawable* db) {
	SDL_RenderCopy(renderer, db->texture, NULL, &db->rect);
}


int init_img(SDL_Renderer* renderer) {
	int flags = IMG_INIT_PNG;
	int result = IMG_Init(0);
	if (result != 0) {
		fprintf(stderr, "SDL_IMAGE: Failed to init: %s\n", IMG_GetError());
		return 1;
	}
	else {
		return 0;
	}
}
void quit_img(void) {
	IMG_Quit();
}

void free_drawable(SDL_Drawable* db) {
	SDL_DestroyTexture(db->texture);
	free(db);
}

SDL_Drawable* load_image_drawable(const char* filename) {
	
	SDL_Drawable* new_draw = (SDL_Drawable* ) malloc(sizeof(SDL_Drawable));
	
	SDL_RWops* rwop = SDL_RWFromFile(filename, "rb");
	SDL_Surface *surface_ptr = IMG_LoadPNG_RW(rwop);

	if (!surface_ptr) {
		fprintf(stderr, "Failed to load png %s: %s\n", filename, IMG_GetError());
		return NULL;
	}

	new_draw->texture = SDL_CreateTextureFromSurface(renderer, surface_ptr);

	if (!new_draw->texture) {
		fprintf(stderr, "Failed to load texture: %s\n", SDL_GetError());
		return NULL;
	}

	new_draw->rect.x = 0;
	new_draw->rect.y = 0;
	
	new_draw->rect.w = surface_ptr->w;
	new_draw->rect.h = surface_ptr->h;

	free(surface_ptr);
	return new_draw;

}


SDL_Texture* load_image(const char *filename) {

	SDL_RWops* rwop = SDL_RWFromFile(filename, "rb");
	SDL_Surface *surface_ptr = IMG_LoadPNG_RW(rwop);

	if (!surface_ptr) {
		fprintf(stderr, "Failed to load png %s: %s\n", filename, IMG_GetError());
		return NULL;
	}

	SDL_Texture* texture_to_return_ptr = SDL_CreateTextureFromSurface(renderer, surface_ptr);

	if (!texture_to_return_ptr) {
		fprintf(stderr, "Failed to load texture: %s\n", SDL_GetError());
		return NULL;
	}

	//SDL_Rect rect;

	//SDL_RenderCopy(renderer, texture_to_return_ptr, NULL, &rect);

	free(surface_ptr);
	return texture_to_return_ptr;

}


void tell_rect(SDL_Rect* rect) {
	if (!rect) 
		return; /* null ptr guard */
	
	fprintf(stderr, "Rect x: %d, y: %d, w: %d, h: %d.\n", rect->x, rect->y, rect->w, rect->h);
}







