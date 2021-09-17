#ifndef RENDER_WRAP_H
#define RENDER_WRAP_H

#include "SDL2/SDL.h"

#define ENTITY_MAX_BEHAVIOURS 10

typedef struct entity__ {
	SDL_Texture* ent_texture;
	char* texture_name;
	SDL_Rect* ent_rect;
	SDL_bool hidden;
	/*SDL_bool run_behaviours;


	NOTE: something i gave up on
	char **behaviour_names;
	void (*behaviours[10])(struct entity__*, void*);
	void (*arguments[10]);
	*/
} Entity ;

// NOTE: init and exit funcs 

int init_img(SDL_Renderer* renderer);
void quit_img();

float lerp_float(float a, float b, float f);

/*
	NOTE: Collision funcs 
*/

SDL_bool check_collision(Entity* ent_a, Entity* ent_b);

/**	
	NOTE: Rendering funcs 
*/

void draw_ent(Entity* ent_to_draw);
int replace_sprite(Entity* , char* );

/**
	NOTE: Entity movement related funcs
*/

void set_ent_pos(Entity* ent, int new_x, int new_y);

void set_ent_pos_point(Entity* ent, SDL_Point pt);

int get_x(Entity* ent);
int get_y(Entity* ent);

void set_ent_y(Entity* ent, int _y);
void set_ent_x(Entity* ent, int _x);

void move_y(Entity* ent, int change);
void move_x(Entity* ent, int change);

/**
	NOTE: Point manipulation funcs 
*/

void pt_plus(SDL_Point pt1, SDL_Point pt2);
void pt_minus(SDL_Point pt1, SDL_Point pt2);

float dist_pt(SDL_Point a, SDL_Point b);

/** 
	NOTE: Entity loading funcs 
*/

Entity* create_entity(char *filename, int _x, int _y);

SDL_Texture* load_image(char *filename);

/**	
	NOTE: Behaviours (note, this is gonna get messy :/)
*/

void add_behaviour(Entity* ent, void* func, int args, char* );
void run_next_behaviour(Entity* ent); // NOTE: Limitations: only functions with an ent pointer at the start can 
									  // be used.
void run_behaviour(Entity* ent, int index);

/** 
misc 
*/

void who_is(Entity* );


#endif