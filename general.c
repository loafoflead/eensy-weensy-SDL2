#include "general.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL2/SDL.h"

gen_list* temp_ptr; /** @Note: temporary ptr, to reuse in funcs instead of creating a bunch of new ones n stuff **/

gen_list* most_recent; /** @Note: the most recent element to be accessed **/



gen_list* gen_init_list(char* tag_name, void* element) {
	
	gen_list* new_ptr = (gen_list* ) malloc(sizeof(gen_list)); /** @NOTE: create new element **/
	
	strcpy(new_ptr->list_tag, tag_name); /* copy the tagname into the new list element */

	new_ptr->element_ptr = element; /* add the pointer to the list element */
	
	new_ptr->next_ptr = NULL; /* set the next ptr to NULL */
	
	new_ptr->prev_ptr = new_ptr; /* set the previous ptr to itself. (it's the head of the list) */
	
	most_recent = new_ptr;
	
	return new_ptr; /* return */
	
}

void gen_add(gen_list* first_element_ptr, char* new_tagname, void* new_element) {
	
	gen_list* new_ptr = (gen_list* ) malloc(sizeof(gen_list)); /** @NOTE: create new element **/
	
	strcpy(new_ptr->list_tag, new_tagname); /* copy the tagname into the new list element */

	new_ptr->element_ptr = new_element; /* add the pointer to the list element */
	
	new_ptr->next_ptr = NULL;
	
	temp_ptr = first_element_ptr;
	
	while(temp_ptr->next_ptr != NULL) {
		temp_ptr = temp_ptr->next_ptr; /** @NOTE: find latest element in the list **/
	}
	
	new_ptr->prev_ptr = temp_ptr; /* set it as the previous ptr for the new element */
	
	most_recent = new_ptr;
	
}
	
gen_list* gen_find(gen_list* first_ptr, char* tagname) {
	
	temp_ptr = first_ptr;
	
	while(temp_ptr != NULL) {
		if (strcmp(temp_ptr->list_tag, tagname) == 0) {
			return temp_ptr;
		}
		temp_ptr = temp_ptr->next_ptr;
	}
	
	return NULL;

}

void gen_remove(gen_list* first_ptr, char* tagname) {
	
	temp_ptr = first_ptr;
	
	while(temp_ptr != NULL) {
		if (strcmp(temp_ptr->list_tag, tagname) == 0) {
			
			temp_ptr->prev_ptr->next_ptr = temp_ptr->next_ptr; /** @NOTE: assign to the previous pointer's next pointer the 
																   current pointer's next value. **/
																   
			temp_ptr->next_ptr->prev_ptr = temp_ptr->prev_ptr; /** @NOTE: assign to this ptrs next pointer this pointer's 
																   previous pointer **/
																   
			free_gen(temp_ptr); /* free the ptr */
			
		}	
		temp_ptr = temp_ptr->next_ptr;
	}
	
}

void free_gen(gen_list* ptr) {
	
	if (ptr == NULL) {
		return;
	}
	
	free(ptr->element_ptr);
	free(ptr);
}

int gen_len(gen_list* first) {
	
	if (first == NULL) {
		return 0; /** @NOTE: null ptr guard **/
	}
	
	int count = 0;
	
	temp_ptr = first;
	
	while (temp_ptr != NULL) {
		count ++;
		temp_ptr = temp_ptr->next_ptr;
	}
	
	return count;
}

gen_list** gen_list_as_array(gen_list* first_ptr) {
	
	if (!first_ptr) {
		return NULL; /// @NOTE: if the ptr is empty, return NULL 
	}
	
	gen_list** arr = (gen_list**) malloc(sizeof(gen_list) * gen_len(first_ptr));
	
	temp_ptr = first_ptr;
	
	for (int i = 0; i < gen_len(first_ptr); i ++) {
		arr[i] = temp_ptr;
		temp_ptr = temp_ptr->next_ptr;
	}
	
	return arr;
	
}


void go_to(int x, int y) {
	printf("\033[%d;%dH", x, y);
	fflush(stdout);
}

void toggle_bool(short int* boolean) {
	if ((*boolean) == 0) {
		*boolean = 1;
	}
	else {
		*boolean = 0;
	}
}

int sizeof_arr(void* array) {
	return( sizeof(array) / sizeof((*array)));
}
