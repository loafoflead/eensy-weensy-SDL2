#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#include "RenderWrap.h"
#include "general.h"

SDL_Renderer* renderer;


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

SDL_bool check_collision(Entity* ent_a, Entity* ent_b) {

	/* REF:
	0				5
  0 °---------------° 0
	|				|
	|				|
	|				|
  5 °---------------° 5
	0				5
	*/

	SDL_Point temp_pt; /* NOTE: TOP LEFT */
	temp_pt.x = ent_a->ent_rect->x;
	temp_pt.y = ent_a->ent_rect->y;

	if (SDL_PointInRect(&temp_pt, ent_b->ent_rect) == SDL_TRUE) {
		return SDL_TRUE;
	}

	/* NOTE: TOP RIGHT */
	temp_pt.x = ent_a->ent_rect->x + ent_a->ent_rect->w;
	temp_pt.y = ent_a->ent_rect->y;

	if (SDL_PointInRect(&temp_pt, ent_b->ent_rect) == SDL_TRUE) {
		return SDL_TRUE;
	}

	/* NOTE: BOTTOM LEFT */
	temp_pt.x = ent_a->ent_rect->x;
	temp_pt.y = ent_a->ent_rect->y + ent_a->ent_rect->h;

	if (SDL_PointInRect(&temp_pt, ent_b->ent_rect) == SDL_TRUE) {
		return SDL_TRUE;
	}

	/* NOTE: BOTTOM RIGHT */
	temp_pt.x = ent_a->ent_rect->x + ent_a->ent_rect->w;
	temp_pt.y = ent_a->ent_rect->y + ent_a->ent_rect->h;

	if (SDL_PointInRect(&temp_pt, ent_b->ent_rect) == SDL_TRUE) {
		return SDL_TRUE;
	}

	return SDL_FALSE;

}

Entity* create_entity(char *filename, int _x, int _y) {

	Entity* to_return = (Entity* ) malloc(sizeof(Entity));

	// NOTE: texture

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

	// NOTE: names

	to_return-> texture_name = (char* ) malloc(sizeof(filename));

	strcpy(to_return->texture_name, filename);

	// NOTE: rects: boundary boxes

	SDL_Rect* new_ent_rect = (SDL_Rect* ) malloc(sizeof(SDL_Rect));

	new_ent_rect->x = _x;
	new_ent_rect->y = _y;

	new_ent_rect->w = surface_ptr->w;
	new_ent_rect->h = surface_ptr->h;

	to_return->ent_rect = new_ent_rect;

	// NOTE: booleans

	to_return->hidden = SDL_FALSE; //sets hidden to false (draws entity)


	free(surface_ptr);
	return to_return;

}

void draw_ent_center(Entity* ent_to_draw) {

	SDL_Rect rect_ptr = *ent_to_draw->ent_rect;

	rect_ptr.x -= (rect_ptr.w / 2);
	rect_ptr.y -= (rect_ptr.h / 2);

	SDL_RenderCopy(renderer, ent_to_draw->ent_texture, NULL, &rect_ptr);

}

void draw_ent(Entity* ent_to_draw) {

	SDL_RenderCopy(renderer, ent_to_draw->ent_texture, NULL, ent_to_draw->ent_rect);

}

int replace_sprite(Entity* ent, char* filename) {

	if (strcmp(ent->texture_name, filename) == 0) {
		return 2;
	}

	SDL_Texture* new_texture = load_image(filename);

	if(new_texture == NULL) {
		return 1;
	}

	ent->ent_texture = new_texture;
	strcpy(ent->texture_name, filename);
	fprintf(stderr, "texture replaced\n");
	return 0;

}

int get_x(Entity* ent) {
	return ent->ent_rect->x;
}

int get_y(Entity* ent) {
	return ent->ent_rect->y;
}

void set_ent_x(Entity* ent, int _x) {
	ent->ent_rect->x = _x;
}

void set_ent_y(Entity* ent, int _y) {
	ent->ent_rect->y = _y;
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

SDL_Texture* load_image(char *filename) {

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

void who_is(Entity* ent) {

	fprintf(stderr, "ent texture name: \033[1;31m%s\033[0m\n", ent->texture_name);

	fprintf(stderr, "ent pos: x:\033[1;31m%d\033[0m, y:\033[1;31m%d\033[0m\n", ent->ent_rect->x, ent->ent_rect->y);
	fprintf(stderr, "ent size: w:\033[1;31m%d\033[0m, h:\033[1;31m%d\033[0m\n", ent->ent_rect->w, ent->ent_rect->h);

	fprintf(stderr, "ent hidden: \033[1;31m%d\033[0m\n", ent->hidden);
	
}