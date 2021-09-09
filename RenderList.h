#ifndef RENDER_LIST_H
#define RENDER_LIST_H value

#include "RenderWrap.h"
#include "SDL2/SDL.h"

typedef struct list_element_ {
	Entity* ent_ptr;
	struct list_element_* next_ptr;
	char name[50];
} ListElement;

int list_len(void);

void print_names(void);

ListElement* find_element(char *_name);

void add_ent(Entity* new_ent, char* _name);

void init_list_ent_ptr(Entity* e, char* _name);

void free_list(void);

ListElement** get_list_arr(void);

#endif