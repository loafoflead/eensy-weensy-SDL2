#ifndef RENDER__ARRAYS__H
#define RENDER__ARRAYS__H

#include "animations.h"
#include "RenderWrap.h"
#include "RenderList.h"
#include "general.h"

#include <SDL2/SDL.h>
#include <math.h>

void list_ents(Entity *arr[]);

void remove_entity(Entity *arr[], Entity* ent);

void draw_array(Entity *arr[]);

void destroy_array(Entity *arr[]);

Entity *search_array(Entity *array[], char *texture_name);
int count_elements(Entity *arr[]);

void set_array_pos(Entity *arr[], int new_x, int new_y);

void change_property(Entity *arr[], enum entity_properties props, int value);
void toggle_property(Entity *arr[], enum entity_properties props);


#endif