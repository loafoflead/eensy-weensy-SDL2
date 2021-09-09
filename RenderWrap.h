#ifndef RENDER_WRAP_H
#define RENDER_WRAP_H

#include "SDL2/SDL.h"

typedef struct {
	SDL_Texture* ent_texture;
	SDL_Rect* ent_rect;
} Entity ;

int init_img();
void quit_img();

void draw_ent(Entity* ent_to_draw, SDL_Renderer* renderer);

void RenderCopyList(SDL_Renderer* renderer);

void set_ent_pos(Entity* ent, int new_x, int new_y);

void set_ent_pos_point(Entity* ent, SDL_Point pt);

void move_y(Entity* ent, int change);

void move_x(Entity* ent, int change);

Entity* create_entity(char *filename, SDL_Renderer* renderer, int _x, int _y);

SDL_Texture* load_image(char *filename, SDL_Renderer *renderer);

#endif