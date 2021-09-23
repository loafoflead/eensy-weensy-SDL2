#include <stdio.h>
#include <SDL2/SDL.h>

#include "RenderWrap.h"
#include "RenderList.h" 
#include "FontRenderWrap.h"
#include "general.h"

#include "animations.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define CLS() printf("\033[H\033[J")

/*
	NOTE: Compiler flags :))
	-lSDL2_image 
	-lSDL2_ttf 
	-lSDL2_mixer
	-lSDL2
	-lSDL2main

	export DISPLAY=:0 <- to make xMing show a picture, make sure to run the app first,
	use the search bar.
*/

/** @NOTE: GAME VARIABLES **/

int world_x = 0;
int world_y = 0;

/* END */

SDL_Window* window;
extern SDL_Renderer* renderer;

SDL_Event event;

SDL_bool is_running = SDL_TRUE;


/** @NOTE: function declarations **/

void initialise_entities(void);

void update_cycle(void);
void handle_input(void);
void game_update(void);

void readouts(void);

void update_world_elements(void);
/**********************************/


/** @NOTE: Variable declarations **/

Entity* boy;
Entity* text_1;

SDL_Point size;

ListElement* entities; /* the entities list, anything that's gonna be interacted with */
ListElement* background; /* true background layer, will have no interactions with entities at all */

SDL_bool is_debug;

SDL_Point point; /* point to re-use */

/**********************************/

int main() {
	
	if (is_running == SDL_FALSE) {
		fprintf(stderr, "Warn: is_running is set to false.");
		return(0);
	}

	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Failed to start SDL.\n");
		exit(8);
	}

	if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer) != 0) {
		fprintf(stderr, "Failed to open window: %s\n", SDL_GetError());
		SDL_Quit();
		exit(8);
	}

	SDL_GetWindowSize(window, &size.x, &size.y);

	init_img(renderer);
	
	initialise_entities();
	
	while (is_running) {
		
		update_cycle();
		
	}

	SDL_Quit();
	quit_img();
	free_list(entities);
	free_list(background);

	return(0);

}

void update_cycle(void) {

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	while(SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			is_running = SDL_FALSE;
		}
		if (event.type == SDL_KEYDOWN) {
			handle_input();
		}
	}

	game_update(); // draw world ents 1st 

	RenderCopyList(entities);

	SDL_RenderPresent(renderer);

}

void initialise_entities(void) {
	
	entities = init_list_ent_ptr(create_entity("boy_idle.png", size.x / 2, size.y /2), "boy");
	boy = find_element(entities, "boy")->ent_ptr;
	
	add_ent(entities, create_entity("earth.png", 0, 0), "ground");
	
	add_ent(entities, create_entity("tree1.png", 0, 100), "\"tree\"");
	add_ent(entities, create_entity("tree1.png", 500, 100), "\"tree2\"");
	
	background = init_list_ent_ptr(create_entity("clouds.png", 0, 0), "clouds_background");
	add_height(index_ls(background, 0)->ent_ptr, 100);
	add_width(index_ls(background, 0)->ent_ptr, 100);
	
}

void game_update(void) {

	RenderCopyListCenter(background);
	update_ent_precise(boy);

	set_ent_pos(index_ls(background, 0)->ent_ptr, get_x(boy) / 10, get_y(boy) / 10);

}

void readouts(void) {

	go_to(0, 0);
	fprintf(stderr, "*---------------------------------------------*\n");
	fprintf(stderr, "*- --------world_x: %d -- world_y: %d------- -*\n", world_x, world_y);
	fprintf(stderr, "*- 				   LISTS		     	  -*\n");
	fprintf(stderr, "*- entity_list_1: ");
	print_names(entities);
	fprintf(stderr, "*---------------------------------------------*\n");

}

void update_world_elements(void) {
	
	
	
}

void handle_input(void) {

	switch(event.key.keysym.sym) {

		case SDLK_ESCAPE:
			is_running = SDL_FALSE;
			break;
			
		case SDLK_z:
			move_y(boy, -10);
			break;
		
		case SDLK_s:
			move_y(boy, 10);
			break;

		case SDLK_d:
			//move_x(boy, 10);
			add_speed(boy, 1.0f);
			break;

		case SDLK_q:
			//move_x(boy, -10);
			add_speed(boy, -1.0f);
			break;
			
		case SDLK_LEFT:
			add_direction(boy, 0.1f);
			break;
			
		case SDLK_RIGHT:
			add_direction(boy, -0.1f);
			break;
			
		case SDLK_SPACE:
			point = save_ent_pos(boy);
			lerp(boy, get_x(boy), get_y(boy) + 80, 5);
			lerp(boy, point.x, point.y, 5);
			break;
			
		case SDLK_c: /* center */
			set_ent_pos(boy, 0, 0);
			break;
			
		case SDLK_u: /* debug */
			who_is(boy);
			break;

		case SDLK_t:
			toggle_bool(&is_debug);
			if (is_debug) 
				debug_all(entities);
			else 
				un_debug_all(entities);
			break;

		case SDLK_o:
			lerp(boy, 0, 0, 10);
			break;

		default:
			break;

	}

}