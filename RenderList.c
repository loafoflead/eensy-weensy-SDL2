#include "RenderList.h"
#include "RenderWrap.h"

#include "SDL2/SDL.h"

static ListElement* first_ptr; /* ptr to first element in list */

static ListElement* curr_ptr; /* Reusable ptr */

static int list_length = 0;



int list_len(void) {

	int count = 0;
	curr_ptr = first_ptr;

	while(curr_ptr != NULL) {
		curr_ptr = curr_ptr->next_ptr;
		count ++;
	}

	return count;
}

/// NOTE: works
void print_names(void) {

	curr_ptr = first_ptr;

	while(curr_ptr != NULL) {
		fprintf(stderr, "[%s]--", curr_ptr->name);
		curr_ptr = curr_ptr->next_ptr;
	}

}

void free_list(void) {

	curr_ptr = first_ptr;
	ListElement* temp_ptr;

	while(curr_ptr != NULL) {
		temp_ptr = curr_ptr;
		curr_ptr = curr_ptr->next_ptr;
		free(temp_ptr);
	}

	list_length = 0;

}

void RenderCopyList(SDL_Renderer* renderer) {

	curr_ptr = first_ptr;

	while(curr_ptr != NULL) {
		draw_ent(curr_ptr->ent_ptr, renderer);
		curr_ptr = curr_ptr->next_ptr;
	}

}

ListElement** get_list_arr(void) {

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

ListElement* find_element(char *_name) {

	curr_ptr = first_ptr;

	while(curr_ptr != NULL) {
		if (strcmp(curr_ptr->name, _name) == 0) {
			return curr_ptr;
		}
		curr_ptr = curr_ptr->next_ptr;
	}

	return NULL;

}

/// TODO: This does not work !!!!!
void add_ent(Entity* new_ent, char* _name) {

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

void init_list_ent_ptr(Entity* e, char* _name) {

	first_ptr = (ListElement *) malloc(sizeof(ListElement));
	first_ptr->next_ptr = NULL;
	first_ptr->ent_ptr = e;

	strcpy(first_ptr->name, _name);

	list_length ++;

}