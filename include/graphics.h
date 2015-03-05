/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-04 17:37:13
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-05 00:26:57
*/

#ifndef _ELUCENAP_GRAPHICSH
#define _ELUCENAP_GRAPHICSH

#include "rogue.h"

void initGraphics();
void endGraphics();
void drawElement(int x, int y, RogueElement element);
void drawLevel(Level* level);

#endif
