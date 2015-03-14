/****************************************io.c***********************************************
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
* CIS 2500 A3 I/O functions implementation
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-02 15:37:58
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-13 22:28:52
* This file contains the implementation of the I/O fuctions
*/

#include "io.h"
#include "parser.h"
#include "util.h"
#include "rogue.h"
#include <string.h>


Level* readFile (char* filename)
{
    int i;
    
    int argc;
    char** argv;
    
    int roomIndex=0;
    int objectIndex;
    char buffer[IO_BUFFER_SIZE];

    int height, width;
    int x, y;
    int roomX, roomY;
    
    FILE* file;
    Level* level;
    Object object;
    Room* room;
    Hero hero;

    roomX = 2;
    roomY = 2;

    level = newLevel(ROOMS_PER_LEVEL);

    file = fopen(filename, "r");

    while (fgets(buffer, IO_BUFFER_SIZE-1, file) != NULL)
    {
        objectIndex = 0;

        argv = parseLine(buffer, &argc);
        sscanf(argv[0],"%dX%d", &height, &width);
        room = newRoom(height+2, width+2, roomX+(25-height)/2, roomY+(30-width)/2, (roomIndex==0)?argc-2:argc-1);
        
        roomY += 30;

        if (roomY>90)
        {
            roomY = 2;
            roomX += 25;
        }


        for (i=1; i<argc; i++)
        {
            switch (argv[i][0])
            {
            case 'd':
                object.element = re_open_door;
                sscanf(argv[i]+2, "%d", &x);
                switch (argv[i][1])
                {
                case 'n':
                    object.position.x = 0;
                    object.position.y = x;
                    break;
                case 'e':
                    object.position.x = x;
                    object.position.y = room->width-1;
                    break;
                case 's':
                    object.position.x = room->height-1;
                    object.position.y = x;
                    break;
                case 'w':
                    object.position.x = x;
                    object.position.y = 0;
                    break;
                }
                break;
            case 's':
                sscanf(argv[i]+1,"%d,%d", &x, &y);
                object.element = re_stairs;
                object.position.x = x;
                object.position.y = y;
                break;
            case 'g':
                sscanf(argv[i]+1,"%d,%d", &x, &y);
                object.element = re_gold;
                object.position.x = x;
                object.position.y = y;
                break;
            case 'm':
                sscanf(argv[i]+1,"%d,%d", &x, &y);
                object.element = re_magic;
                object.position.x = x;
                object.position.y = y;
                break;
            case 'h':
                sscanf(argv[i]+1,"%d,%d", &x, &y);
                object.element = re_hero;
                hero.inventory[0] = 0;
                hero.inventory[1] = 0;
                hero.inventory[2] = 0;
                hero.inventory[3] = 0;
                hero.position.x = room->position.x + x;
                hero.position.y = room->position.y + y;
                level->hero = hero;
                break;
            case 'p':
                sscanf(argv[i]+1,"%d,%d", &x, &y);
                object.element = re_potion;
                object.position.x = x;
                object.position.y = y;
                break;
            case 'w':
                sscanf(argv[i]+1,"%d,%d", &x, &y);
                object.element = re_weapon;
                object.position.x = x;
                object.position.y = y;
                break;
            case 'M':
                sscanf(argv[i]+1,"%d,%d", &x, &y);
                object.element = re_monster;
                object.position.x = x;
                object.position.y = y;
                break;
            }

            if (object.element != re_hero)
            {
                object.marked = false;
                room->objects[objectIndex++] = object;
            }

        }
        level->rooms[roomIndex++] = room;
        freeArgs(argv, argc);
    }

    return level;
}

