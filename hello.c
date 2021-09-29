#include <stdio.h>
#include <SDL2/SDL.h>

#include "RenderWrap.h"
#include "RenderList.h" 
#include "RenderArrays.h"
#include "Entity.h"
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
	
	gcc *.c -o hello.exe -lSDL2main -lSDL2 -lSDL2_image -lm -lSDL2_ttf -lpthread <- current compilation command :) 
*/

/** @NOTE: GAME VARIABLES **/

int world_x = 0;
int world_y = 0;

/* END */

SDL_Window* window;
extern SDL_Renderer* renderer;

SDL_Event event;

SDL_bool is_running = SDL_FALSE;


/** @NOTE: function declarations **/

void initialise_entities(void);

void update_cycle(void);
void handle_input(void);
void game_update(void);

void readouts(void);

void update_world_elements(void);
/**********************************/


/** @NOTE: Variable declarations **/

Entity *boy;

Entity boy_real;

Entity* pear;

SDL_Point size;

Entity *entity_array[10];  /// @todo: maybe just make... an entity list haha :raised_eyebrows:

ListElement* entities; /* the entities list, anything that's gonna be interacted with */
ListElement* background; /* true background layer, will have no interactions with entities at all */

short int is_debug;

SDL_Point point; /* point to re-use */

/**********************************/

int main() {
	
	if (is_running == SDL_FALSE) {
		fprintf(stderr, "Warn: is_running is set to false.\n");
		//exit(8);
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

	init_img(renderer);
	
	/*SDL_Drawable dra = *load_image_drawable("images_folder/boy_idle.png");
	
	draw_drawable(&dra);*/
	
	fill_ent(&boy_real, "boy_idle.png", 0, 0);
	
	draw_ent(&boy_real);
	
	who_is(&boy_real);
	
	SDL_RenderPresent(renderer);
	
	SDL_Delay(1000);

	while (is_running) {
		
		//update_cycle();
		
	}

	SDL_Quit();
	quit_img();
	
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

	SDL_RenderPresent(renderer);

}

void initialise_entities(void) {
	
	
}

void handle_input(void) {

	switch(event.key.keysym.sym) {

		case SDLK_ESCAPE:
			is_running = SDL_FALSE;
			break;
			
		

	}

}
