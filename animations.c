#include "animations.h"
#include "RenderWrap.h"
#include "RenderList.h"
#include "general.h"

#include <SDL2/SDL.h>
#include <math.h>

// Threading libs: 
#include <pthread.h>
#include <unistd.h> // timing lib

void* example_func(void* arg) {
	sleep(1);
	fprintf(stderr, "shart");
	return NULL;
}

void* lin_interpolate(void* argvi) {
	
	struct lerp_args* argv = argvi;
	
	/// @TODO: REVISIT THIS!!!!!!!!!!!!! AAAAAAAAAAAAAA
	for (int i = 0; i < 101; i ++) {
		if (get_x(argv->ent) == argv->x && get_y(argv->ent) == argv->y) {
			pthread_exit(NULL);
			return NULL; /* return if no motion is actually being done */
		}
		set_ent_x(argv->ent, (int) lerp_float( (float) get_x(argv->ent), (float) argv->x, (float) i / 100 ));
		set_ent_y(argv->ent, (int) lerp_float( (float) get_y(argv->ent), (float) argv->y, (float) i / 100 ));
		SDL_Delay(argv->delay);
	}
	/*if (it < 101) {
		set_ent_x(new_ent, (int)lerp_float((float) get_x(new_ent), (float) get_x(new_ent) + 10.0f, it / 100));
		it ++;
	}*/
}

void* lin_interpolate_u(void* argvi) {
	
	struct lerp_args* argv = argvi;
	
	for (int i = 0; i < 101; i ++) {
		if (get_x(argv->ent) == argv->x && get_y(argv->ent) == argv->y) {
			pthread_exit(NULL);
			return NULL; /* return if no motion is actually being done */
		}
		move_x(argv->ent, (int) lerp_float( (float) get_x(argv->ent), (float) argv->x, (float) i / 100 ));
		move_y(argv->ent, (int) lerp_float( (float) get_y(argv->ent), (float) argv->y, (float) i / 100 ));
		SDL_Delay(argv->delay);
	}
	
}


void lerp(Entity* ent, int x, int y, int delay_between_its) {
	
	if (get_x(ent) == x && get_y(ent) == y) {
		return; /* return if no motion is actually being done */
	}
	
	pthread_t lerp_thread;
	
	struct lerp_args* arg = (struct lerp_args* ) malloc(sizeof(struct lerp_args));
	arg->ent = ent;
	arg->x = x;
	arg->y = y;
	arg->delay = delay_between_its;
	
	pthread_create(&lerp_thread, NULL, lin_interpolate, (void* )arg);
	
}

void lerp_unsafe(Entity* ent, int x, int y, int delay) {
	
	if (get_x(ent) == x && get_y(ent) == y) {
		return; /* return if no motion is actually being done */
	}
	
	pthread_t lerp_thread;
	
	struct lerp_args* arg = (struct lerp_args* ) malloc(sizeof(struct lerp_args));
	arg->ent = ent;
	arg->x = x;
	arg->y = y;
	arg->delay = delay;
	
	pthread_create(&lerp_thread, NULL, lin_interpolate_u, (void* )arg);
	
}

void run_thread(void) {
	
	pthread_t thread_id;
    printf("Before Thread\n");
	
    pthread_create(&thread_id, NULL, example_func, NULL); /// @arg1: thread id, @arg2: attributes?, @arg3: func ptr, @arg4: arguments
	
    pthread_join(thread_id, NULL); /// @note: essentially waits for the thread given to finish before continuing the caller's thread
	
    printf("After Thread\n");
	
}
