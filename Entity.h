#ifndef ENTITY_HEADER_H
#define ENTITY_HEADER_H

#include <SDL2/SDL.h>
#include "RenderWrap.h"

enum entity_properties {
	DEBUG_DRAWING = 0,
	HIDDEN = 1,
	XPOS = 2,
	YPOS = 3,
	WIDTH = 4,
	HEIGHT = 5,
	DIR = 6,
	SPEED = 7,
};


typedef struct v2 {
	int x, y;
	float direction, distance;
} v2 ;


typedef struct entity__ {
	
	/// @NOTE: The SDL_Texture object that our entity is drawn as
	SDL_Drawable ent_drawable;
	
	/// @NOTE: The name of the texture file that is stored in 'ent_texture'
	char* texture_name;
	
	/// @NOTE: The SDL_Rect where our entity is drawn and at what dimensions @ps: can be debugged by setting 'debug' to SDL_TRUE
	SDL_Rect* ent_rect;
	
	/// @NOTE: Whether or not the sprite is drawn on a render pass
	short int hidden;
	
	/// @NOTE: the velocity and direction of the entity 
	v2* velocity; 

	/// @NOTE: Whether the sprite's debug box is drawn on a render pass
	short int debug;
	
} Entity ;


typedef struct collision__ {
	Entity* a;
	Entity* b;
	SDL_Point collision_point;
} Collision ;



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

void update_rect_to_texture(Entity* ent);
void update_texture_to_rect(Entity* ent);

/**
	@NOTE: Entity movement related funcs
*/

/*************************
	@NOTE: Position
*************************/

/* get and set entity velocity var */
v2 get_velocity(Entity* ent);
void set_velocity(Entity* ent, v2 new_vec);

/* add to the speed and direction vars */
void add_force(Entity* ent, float speed, float direction);

/* change entity direction */
void add_direction(Entity* ent, float amount);
void set_direction(Entity* ent, float amount);
float get_direction(Entity* ent);

/* change entity speed */
void add_speed(Entity* ent, float incr);
void set_speed(Entity* ent, float new_speed);
float get_speed(Entity* ent);

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

void set_debug(Entity* ent, int boo);

void set_hidden(Entity* ent, int boo);

SDL_bool get_debug(Entity* ent);

SDL_bool get_hidden(Entity* ent);


/** 
	@NOTE: Entity loading funcs 
*/

Entity* create_entity(char *filename, int _x, int _y);


void destroy_entity(Entity** ent);

// fill an ent using a pointer to it's instance
void fill_ent(Entity* ent, char* filename, int x, int y);

// free all pointers in an instance of an entity using a ref to it 
void free_ent(Entity* ent);


/**	
	@NOTE: Behaviours (note, this is gonna get messy :/)
*/

void set_action(Entity* ent, void (*func)(void *));
void run_action(Entity* ent, void *args);
void remove_action(Entity* ent);

/* old */

void add_behaviour(Entity* ent, void* func, int args, char* );
void run_next_behaviour(Entity* ent); // NOTE: Limitations: only functions with an ent pointer at the start can 
									  // be used.
void run_behaviour(Entity* ent, int index);



/** 
misc 
*/

void who_is(Entity* ); /* give debug info on an entity */

void tell_collision(Collision* col); /* give debug info on a collision object */



#endif
