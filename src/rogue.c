/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-02 15:39:03
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-05 00:18:22
*/

#include "rogue.h"
#include <stdlib.h>
#include <stdbool.h>

Room* newRoom (int height, int width, int x, int y)
{
    Room *room;

    room = malloc (sizeof(Room));

    if (room != NULL)
    {        
        room->height = height;
        room->width = width;
        room->position.x = x;
        room->position.y = y;
    }
    return room;
}

void freeRoom(Room* room)
{
    free(room);
}

Level* newLevel (Hero hero, int nRooms)
{
    int i;
    bool error;
    Level* level;

    level = malloc(sizeof(Level));

    if (level != NULL)
    {
        level->rooms = malloc(sizeof(Room*)*nRooms);

        if(level->rooms != NULL)
        {
            level->hero = hero;
            level->nRooms = nRooms;

            level->elements = malloc(sizeof(RogueElement*)*LEVEL_MAX_HEIGHT);

            if (level->elements != NULL)
            {
                for (i=0; i<LEVEL_MAX_HEIGHT; i++)
                {
                    level->elements[i] = calloc(sizeof(RogueElement), LEVEL_MAX_WIDTH);

                    if (level->elements[i] == NULL)
                    {
                        error = true;
                        for (i-=1; i>=0; i--)
                        {
                            free(level->elements[i]);
                        }
                        break;
                    }
                }
            }
            else
            {
                free(level->rooms);
                free(level);
            }
            
            if (error)
            {
                free(level->elements);
                free(level->rooms);
                free(level);
            }
        }
        else
        {
            free(level);
        }
    }

    return level;
}

void freeLevel (Level* level)
{
    free(level->rooms);
    free(level);
}

void initLevel (Level* level)
{
    int i, j, k;
    Room* room;

    for (k=0; k<level->nRooms; k++)
    {
        room = level->rooms[k];
        for (i=0;i<level->rooms[k]->height; i++)
        {
            for (j=0;j<level->rooms[k]->height; j++)
            {
                level->elements[room->position.x+i][room->position.y+j] = re_floor;
            }
        }

        for ( i=0; i<room->height; i++)
        {
            level->elements[room->position.x+i][room->position.y] = re_vertical_wall;
            level->elements[room->position.x+i][room->position.y+room->width-1] = re_vertical_wall;
        }

        for ( i=0; i<room->width; i++)
        {
            level->elements[room->position.x][room->position.y+i] = re_horizontal_wall;
            level->elements[room->position.x+room->height-1][room->position.y+i] = re_horizontal_wall;
        }

    }
}

bool isWalkable(RogueElement element)
{
    bool walkable = false;
    
    switch (element)
    {
    case re_floor:
    case re_corridor:
    case re_door:
        walkable = true;
        break;
    case re_blank:
    case re_vertical_wall:
    case re_horizontal_wall:
    case re_stairs:
    case re_gold:
    case re_magic:
    case re_hero:
    case re_potion:
    case re_weapon:
    case re_monster:
        walkable = false;
        break;
    }

    return walkable;
}

void moveHero(Level* level, Direction direction)
{

    switch (direction)
    {
    case up:
        if(isWalkable(level->elements[level->hero.position.x-1][level->hero.position.y]))
        {
            level->hero.position.x -= 1;
        }
        break;
    case upRight:
        if(isWalkable(level->elements[level->hero.position.x-1][level->hero.position.y+1]))
        {
            level->hero.position.x -= 1;
            level->hero.position.y += 1;   
        }
        break;
    case right:
        if(isWalkable(level->elements[level->hero.position.x][level->hero.position.y+1]))
        {
            level->hero.position.y += 1;
        }
        break;
    case downRight:
        if(isWalkable(level->elements[level->hero.position.x+1][level->hero.position.y+1]))
        {
            level->hero.position.x += 1;
            level->hero.position.y += 1;
        }
        break;
    case down:
        if(isWalkable(level->elements[level->hero.position.x+1][level->hero.position.y]))
        {
            level->hero.position.x += 1;
        }
        break;
    case downLeft:
        if(isWalkable(level->elements[level->hero.position.x+1][level->hero.position.y-1]))
        {
            level->hero.position.x += 1;
            level->hero.position.y -= 1;
        }
        break;
    case left:
        if(isWalkable(level->elements[level->hero.position.x][level->hero.position.y-1]))
        {
            level->hero.position.y -= 1;
        }
        break;
    case upLeft:
        if(isWalkable(level->elements[level->hero.position.x-1][level->hero.position.y-1]))
        {
            level->hero.position.x -= 1;
            level->hero.position.y -= 1;
        }
        break;
    }
}