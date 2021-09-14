#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#include "RenderWrap.h"
#include "general.h"

void add_behaviour(Entity* ent, void* func, void* args, char* name) {
	
		ent->behaviour_names[0] = (char *) malloc(sizeof(name));
		strcpy(ent->behaviour_names[0], name);
		ent->behaviours[0] = func;
		ent->arguments[0] = args;
		ent->behaviour_count ++;
	
}

void run_behaviour(Entity* ent, int index) {

	if (ent->behaviours[index] == NULL) {
		return;
	}

	(*ent->behaviours[index])(ent, ent->arguments[index]);

}



int index_of_latest = 0;

void run_next_behaviour(Entity* ent) {

	if (ent->behaviours[index_of_latest] == NULL) {
		index_of_latest = 0;
		return;
	}

	(*ent->behaviours[index_of_latest])(ent, ent->arguments[index_of_latest]);
	index_of_latest ++;
	if (ent->behaviours[index_of_latest] == NULL) {
		index_of_latest = 0;
	}

}

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

	to_return-> texture_name = (char* ) malloc(sizeof(filename));

	strcpy(to_return->texture_name, filename);

	to_return->behaviour_names = (char **) malloc(sizeof(char *) * 10);

	SDL_Rect* new_ent_rect = (SDL_Rect* ) malloc(sizeof(SDL_Rect));

	new_ent_rect->x = _x;
	new_ent_rect->y = _y;

	new_ent_rect->w = surface_ptr->w;
	new_ent_rect->h = surface_ptr->h;

	to_return->ent_rect = new_ent_rect;

	to_return->hidden = SDL_FALSE;
	to_return->run_behaviours = SDL_TRUE;
	to_return->behaviour_count = 0;

	free(surface_ptr);
	return to_return;

}

void draw_ent(Entity* ent_to_draw, SDL_Renderer* renderer) {

	SDL_RenderCopy(renderer, ent_to_draw->ent_texture, NULL, ent_to_draw->ent_rect);

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

void who_is(Entity* ent) {

	fprintf(stderr, "ent texture name: \033[1;31m%s\033[0m\n", ent->texture_name);

	fprintf(stderr, "ent pos: x:\033[1;31m%d\033[0m, y:\033[1;31m%d\033[0m\n", ent->ent_rect->x, ent->ent_rect->y);
	fprintf(stderr, "ent size: w:\033[1;31m%d\033[0m, h:\033[1;31m%d\033[0m\n", ent->ent_rect->w, ent->ent_rect->h);

	fprintf(stderr, "ent hidden: \033[1;31m%d\033[0m\n", ent->hidden);
	fprintf(stderr, "ent run behaviours: \033[1;31m%d\033[0m\n", ent->run_behaviours);

	fprintf(stderr, "ent behaviour count: \033[1;31m%d\033[0m\n", ent->behaviour_count);

	for (int i = 0; i < ent->behaviour_count; i ++) {
		if (ent->behaviour_names[i] != NULL) {
			fprintf(stderr, "[\033[1;31m%s\033[0m,]:", ent->behaviour_names[i], ent->arguments[i]);
		}
	}

	fprintf(stderr, "\n\033[1;35m----------------------\033[0m\n");

}