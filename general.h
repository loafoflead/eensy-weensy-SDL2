#ifndef GENERAL__H
#define GENERAL__H value

#include "SDL2/SDL.h"

typedef struct gen_list {
	char list_tag[100];
	void* element_ptr;
	struct gen_list* next_ptr;
	struct gen_list* prev_ptr;
} gen_list ;

void free_gen(gen_list* ptr); /* free memory of a list ptr */

void gen_remove(gen_list* first_ptr, char* tagname); /* remove an element ptr and stitch the list back together */

gen_list* gen_find(gen_list* first_ptr, char* tagname); /* find and return an element from a list using it's tagname */

void gen_add(gen_list* first_element_ptr, char* new_tagname, void* new_element); /* add an element to a list */

gen_list* gen_init_list(char* tag_name, void* element); /* initalise the list with a new element */

int gen_len(gen_list* first);

gen_list** gen_list_as_array(gen_list* ); /* return the list as a traditional array */

void toggle_bool(SDL_bool* );
int sizeof_arr(void* array);
void go_to(int x, int y);

#endif