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

SDL_Window* window;
SDL_Renderer* renderer;

SDL_Event event;

SDL_bool is_running = SDL_TRUE;

void update_cycle(void);
void handle_input(void);

Entity* boy;

ListElement* entity_list_1;

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

	init_img();

	boy = create_entity("boy_idle.png", renderer, 0, 0);

	entity_list_1 = init_list_ent_ptr(boy, "boy");
	add_ent(entity_list_1, create_entity("earth.png", renderer, 0, 0), "ground");

	int incr = 1;

	add_behaviour(boy, &move_x, &incr, "move");
	boy->run_behaviours = SDL_FALSE;

	while (is_running) {
		update_cycle();
		who_is(boy);
		SDL_Delay(1000);
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

	RenderCopyList(entity_list_1, renderer);

	/* TODO: REVISIT THIS!!!!!!!!!!!!! AAAAAAAAAAAAAA
	if (lerpp == SDL_TRUE && it < 101) {
		set_ent_x(new_ent, (int)lerp_float((float) get_x(new_ent), (float) get_x(new_ent) + 10.0f, it / 100));
		it ++;
	}*/ 

	SDL_RenderPresent(renderer);

}

void handle_input(void) {

	switch(event.key.keysym.sym) {

		case SDLK_ESCAPE:
			is_running = SDL_FALSE;
			break;

		case SDLK_d:
			move_x(boy, 5);
			break;

		case SDLK_q:
			move_x(boy, -5);
			break;

		case SDLK_c:
			set_ent_x(boy, 0);
			break;

		case SDLK_a:
			toggle_bool(&boy->hidden);
			break;

		case SDLK_p:


		default:
			break;

	}

}