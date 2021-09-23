#ifndef RENDER_LIST_H
#define RENDER_LIST_H value

#include "RenderWrap.h"
#include "SDL2/SDL.h" 

typedef struct list_element_ {
	
	Entity* ent_ptr; /// @NOTE: Pointer to the element's entity 
	
	struct list_element_* next_ptr; /// @NOTE: Pointer to the next list element
	
	char name[50]; /// @NOTE: Name of the list entry
	
} ListElement;

/****************************************************************************
*	@func: get an array of all collisions between elements in a list.		*
*																			*
*	@note: returns instance of only one array, and frees it whenever it's	*
*		used again.															*
*																			*
*	@returns: Collision** coll_arr ->										*
*				Array of 'Collision' structs.								*
*																			*
****************************************************************************/
Collision** get_collisions(ListElement* first_ptr);

/****************************************************************************
*																			*
*	@func: same as above function, only instead of creating an array it 	*
*	stores the collision info in a provided array							*
*																			*
****************************************************************************/
void get_collisions_toarray(ListElement* first_ptr, Collision** collision_array_pointer);

/****************************************************************************
*	@NOTE:																	*
*		Gets the number of elements in desired list.						*
*																			*
*	@TAKES:																	*
*		ListElement* first_ptr ->											*
*			Pointer to first element in desired list.						*
*																			*
*	@RETURNS:																*
*		int list_len ->														*
*			Integer representing number of elements in a given list.		*
*																			*
****************************************************************************/
int list_len(ListElement* ); 

/****************************************************************************
*	@NOTE:																	*
*		Prints out the names of each entry in a list. 						*
*		(uses fprinf() routine)												*	
*																			*
*	@TAKES:																	*
*		ListElement* first_ptr ->											*
*			Pointer to first element in desired list.						*
*																			*
****************************************************************************/
void print_names(ListElement* );


/****************************************************************************
*	@NOTE:																	*
*		Finds an entry in the desired list by name.							*
*																			*
*	@TAKES:																	*
*		ListElement* first_ptr ->											*
*			Pointer to first element in desired list.						*
*																			*
*		char* _name ->														*
*			Name to search the list for.									*
*																			*
*	@RETURNS:																*
*		ListElement* element_found ->										*
*			Pointer to the element found, or null if no matching element 	*
*			is found.														*
*																			*
****************************************************************************/
ListElement* find_element(ListElement* , char *_name);

/// @note: similar to the above function, only it directly returns the ent
Entity* get_ent(ListElement* first_ptr, char* _name);

/****************************************************************************
*	@NOTE:																	*
*		Adds an entity onto the desired list.								*
*																			*
*	@TAKES:																	*
*		ListElement* first_ptr ->											*
*			Pointer to first element in desired list.						*
*																			*
*		Entity* new_ent ->													*
*			Pointer to new entity to add to desired list.					*
*																			*
*		char* _name ->														*
*			Name to give the new list entry.								*
*																			*
****************************************************************************/
void add_ent(ListElement* , Entity* new_ent, char* _name);


/****************************************************************************
*	@@WARNING this doesn't work yet, results in seg fault.					*
*																			*
*	@NOTE:																	*
*		Removes an element from the list, can be any element except the 	*
*		first element.														*
*																			*
*	@TAKES:																	*
*		ListElement* first_ptr ->											*
*			Pointer to first element in desired list.						*
*																			*
*		ListElement* element_to_remove_ptr ->								*
*			Pointer to the element to remove.								*
*																			*
****************************************************************************/
void remove_element(ListElement* first_ptr, ListElement* el_ptr);

/****************************************************************************
*	@NOTE:																	*
*		Initialise the list with a pointer to an entity.					*
*																			*
*	@TAKES:																	*
*		Entity* ent_ptr ->													*
*			Pointer to first entity to be stored in the list.				*
*																			*
*		char* name ->														*
*			Name of the list entry.											*
*																			*
*	@RETURNS:																*
*		ListElement* first_ptr ->											*
*			Pointer to the first element in the new list created.			*
*																			*
****************************************************************************/
ListElement* init_list_ent_ptr(Entity* e, char* _name);


/****************************************************************************
*	@NOTE:																	*
*		Function to free all pointers in a list.							*
*																			*
*	@TAKES:																	*
*		ListElement* first_ptr ->											*
*			Pointer to first element in desired list.						*
*																			*
****************************************************************************/
void free_list(ListElement* );

/****************************************************************************
*	@NOTE:																	*
*		Function to get the elements of a desired list in the form of an	* 
*		array.																*
*																			*
*	@TAKES:																	*
*		ListElement* first_ptr ->											*
*			Pointer to first element in desired list.						*
*																			*
*	@RETURNS:																*
*		ListElement** list_arr ->											*
*			An array of all items in a specific list.						*
*																			*
****************************************************************************/
ListElement** get_list_arr(ListElement* );


/**
	@NOTE: Same as RenderCopyListCenter only it draws the sprite from origin
		   top left.
**/
void RenderCopyList(ListElement* );

/****************************************************************************
*	@NOTE:																	*
*		Copies every element in the list given's entities to the render		*
*		buffer, or doesn't if the entitie's 'hidden' value is set to true.	*
*		this function also decides whether or not to draw the debug box.	*
*																			*
*	@TAKES:																	*
*		ListElement* first_ptr ->											*
*			pointer to the first element in desired	list.					*
*																			*
****************************************************************************/
void RenderCopyListCenter(ListElement* );


/****************************************************************************
*	@NOTE:																	*
*		Counts the number of collisions found when cross-referencing		*
*		each element in a specified list with each other element.			*
*																			*
*	@TAKES:																	*
*		ListElement* first_ptr -> pointer to the first element in desired	*
*		list.																*
*																			*
*	@RETURNS:																*
*		int collision_count -> number of collisions found.					*
****************************************************************************/
int count_collisions(ListElement* );

/****************************************************************************
*	@NOTE:																	*
*		Functions to set or unset debug box drawing on all elements of a	*
*		list.																*
*																			*
*	@TAKES:																	*
*		ListElement* first_ptr ->											*
*			Pointer to first element in desired list.						*
*																			*
****************************************************************************/
void debug_all(ListElement* first_ptr);
void un_debug_all(ListElement* first_ptr);

/****************************************************************************
*	@NOTE:																	*
*		Functions to set or unset 'hidden' property on all entities in a	*
*		list. Effectively whether or not they are drawn.					*
*																			*
*	@TAKES:																	*
*		ListElement* first_ptr ->											*
*			Pointer to first element in desired list.						*
*																			*
****************************************************************************/
void show_all(ListElement* first_ptr);
void hide_all(ListElement* first_ptr);

/****************************************************************************
*	@NOTE:																	*
*		Functions to apply movement to all elements of a list.				*
*																			*
*	@TAKES:																	*
*		ListElement* first_ptr ->											*
*			Pointer to first element in desired list.						*
*																			*	
*		int _x ->															*
*			New x position to assign to each entity.						*
*																			*
*		int _y ->															*
*			New y position to assign to each entity.						*
*																			*
****************************************************************************/
void move_all(ListElement* first_ptr, int _x, int _y);
void set_all(ListElement* first_ptr, int _x, int _y);

/**
	@func: copies one list to another
	
	@note: all it actually does is set the first pointer of the second one 
	to the first of the first. ( @warn: list_b full is unnaccounted for)
	
**/
int copy_list(ListElement* first_a, ListElement* first_b);

#endif