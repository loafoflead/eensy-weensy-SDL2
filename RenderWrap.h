#ifndef RENDER_WRAP_H
#define RENDER_WRAP_H

#include "SDL2/SDL.h"

SDL_Renderer* renderer;

SDL_Texture* err_texture;

typedef struct v2 {
	int x, y;
	float direction, distance;
} v2 ;

typedef struct entity__ {
	
	/// @NOTE: The SDL_Texture object that our entity is drawn as
	SDL_Texture* ent_texture;
	
	/// @NOTE: The name of the texture file that is stored in 'ent_texture'
	char* texture_name;
	
	/// @NOTE: The SDL_Rect where our entity is drawn and at what dimensions @ps: can be debugged by setting 'debug' to SDL_TRUE
	SDL_Rect* ent_rect;
	
	/// @NOTE: Whether or not the sprite is drawn on a render pass
	SDL_bool hidden;
	
	/// @NOTE: the velocity and direction of the entity 
	v2 velocity; 
	
	/// @NOTE: Whether the sprite's debug box is drawn on a render pass
	SDL_bool debug;
	
} Entity ;

typedef struct SDLPLUS_Drawable {
	SDL_Texture* texture;
	SDL_Rect rect;
} SDLPLUS_Drawable ;

Entity* err_entity;


typedef struct collision__ {
	Entity* a;
	Entity* b;
	SDL_Point collision_point;
} Collision ;

/// @NOTE: init and exit funcs 

int init_img(SDL_Renderer* renderer);
void quit_img();

float lerp_float(float a, float b, float f);



/**
	@NOTE: Collision funcs 
*/

SDL_bool check_collision(Entity* ent_a, Entity* ent_b);
Collision get_collision(Entity* ent_a, Entity* ent_b);

void get_collision_obj(Entity* ent_a, Entity* ent_b, Collision* collision_object);

/**	
	@NOTE: Rendering funcs 
*/

void draw_ent(Entity* ent_to_draw);
void draw_ent_center(Entity* ent_to_draw);
int replace_sprite(Entity* , char* );

void draw_debug(Entity* ent);



/**
	@NOTE: Entity movement related funcs
*/

/*************************
	@NOTE: Position
*************************/

/* get and set entity velocity var */
v2 get_velocity(Entity* ent);
void set_velocity(Entity* ent, v2 new_vec);

/* change entity direction */
void add_direction(Entity* ent, float amount);
void set_direction(Entity* ent, float amount);
int get_direction(Entity* ent);

/* change entity speed */
void add_speed(Entity* ent, float incr);
void set_speed(Entity* ent, float new_speed);
int get_speed(Entity* ent);

/* update ent position based on speed and direction */
void update_ent(Entity* ent);
void update_ent_precise(Entity* ent);

/* Copy and paste functions for an entity's position */
SDL_Point save_ent_pos(Entity* ent);
void restore_ent_pos(Entity* ent, SDL_Point saved_pt);

/* Sets the position of the entity to the position given */
void set_ent_pos(Entity* ent, int new_x, int new_y);

/* sets the entities position according to a point */
void set_ent_pos_point(Entity* ent, SDL_Point pt);

/* get position of specified entity */
int get_x(Entity* ent);
int get_y(Entity* ent);

/* set en entity's postion */
void set_ent_y(Entity* ent, int _y);
void set_ent_x(Entity* ent, int _x);

/* change an entity's position by the values given */
void move_y(Entity* ent, int change);
void move_x(Entity* ent, int change);

/* change an entity's x and y by the value given */
void move_xy(Entity* ent, int xpl, int ypl);

/**************************
	@NOTE: Dimensions
**************************/

/* get center of an entity */
SDL_Point get_center(Entity* ent);

/* get the dimensions of a specified entity */
int get_width(Entity* ent);
int get_height(Entity* ent);

/* set the dimesnsions of a specified entity */
void set_height(Entity* ent, int value);
void set_width(Entity* ent, int value);

/* increment dimensions */
void add_width(Entity* ent, int value);
void add_height(Entity* ent, int value);

/* change the dimensions of an entity by a value */
void change_height(Entity* ent, int value);
void change_width(Entity* ent, int value);



/**
	@NOTE: Point manipulation funcs 
*/

void pt_plus(SDL_Point pt1, SDL_Point pt2);
void pt_minus(SDL_Point pt1, SDL_Point pt2);

float dist_pt(SDL_Point a, SDL_Point b);



/** 
	@NOTE: Entity loading funcs 
*/

Entity* create_entity(char *filename, int _x, int _y);

SDL_Texture* load_image(char *filename);

void destroy_entity(Entity* ent);

/**	
	@NOTE: Behaviours (note, this is gonna get messy :/)
*/

void add_behaviour(Entity* ent, void* func, int args, char* );
void run_next_behaviour(Entity* ent); // NOTE: Limitations: only functions with an ent pointer at the start can 
									  // be used.
void run_behaviour(Entity* ent, int index);



/** 
misc 
*/

void who_is(Entity* ); /* give debug info on an entity */
void tell_rect(SDL_Rect* rect); /* give basic debug info on an sdl_rect */
void tell_collision(Collision* col); /* give debug info on a collision object */

#endif