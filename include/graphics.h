/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-04 17:37:13
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-13 20:05:24
*/

#ifndef _ELUCENAP_GRAPHICSH
#define _ELUCENAP_GRAPHICSH

#include "rogue.h"
#include <stdbool.h>

void initGraphics();
void endGraphics();
void drawElement(int x, int y, RogueElement element);
void drawLevel(Level* level);
bool getInput(Level* level);

#endif
