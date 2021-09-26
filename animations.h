#ifndef ANIMATION_H_
#define ANIMATION_H_ 

#include "animations.h"
#include "RenderWrap.h"
#include "RenderList.h"

enum movement_types {
	LERP = 0,
	NORMAL = 1
};

struct lerp_args {
	Entity* ent;
	int x;
	int y;
	int delay;
};

void lerp(Entity* ent, int x, int y, int);
void* lin_interpolate(void* argvi);

void lerp_unsafe(Entity* ent, int x, int y, int delay);
void* lin_interpolate_u(void* argvi);

void* example_func(void* arg);
void run_thread(void);

#endif