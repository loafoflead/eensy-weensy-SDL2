#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#include "RenderWrap.h"
#include "general.h"

SDL_Point debug_points[5]; /* debug points used to draw hitboxes */

Collision collision_object_static; /* reusable collision object */

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
	
	if (ent_a == NULL || ent_b == NULL) {
		return SDL_FALSE; /* safeguard null ptrs */
	}

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

Collision get_collision(Entity* ent_a, Entity* ent_b) {
	
	Collision col = {NULL, NULL, {0, 0}};

	if (ent_a == NULL || ent_b == NULL) {
		return col; /* safeguard null ptrs */
	}

	SDL_Point temp_pt; /* NOTE: TOP LEFT */
	temp_pt.x = ent_a->ent_rect->x;
	temp_pt.y = ent_a->ent_rect->y;

	if (SDL_PointInRect(&temp_pt, ent_b->ent_rect) == SDL_TRUE) {
		col.a = ent_a;
		col.b = ent_b;
		col.collision_point = temp_pt;
	}

	/* NOTE: TOP RIGHT */
	temp_pt.x = ent_a->ent_rect->x + ent_a->ent_rect->w;
	temp_pt.y = ent_a->ent_rect->y;

	if (SDL_PointInRect(&temp_pt, ent_b->ent_rect) == SDL_TRUE) {
		col.a = ent_a;
		col.b = ent_b;
		col.collision_point = temp_pt;
	}

	/* NOTE: BOTTOM LEFT */
	temp_pt.x = ent_a->ent_rect->x;
	temp_pt.y = ent_a->ent_rect->y + ent_a->ent_rect->h;

	if (SDL_PointInRect(&temp_pt, ent_b->ent_rect) == SDL_TRUE) {
		col.a = ent_a;
		col.b = ent_b;
		col.collision_point = temp_pt;
	}

	/* NOTE: BOTTOM RIGHT */
	temp_pt.x = ent_a->ent_rect->x + ent_a->ent_rect->w;
	temp_pt.y = ent_a->ent_rect->y + ent_a->ent_rect->h;

	if (SDL_PointInRect(&temp_pt, ent_b->ent_rect) == SDL_TRUE) {
		col.a = ent_a;
		col.b = ent_b;
		col.collision_point = temp_pt;
	}

	return col;
	
}

void get_collision_obj(Entity* ent_a, Entity* ent_b, Collision* collision_object) {
	
	collision_object_static = get_collision(ent_a, ent_b);
	
	if (collision_object_static.a == NULL)
		return; /* return if no collision found */
	
	collision_object->a = collision_object_static.a;
	collision_object->b = collision_object_static.b;
	
	collision_object->collision_point = collision_object_static.collision_point;
	
}
	

