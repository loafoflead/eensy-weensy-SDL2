#include "RenderList.h"
#include "RenderWrap.h"
#include "general.h"

#include "SDL2/SDL.h"

//static ListElement* first_ptr; /* ptr to first element in list */

static ListElement* curr_ptr; /* Reusable ptr */

static int list_length = 0;


int count_collisions(ListElement* first_ptr) {

	ListElement** list = get_list_arr(first_ptr);

	int collision_count = 0;

	for(int i = 0; i < list_len(first_ptr); i ++) {
		for (int j = i + 1; j < list_len(first_ptr); j ++) {

			if (check_collision(list[i]->ent_ptr, list[j]->ent_ptr) == SDL_TRUE) {
				collision_count ++;
			}

		}
	}

	return collision_count;

}


int list_len(ListElement* first_ptr) {

	int count = 0;
	curr_ptr = first_ptr;

	while(curr_ptr != NULL) {
		curr_ptr = curr_ptr->next_ptr;
		count ++;
	}

	return count;
}

/// NOTE: works
void print_names(ListElement* first_ptr) {

	curr_ptr = first_ptr;

	while(curr_ptr != NULL) {
		fprintf(stderr, "[%s]--", curr_ptr->name);
		curr_ptr = curr_ptr->next_ptr;
	}

}

void free_list(ListElement* first_ptr) {

	curr_ptr = first_ptr;
	ListElement* temp_ptr;

	while(curr_ptr != NULL) {
		temp_ptr = curr_ptr;
		curr_ptr = curr_ptr->next_ptr;
		free(temp_ptr);
	}

	list_length = 0;

}

void hide_all(ListElement* first_ptr) {

	curr_ptr = first_ptr;

	while(curr_ptr != NULL) {
		curr_ptr->ent_ptr->hidden = SDL_TRUE;
		curr_ptr = curr_ptr->next_ptr;
	}

}

void show_all(ListElement* first_ptr) {

	curr_ptr = first_ptr;

	while(curr_ptr != NULL) {
		curr_ptr->ent_ptr->hidden = SDL_FALSE;
		curr_ptr = curr_ptr->next_ptr;
	}

}

void debug_all(ListElement* first_ptr) {

	curr_ptr = first_ptr;

	while(curr_ptr != NULL) {
		curr_ptr->ent_ptr->debug = SDL_TRUE;
		curr_ptr = curr_ptr->next_ptr;
	}

}

void un_debug_all(ListElement* first_ptr) {

	curr_ptr = first_ptr;

	while(curr_ptr != NULL) {
		curr_ptr->ent_ptr->debug = SDL_FALSE;
		curr_ptr = curr_ptr->next_ptr;
	}

}

void set_all(ListElement* first_ptr, int _x, int _y) {

	curr_ptr = first_ptr;

	while(curr_ptr != NULL) {
		curr_ptr->ent_ptr->ent_rect->x = _x;
		curr_ptr->ent_ptr->ent_rect->y = _y;
		curr_ptr = curr_ptr->next_ptr;
	}

}

void move_all(ListElement* first_ptr, int _x, int _y) {

	curr_ptr = first_ptr;

	while(curr_ptr != NULL) {
		curr_ptr->ent_ptr->ent_rect->x += _x;
		curr_ptr->ent_ptr->ent_rect->y += _y;
		curr_ptr = curr_ptr->next_ptr;
	}

}


void RenderCopyList(ListElement* first_ptr) {

	curr_ptr = first_ptr;

	while(curr_ptr != NULL) {
		if (curr_ptr->ent_ptr->hidden == SDL_FALSE) {
			draw_ent(curr_ptr->ent_ptr);
		}
		if (curr_ptr->ent_ptr->debug == SDL_TRUE) 
				draw_debug(curr_ptr->ent_ptr);
		curr_ptr = curr_ptr->next_ptr;
	}

}

void RenderCopyListCenter(ListElement* first_ptr) {

	curr_ptr = first_ptr;

	while(curr_ptr != NULL) {
		if (curr_ptr->ent_ptr->hidden == SDL_FALSE) {
			draw_ent_center(curr_ptr->ent_ptr);
		}
		if (curr_ptr->ent_ptr->debug == SDL_TRUE) 
				draw_debug(curr_ptr->ent_ptr);
		curr_ptr = curr_ptr->next_ptr;
	}

}


ListElement** get_list_arr(ListElement* first_ptr) {

	curr_ptr = first_ptr;

	ListElement** arr_to_return = (ListElement** ) malloc(sizeof(ListElement) * list_length);

	int index = 0;

	while(curr_ptr != NULL) {

		*(arr_to_return + index) = curr_ptr;

		curr_ptr = curr_ptr->next_ptr;

		index ++;

	}

	return arr_to_return;

}

ListElement* find_element(ListElement* first_ptr, char *_name) {

	curr_ptr = first_ptr;

	while(curr_ptr != NULL) {
		if (strcmp(curr_ptr->name, _name) == 0) {
			return curr_ptr;
		}
		curr_ptr = curr_ptr->next_ptr;
	}

	return NULL;

}

/// TODO: This does -n-o-t- WORKS :) !!!!!
void add_ent(ListElement* first_ptr, Entity* new_ent, char* _name) {

	curr_ptr = first_ptr;

	while(curr_ptr->next_ptr != NULL) {
		curr_ptr = curr_ptr->next_ptr;
	}

	ListElement* new_ptr = (ListElement *) malloc(sizeof(ListElement));
	new_ptr->next_ptr = NULL;
	new_ptr->ent_ptr = new_ent;

	strcpy(new_ptr->name, _name);

	curr_ptr->next_ptr = new_ptr;

	list_length ++;

}

void remove_element(ListElement* first_ptr, ListElement* el_ptr) {

	if(el_ptr == NULL) {
		return;
	}

	if(first_ptr == NULL) {
		return;
	}

	curr_ptr = first_ptr;

	if (curr_ptr == el_ptr) {
		return;
	}

	while(curr_ptr != NULL) {
		if (curr_ptr->next_ptr == el_ptr) {
			break;
		}
		curr_ptr = curr_ptr->next_ptr;
	}

	if (el_ptr->next_ptr != NULL)
		curr_ptr->next_ptr = el_ptr->next_ptr;
	else 
		curr_ptr->next_ptr = NULL;

	free(el_ptr);

}

ListElement* init_list_ent_ptr(Entity* e, char* _name) {

	ListElement* first_ptr = (ListElement *) malloc(sizeof(ListElement));
	first_ptr->next_ptr = NULL;
	first_ptr->ent_ptr = e;

	strcpy(first_ptr->name, _name);

	list_length ++;

	return first_ptr;

}