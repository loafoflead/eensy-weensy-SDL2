#include <SDL2/SDL.h>
#include <string.h>
#include <stdio.h>

#include "RenderWrap.h"
#include "RenderArrays.h"
#include "animations.h"
#include "general.h"

Entity* ent;

void list_ents(Entity *arr[]) {
	if (count_elements(arr) < 1) {
		fprintf(stderr, "[ array null! ]");
	}
	for (int i = 0; i < count_elements(arr); i ++) {
		fprintf(
			stderr, 
			"[ %s >> x: %d y: %d >> dir: %f >> speed: %f >> at index: %d] ",
			arr[i]->texture_name, 
			get_x(arr[i]), 
			get_y(arr[i]),
			get_direction(arr[i]),
			get_speed(arr[i]),
			i
		);
	}
	fputc('\n', stderr);
}

void change_property(Entity *arr[], enum entity_properties props, int value) {
	
	void (*func_type)(Entity* , int );
	
	switch (props) {
		
		case DEBUG_DRAWING:
			func_type = &set_debug;
			break;
			
		case HIDDEN:
			func_type = &set_hidden;
			break;
			
		case WIDTH:
			func_type = &set_height;
			break;
			
		case HEIGHT:
			func_type = &set_height;
			break;
		
		case XPOS:
			func_type = &move_x;
			break;
			
		case YPOS:
			func_type = &move_y;
			break;
			
		default:
			return;
	
	}
	

	for (int i = 0; i < sizeof_arr(arr); i ++) {
		if (arr[i] == NULL) 
			return;
		func_type(arr[i], value);
	}
	
}

void toggle_property(Entity *arr[], enum entity_properties props) {
	
	switch (props) {
		
		case DEBUG_DRAWING:
			for (int i = 0; i < sizeof_arr(arr); i ++) {
				if (arr[i] == NULL) 
					return;
				toggle_bool(&arr[i]->debug);
			}
			break;
			
		case HIDDEN:
			for (int i = 0; i < sizeof_arr(arr); i ++) {
				if (arr[i] == NULL) 
					return;
				toggle_bool(&arr[i]->hidden);
			}
			break;
		
		default:
			return;
	
	}
	
}

void set_all_positions(Entity *arr[], enum movement_types mt, int x, int y) {
	
	switch(mt) {
		
		case LERP:
			for (int i = 0; i < count_elements(arr); i ++) {
				lerp(arr[i], x, y, 10);
			}
		break;
			
		case NORMAL:
			for (int i = 0; i < count_elements(arr); i ++) {
				set_ent_pos(arr[i], x, y);
			}
		break;
		
	}
	
}

	
	


void update_arr(Entity *arr[]) {
	for (int i = 0; i < count_elements(arr); i ++) {
		update_ent(arr[i]);
	}
}

void add_next_ent(Entity *arr[], Entity* new_ent) {
	for (int i = 0; i < count_elements(arr); i ++) {
		if (arr[i] == NULL) {
			arr[i] = new_ent;
		}
	}
}

void remove_entity(Entity *arr[], Entity** entt) {
	
	ent = *entt;
	
	if (!ent)
		return; // null ptr safeguard 
	
	for (int i = 0; i < count_elements(arr); i ++) {
		
		if (arr[i] == NULL)
			return;
		
		if (arr[i] == ent) { /// @note find the element, now resize the list in backwards order ??? aa
		
			destroy_entity(arr[i]);		
			*entt = NULL;
			
			for (int b = i; b < count_elements(arr); b ++) { // go thru the list setting each element to the element in 
				arr[b] = arr[b + 1];
			}
			
		}
	
	}
}

int count_elements(Entity *arr[]) {
	int cc = 0;
	for (int i = 0; i < sizeof_arr(arr); i ++) {
		if (arr[i] != NULL) {
			cc ++;
		}
	}
	return cc;
}

void draw_array(Entity *arr[]) {
	for (int  i = 0; i < sizeof_arr(arr); i ++) {
		if (arr[i] == NULL) {
			return; // safeguard a null entity ptr
		}
		if(arr[i]->hidden == SDL_FALSE)
			draw_ent(arr[i]);
		if(arr[i]->debug == SDL_TRUE)
			draw_debug(arr[i]);
	}
}

void destroy_array(Entity *arr[]) {
	for (int i = 0; i < sizeof_arr(arr); i ++) {
		if (arr[i] == NULL) {
			return; // safeguard a null entity ptr
		}
		destroy_entity(arr[i]);
		arr[i] = NULL;
	}
}

Entity *search_array(Entity *array[], char *texture_name) {
	for (int i = 0; i < sizeof_arr(array); i ++) {
		if (array[i] == NULL) {
			return NULL; // safeguard a null entity ptr
		}
		if (strcmp(texture_name, array[i]->texture_name) == 0) {
			return array[i];
		}
	}
	return NULL;
}

int index_of_ent(Entity *arr[], Entity* ent) {
	for (int i = 0; i < count_elements(arr); i ++) {
		if (arr[i] == ent) {
			return i;
		}
	}
}

void set_array_pos(Entity *arr[], int new_x, int new_y) {
	for (int i = 0; i < sizeof_arr(arr); i ++) {
		if (arr[i] == NULL)
			return; // null ptr safeguard
		set_ent_pos(arr[i], new_x, new_y);
	}
}
