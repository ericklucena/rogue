/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-02 14:52:32
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-13 20:07:20
*/

#include "graphics.h"
#include "rogue.h"
#include "io.h"

int main (int argc, char** argv) {

    Level* level;

    level = readFile(argv[1]);

    initLevel(level);
    initCorridors(level);
    initGraphics();

    do
    {
        drawLevel(level);
    } while (getInput(level));

    endGraphics();

    printf("You found %d magics.\n", level->hero.inventory[0]);
    printf("You found %d potions.\n", level->hero.inventory[1]);
    printf("You found %d gold pieces.\n", level->hero.inventory[2]);
    printf("You found %d weapons.\n", level->hero.inventory[3]);

    return 0;
}
