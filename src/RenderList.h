#ifndef RENDER_LIST_H
#define RENDER_LIST_H value

#include "RenderWrap.h"
#include "SDL2/SDL.h" 

typedef struct list_element_ {
	Entity* ent_ptr;
	struct list_element_* next_ptr;
	char name[50];
} ListElement;

int list_len(ListElement* ); 

void print_names(ListElement* );

ListElement* find_element(ListElement* , char *_name);

void add_ent(ListElement* , Entity* new_ent, char* _name);

void remove_element(ListElement* first_ptr, ListElement* el_ptr);

ListElement* init_list_ent_ptr(Entity* e, char* _name);

void free_list(ListElement* );

ListElement** get_list_arr(ListElement* );

void RenderCopyList(ListElement* );

void RenderCopyListCenter(ListElement* );

int count_collisions(ListElement* );


void debug_all(ListElement* first_ptr);
void un_debug_all(ListElement* first_ptr);

void show_all(ListElement* first_ptr);
void hide_all(ListElement* first_ptr);

void move_all(ListElement* first_ptr, int _x, int _y);
void set_all(ListElement* first_ptr, int _x, int _y);

#endif