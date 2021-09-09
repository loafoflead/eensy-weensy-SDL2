#include <stdio.h>
#include <SDL2/SDL.h>

#include "RenderWrap.h"
#include "RenderList.h"

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

Entity* new_ent;

int main() {

	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Failed to start SDL.\n");
		exit(8);
	}

	if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) != 0) {
		fprintf(stderr, "Failed to open window: %s\n", SDL_GetError());
		SDL_Quit();
		exit(8);
	}

	init_img();

	new_ent = create_entity("png_test.png", renderer, 0, 0);

	init_list_ent_ptr(new_ent, "new boy");
	add_ent(create_entity("png_test_2.png", renderer, 0, 0), "next boy");
	add_ent(create_entity("png_test_2.png", renderer, 80, 0), "next boy");

	while (is_running) {
		update_cycle();
	}

	SDL_Delay(1000);

	SDL_Quit();
	quit_img();
	free_list();

	return(0);

}

void update_cycle(void) {

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	while(SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			is_running = SDL_FALSE;
		}
		if (event.type == SDL_KEYDOWN) {
			handle_input();
		}
	}

	RenderCopyList(renderer);

	SDL_RenderPresent(renderer);

}

void handle_input(void) {

	switch(event.key.keysym.sym) {

		case SDLK_ESCAPE:
			is_running = SDL_FALSE;
			break;

		case SDLK_z:
			move_x(new_ent, 5);
			break;

		case SDLK_s:
			move_x(new_ent, -5);
			break;

		default:
			break;

	}

}