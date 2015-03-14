/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-04 17:37:13
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-13 21:02:53
*/

#ifndef _ELUCENAP_GRAPHICSH
#define _ELUCENAP_GRAPHICSH

#include "rogue.h"
#include <stdbool.h>

/**
 InitGraphics: Initializes the graphic library
 Pre: Not applicable
 Post: The graphic library is ready
*/
void initGraphics();

/**
 EndGraphics: Finalizes the graphic library
 Pre: Not applicable
 Post: The graphic library is deactivated
*/
void endGraphics();

/**
 DrawElement: Draw a $element in the selected ($x, $y) position of the screen
 Pre: The graphic library is ready
 Post: The element is printed on the screen
*/
void drawElement(int x, int y, RogueElement element);

/**
 DrawLevel: Draw the $level in the screen
 Pre: The graphic library is ready
 Post: The level is printed on the screen
*/
void drawLevel(Level* level);

/**
 GetInput: Read a character input from the keyboard, and run its command
 Pre: The graphic library is ready
 Post: Returns false if 'q' is read, true otherwise
*/
bool getInput(Level* level);

#endif
