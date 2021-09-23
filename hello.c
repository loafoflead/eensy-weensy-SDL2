#include <stdio.h>
#include <SDL2/SDL.h>

#include "RenderWrap.h"
#include "RenderList.h" 
#include "FontRenderWrap.h"
#include "general.h"

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

/* NOTE: GAME VARIABLES */

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

ListElement* entity_list_1;

ListElement* world_entity_list;

ListElement* update_entity_list;
/**********************************/

int main() {

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
	free_list(entity_list_1);

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

	RenderCopyList(entity_list_1);

	/* TODO: REVISIT THIS!!!!!!!!!!!!! AAAAAAAAAAAAAA
	if (lerpp == SDL_TRUE && it < 101) {
		set_ent_x(new_ent, (int)lerp_float((float) get_x(new_ent), (float) get_x(new_ent) + 10.0f, it / 100));
		it ++;
	}*/ 

	SDL_RenderPresent(renderer);

}

void initialise_entities(void) {
	
	entity_list_1 = init_list_ent_ptr(create_entity("boy_idle.png", size.x / 2, size.y /2), "boy");
	boy = find_element(entity_list_1, "boy")->ent_ptr;
	
	world_entity_list = init_list_ent_ptr(create_entity("earth.png", 0, 0), "ground");
	
	add_ent(world_entity_list, create_entity("tree1.png", 0, 100), "\"tree\"");
	add_ent(world_entity_list, create_entity("tree1.png", 500, 100), "\"tree2\"");
	
	update_entity_list = init_list_ent_ptr(create_entity("pear.png", size.x /2, size.y / 2), "pear");
	
}

void game_update(void) {

	RenderCopyList(world_entity_list);
	RenderCopyListCenter(update_entity_list);
	
}

void readouts(void) {

	go_to(0, 0);
	fprintf(stderr, "*---------------------------------------------*\n");
	fprintf(stderr, "*- --------world_x: %d -- world_y: %d------- -*\n", world_x, world_y);
	fprintf(stderr, "*- 				   LISTS		     	  -*\n");
	fprintf(stderr, "*- entity_list_1: ");
	print_names(entity_list_1);
	fprintf(stderr, "*---------------------------------------------*\n");

}

void update_world_elements(void) {
	
	
	
}


Collision temp_col;

void handle_input(void) {

	switch(event.key.keysym.sym) {

		case SDLK_ESCAPE:
			is_running = SDL_FALSE;
			break;

		case SDLK_d:
			//move_all(world_entity_list, 5, 0);
			debug_all(world_entity_list);
			//move_x(boy, 5);
			break;

		case SDLK_q:
			move_all(world_entity_list, -5, 0);
			//move_x(boy, -5);
			break;

		case SDLK_z:
			move_all(world_entity_list, 0, -5);
			//move_x(boy, -5);
			break;

		case SDLK_s:
			move_all(world_entity_list, 0, 5);
			//move_x(boy, -5);
			break;

		case SDLK_c:
			replace_sprite(boy, "boy_idle.png");
			break;

		case SDLK_r:
			replace_sprite(boy, "boy_jump.png");
			break;

		case SDLK_u:
			who_is(boy);
			break;

		case SDLK_a:
			toggle_bool(&boy->hidden);
			break;

		case SDLK_t:
			toggle_bool(&boy->debug);
			break;

		case SDLK_p:
			get_collision_obj(boy, get_ent(world_entity_list, "ground"), &temp_col);
			tell_collision(&temp_col);
			break;
			
		case SDLK_m:
			set_ent_pos(boy, 0, 0);
			break;

		default:
			break;

	}

}