#include "RenderList.h"
#include "RenderWrap.h"
#include "general.h"
#include "animations.h"

#include "SDL2/SDL.h"

static ListElement* curr_ptr; /* Reusable ptr */
static ListElement** temp_list; /* reusable ptr list */

Collision** collision_list; /** @note: collision list **/

/** @warn: neither of these funcs work, to re-do **/
Collision** get_collisions(ListElement* first_ptr) {
	
	if (first_ptr == NULL) 
		return NULL; /* null ptr safeguard */
	
	temp_list = get_list_arr(first_ptr);
	
	collision_list = (Collision** ) malloc(sizeof(Collision) * count_collisions(first_ptr));
	
	for(int i = 0; i < list_len(first_ptr); i ++) {
		for (int j = i + 1; j < list_len(first_ptr); j ++) {

			if (check_collision(temp_list[i]->ent_ptr, temp_list[j]->ent_ptr) == SDL_TRUE) {
				collision_list[i]->a = temp_list[i]->ent_ptr;
				collision_list[i]->b = temp_list[j]->ent_ptr;
			}

		}
	}
	
	return collision_list;
	
}

void get_collisions_toarray(ListElement* first_ptr, Collision* collision_array_pointer) {
	
	if (collision_array_pointer == NULL) {
		fprintf(stderr, "tried to fill a null array with collisions.\n");	
		return;
	}
	
	fprintf(stderr, "length: %d\n", list_len(first_ptr));
	
	temp_list = get_list_arr(first_ptr);
	
	for(int i = 0; i < list_len(first_ptr); i ++) {
		
		fprintf(stderr, "Running collision loop.\n");	
		
		if (i == (sizeof(collision_array_pointer) / sizeof(collision_array_pointer[0])) - 1) {
			fprintf(stderr, "Reached the end of the array.\n");	
			break ;
		}
		
		for (int j = i + 1; j < list_len(first_ptr); j ++) {
			
			fprintf(stderr, "Running second collision loop.\n");	

			if (check_collision(temp_list[i]->ent_ptr, temp_list[j]->ent_ptr) == SDL_TRUE) {
				fprintf(stderr, "Collision found!\n");	
				fflush(stdout);
				get_collision_obj(temp_list[i]->ent_ptr, temp_list[j]->ent_ptr, &collision_array_pointer[i]);
			}
			
			fprintf(stderr, "Collision not found.\n");	

		}
	}
	
}
/**											    **/

int count_collisions(ListElement* first_ptr) {

	temp_list = get_list_arr(first_ptr);

	int collision_count = 0;

	for(int i = 0; i < list_len(first_ptr); i ++) {
		for (int j = i + 1; j < list_len(first_ptr); j ++) {

			if (check_collision(temp_list[i]->ent_ptr, temp_list[j]->ent_ptr) == SDL_TRUE) {
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
		destroy_entity(temp_ptr->ent_ptr);
		free(temp_ptr);
	}

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

void lerp_all(ListElement* first, int _x, int _y, int ti) {
	
	curr_ptr = first;

	while(curr_ptr != NULL) {
		lerp(curr_ptr->ent_ptr, _x, _y, ti);
		curr_ptr = curr_ptr->next_ptr;
	}
	
}

void lerp_all_local_offset(ListElement* first, int _x, int _y, int ti) {
	curr_ptr = first;

	while(curr_ptr != NULL) {
		lerp(curr_ptr->ent_ptr, _x + get_x(curr_ptr->ent_ptr), _y + get_y(curr_ptr->ent_ptr), ti);
		curr_ptr = curr_ptr->next_ptr;
	}
	
}

void update_all(ListElement* first) {
	curr_ptr = first;
	
	while(curr_ptr != NULL) {
		update_ent(curr_ptr->ent_ptr);
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


int copy_list(ListElement* first_a, ListElement* first_b) {
	
	first_b = first_a;
	
}

ListElement** get_list_arr(ListElement* first_ptr) {
	
	if (first_ptr = NULL) 
		return NULL;

	curr_ptr = first_ptr;

	ListElement** arr_to_return = (ListElement** ) malloc(sizeof(ListElement) * list_len(first_ptr));

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

ListElement* index_ls(ListElement* first_ptr, int index) {
	
	curr_ptr = first_ptr;
	
	int counter = 0;
	
	while(curr_ptr != NULL) {
		if (counter == index) {
			return curr_ptr;
		}
		curr_ptr = curr_ptr->next_ptr;
		counter ++;
	}
	
	return NULL;
	
}

Entity* get_ent(ListElement* first_ptr, char* _name) {
	return find_element(first_ptr, _name)->ent_ptr;
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

	return first_ptr;

}