void destroy_entity(Entity* ent) {
	SDL_DestroyTexture(ent->ent_texture);
	free(ent);
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
	
	to_return->velocity.x = _x;
	to_return->velocity.y = _y;
	
	to_return->velocity.direction = 0;
	to_return->velocity.distance = 0;

	// NOTE: booleans

	to_return->hidden = SDL_FALSE; //sets hidden to false (draws entity)
	to_return->debug = SDL_FALSE; // sets debug to false (draws hitbox)

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

void draw_debug(Entity* ent) {

	SDL_Point tempo = {get_x(ent), get_y(ent)};  /* *------| */
	debug_points[0] = tempo;

	tempo.x = get_x(ent) + get_width(ent);		 /* |------* */
	tempo.y = get_y(ent);
	debug_points[1] = tempo;

	tempo.x = get_x(ent) + get_width(ent);		 /* |------* (down) */
	tempo.y = get_y(ent) + get_height(ent);
	debug_points[2] = tempo;

	tempo.x = get_x(ent);
	tempo.y = get_y(ent) + get_height(ent);
	debug_points[3] = tempo;

	tempo.x = get_x(ent);		 /* |------* */
	tempo.y = get_y(ent);
	debug_points[4] = tempo;

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
	
	SDL_RenderDrawLines(renderer, debug_points, 5);
	
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	
	SDL_RenderDrawLine(renderer, 
		get_center(ent).x, 
		get_center(ent).y, 
		get_center(ent).x + (cos(ent->velocity.direction) * 100), 
		get_center(ent).y + (sin(ent->velocity.direction) * 100)
	);

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

SDL_Point save_ent_pos(Entity* ent) {
	SDL_Point p = {ent->ent_rect->x, ent->ent_rect->y};
	return p;
}

void restore_ent_pos(Entity* ent, SDL_Point saved_pt) {
	set_ent_x(ent, saved_pt.x);
	set_ent_y(ent, saved_pt.y);
}

v2 get_velocity(Entity* ent) {
	return ent->velocity;
}

void set_velocity(Entity* ent, v2 new_vec) {
	ent->velocity = new_vec;
}

void add_direction(Entity* ent, float amount) {
	if ((ent->velocity.direction + amount) > 360) {
		ent->velocity.direction = (ent->velocity.direction + amount) - 360;
	}
	else if ((ent->velocity.direction + amount) < 0) {
		ent->velocity.direction = (ent->velocity.direction + amount) + 360;
	}
	else {
		ent->velocity.direction += amount;
	}
}

void set_direction(Entity* ent, float amount) {
	if (amount > 360) {
		ent->velocity.direction = 360;
	}
	else if (amount < 0) {
		ent->velocity.direction = 0;
	}
	else {
		ent->velocity.direction = amount;
	}
}

int get_direction(Entity* ent) {
	return ent->velocity.direction;
}

void add_speed(Entity* ent, float incr) {
	ent->velocity.distance += incr;
}

void set_speed(Entity* ent, float new_speed) {
	ent->velocity.distance = new_speed;
}

int get_speed(Entity* ent) {
	return ent->velocity.distance;
}

void update_ent(Entity* ent) {
	move_x(ent, (float) cos(ent->velocity.direction) * ent->velocity.distance); ///@Note: ??? idk some math magic lowl
	move_y(ent, (float) sin(ent->velocity.direction) * ent->velocity.distance);
}

void update_ent_precise(Entity* ent) {
	move_x(ent, cos(ent->velocity.direction) * ent->velocity.distance); ///@Note: ??? idk some math magic lowl
	move_y(ent, sin(ent->velocity.direction) * ent->velocity.distance);
}

int get_x(Entity* ent) {
	return ent->ent_rect->x;
}

int get_y(Entity* ent) {
	return ent->ent_rect->y;
}

void move_xy(Entity* ent, int xpl, int ypl) {
	move_x(ent, xpl);
	move_y(ent, ypl);
}

SDL_Point get_center(Entity* ent) {
	SDL_Point newp = {get_x(ent) + get_width(ent) / 2, get_y(ent) + get_height(ent) / 2};
	return newp;
}

int get_width(Entity* ent) {
	return ent->ent_rect->w;
}

int get_height(Entity* ent) {
	return ent->ent_rect->h;
}

void set_height(Entity* ent, int value) {
	ent->ent_rect->h = value;
}

void add_width(Entity* ent, int value) {
	ent->ent_rect->w += value;
}

void add_height(Entity* ent, int value) {
	ent->ent_rect->h += value;
}

void set_width(Entity* ent, int value) {
	ent->ent_rect->w = value;
}

void change_height(Entity* ent, int value) {
	ent->ent_rect->h += value;
}

void change_width(Entity* ent, int value) {
	ent->ent_rect->w += value;
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
	err_texture = load_image("err_texture.png");
	err_entity = create_entity("err_texture.png", 0, 0);
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
	
	if (!ent) 
		return; /* null ptr guard */

	fprintf(stderr, "ent texture name: \033[1;31m%s\033[0m\n", ent->texture_name);

	fprintf(stderr, "ent pos: x:\033[1;31m%d\033[0m, y:\033[1;31m%d\033[0m\n", ent->ent_rect->x, ent->ent_rect->y);
	fprintf(stderr, "ent size: w:\033[1;31m%d\033[0m, h:\033[1;31m%d\033[0m\n", ent->ent_rect->w, ent->ent_rect->h);

	fprintf(stderr, "ent hidden: \033[1;31m%d\033[0m\n", ent->hidden);
	fprintf(stderr, "ent debugged: \033[1;31m%d\033[0m\n", ent->debug);
	
	fprintf(stderr, 
	"ent velocity: x: \033[1;31m %d \033[0m y: \033[1;31m %d \033[0m\n",
	ent->velocity.x, ent->velocity.y);
	
	fprintf(stderr, 
	"ent direction: \033[1;31m %f \033[0m ent speed: \033[1;31m %f \033[0m\n",
	ent->velocity.direction, ent->velocity.distance);
	
}

void tell_rect(SDL_Rect* rect) {
	if (!rect) 
		return; /* null ptr guard */
	
	fprintf(stderr, "Rect x: %d, y: %d, w: %d, h: %d.\n", rect->x, rect->y, rect->w, rect->h);
}

void tell_collision(Collision* col) {
	if (col == NULL || col->a == NULL || col->b == NULL)
		return; /* null ptr guard */
	
	fprintf(
		stderr, 
		"Collision ent_a->name: %s, x: %d, y: %d, Collision ent_b->name: %s, x: %d, y: %d at pos: x: %d, y: %d.\n", 
		col->a->texture_name, col->a->ent_rect->x, col->a->ent_rect->y, 
		col->b->texture_name, col->b->ent_rect->x, col->b->ent_rect->y,
		col->collision_point.x, col->collision_point.y
	);
}