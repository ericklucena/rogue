/******************************************a3.c*********************************************
Student Name: Erick Lucena Palmeira Silva    Student Number:  0905100-
Date: 02/12/2015                             Course Name: cis2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
********************************************************************************************/

/* 
* CIS 2500 A3 Main function
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-02 14:52:32
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-13 22:47:31
* This file contains the implementation of the main fuction
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

    freeLevel(level);

    return 0;
}
