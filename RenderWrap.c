#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWrap.h"

Entity* create_entity(char *filename, SDL_Renderer* renderer, int _x, int _y) {

	Entity* to_return = (Entity* ) malloc(sizeof(Entity));

	SDL_RWops* rwop = SDL_RWFromFile(filename, "rb");
	SDL_Surface *surface_ptr = IMG_LoadPNG_RW(rwop);

	if (!surface_ptr) {
		fprintf(stderr, "Failed to load png %s: %s\n", filename, IMG_GetError());
		return NULL;
	}

	to_return->ent_texture = SDL_CreateTextureFromSurface(renderer, surface_ptr);

	if (!to_return->ent_texture) {
		fprintf(stderr, "Failed to load texture: %s\n", SDL_GetError());
		return NULL;
	}

	SDL_Rect* new_ent_rect = (SDL_Rect* ) malloc(sizeof(SDL_Rect));

	new_ent_rect->x = _x;
	new_ent_rect->y = _y;

	new_ent_rect->w = surface_ptr->w;
	new_ent_rect->h = surface_ptr->h;

	to_return->ent_rect = new_ent_rect;

	free(surface_ptr);
	return to_return;

}

void draw_ent(Entity* ent_to_draw, SDL_Renderer* renderer) {

	SDL_RenderCopy(renderer, ent_to_draw->ent_texture, NULL, ent_to_draw->ent_rect);

}

void set_ent_pos(Entity* ent, int new_x, int new_y) {
	ent->ent_rect->x = new_x;
	ent->ent_rect->y = new_y;
}

void set_ent_pos_point(Entity* ent, SDL_Point pt) {
	ent->ent_rect->x = pt.x;
	ent->ent_rect->y = pt.y;
}

void move_x(Entity* ent, int change) {
	ent->ent_rect->x += change;
}

void move_y(Entity* ent, int change) {
	ent->ent_rect->y += change;
}

int init_img(void) {
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

SDL_Texture* load_image(char *filename, SDL_Renderer *renderer) {

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