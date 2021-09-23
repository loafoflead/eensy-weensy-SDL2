#include "FontRenderWrap.h"
#include "RenderWrap.h"
#include "RenderList.h"

#include <stdio.h>
#include <string.h>

/** @VARS	**/


/** @NOTE: big challenge ahead, ur tryna make a font cache, it won't work first try maybe not even at all that's ok.
	this is dumb anywaysjdhf anything works :] don't worry about it too much.
	
	anyway, off we pop!!! 
	
	@TODO: texture atlas
**/


/** 
	: attempt 2, plan it out this time, what do you want to acheive, then figure out how.
	
	1: I want to be able to load a font into an object; i.e. special font object, then be able to pass it as a ref to a 
	fucnction that will then draw at least a character to the screen.
	2: I want for it to not reload a texture each time it draws a new character, i want a cutout of a texture atlas.
	3: I want the lookup thru the texture atlas to be quick
	
	OK, so how do i do that???
	
	Array of indexes into the atlas, each containing it's own dimensions in the form of an SDL_Rect.
	
	
	
	: i will get back to this but a lot l8er ok?? thx :] 
	
**/