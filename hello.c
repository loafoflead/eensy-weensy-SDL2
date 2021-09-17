#include <stdio.h>
#include <SDL2/SDL.h>

#include "RenderWrap.h"
#include "RenderList.h" 
#include "general.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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
SDL_Renderer* renderer;

SDL_Event event;

SDL_bool is_running = SDL_TRUE;

void update_cycle(void);
void handle_input(void);
void game_update(void);

void update_world_elements(void);

Entity* boy;

ListElement* entity_list_1;

ListElement* world_entity_list;

int main() {

	SDL_Point size;

	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Failed to start SDL.\n");
		exit(8);
	}

	if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer) != 0) {
		fprintf(stderr, "Failed to open window: %s\n", SDL_GetError());
		SDL_Quit();
		exit(8);
	}

	SDL_GetWindowSize(window, &size.x, &size.y); // TODO: Figure out how to make the "center" of sprites not
												 // be the top left <3 much love good luck

	init_img(renderer);

	boy = create_entity("boy_idle.png", size.x / 2, size.y /2);
	world_entity_list = init_list_ent_ptr(create_entity("earth.png", 0, 0), "ground");

	entity_list_1 = init_list_ent_ptr(boy, "boy");
	add_ent(world_entity_list, create_entity("boy_jump.png", 0, 0), "\"tree\"");

	//who_is(boy);
	
	while (is_running) {
		update_cycle();
		//who_is(boy);
		//SDL_Delay(1000);
	}

	SDL_Quit();
	quit_img();
	free_list(entity_list_1);

	return(0);

}

float it = 0;
SDL_bool lerpp = SDL_FALSE;

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

	game_update();

	RenderCopyList(entity_list_1);

	/* TODO: REVISIT THIS!!!!!!!!!!!!! AAAAAAAAAAAAAA
	if (lerpp == SDL_TRUE && it < 101) {
		set_ent_x(new_ent, (int)lerp_float((float) get_x(new_ent), (float) get_x(new_ent) + 10.0f, it / 100));
		it ++;
	}*/ 

	SDL_RenderPresent(renderer);

}


void game_update(void) {

	update_world_elements();



}


void update_world_elements(void) {
	ListElement** bg_list = get_list_arr(world_entity_list);

	for(int i = 0; i < list_len(world_entity_list); i ++) {
		//fprintf(stderr, "current_ent: %s\n", bg_list[i]->ent_ptr->texture_name);
		set_ent_x(bg_list[i]->ent_ptr, 0 + world_x); 
		set_ent_y(bg_list[i]->ent_ptr, 0 + world_y); 
	}

	RenderCopyList(world_entity_list);
}




void handle_input(void) {

	switch(event.key.keysym.sym) {

		case SDLK_ESCAPE:
			is_running = SDL_FALSE;
			break;

		case SDLK_d:
			world_x += 10;
			//move_x(boy, 5);
			break;

		case SDLK_q:
			world_x -= 10;
			//move_x(boy, -5);
			break;

		case SDLK_z:
			world_y -= 10;
			//move_x(boy, -5);
			break;

		case SDLK_s:
			world_y += 10;
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

		case SDLK_p:
			break;

		default:
			break;

	}

}