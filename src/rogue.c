/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-02 15:39:03
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-12 18:58:08
*/

#include "rogue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Room* newRoom (int height, int width, int x, int y, int nObjects)
{
    Room *room;

    room = malloc (sizeof(Room));

    if (room != NULL)
    {        
        room->height = height;
        room->width = width;
        room->position.x = x;
        room->position.y = y;
        room->nObjects = nObjects;
        room->objects = malloc(sizeof(Object)*nObjects);

        if (room->objects == NULL)
        {
            fprintf(stderr, "Malloc error (Object) in newRoom\n");
            free(room);
            room = NULL;
        }
    }
    else
    {
        fprintf(stderr, "Malloc error (Room) in newRoom\n");
    }

    return room;
}

const char* elementText(RogueElement element)
{
    char* text;
    switch (element)
    {
    case re_door:
        text = "door";
        break;
    case re_stairs:
        text = "stairs";
        break;
    case re_gold:
        text = "gold";
        break;
    case re_magic:
        text = "magic";
        break;
    case re_hero:
        text = "hero";
        break;
    case re_potion:
        text = "potion";
        break;
    case re_weapon:
        text = "weapon";
        break;
    case re_monster:
        text = "monster";
        break;
    default:
        break;
    }

    return text;
}

void freeRoom(Room* room)
{
    free(room->objects);
    free(room);
}

void printRoom(Room* room)
{
    int i;

    printf("(%d, %d) %d x %d\n", room->position.x, room->position.y, room->height, room->width);

    for (i=0; i<room->nObjects; i++)
    {
        printf("%s\n", elementText(room->objects[i].element));
    }
}

Level* newLevel (int nRooms)
{
    int i;
    bool error = false;
    Level* level;

    level = malloc(sizeof(Level));

    if (level != NULL)
    {
        level->nRooms = nRooms;
        level->rooms = malloc(sizeof(Room*)*nRooms);

        if(level->rooms != NULL)
        {
            level->elements = malloc(sizeof(RogueElement*)*LEVEL_MAX_HEIGHT);

            if (level->elements != NULL)
            {
                for (i=0; i<LEVEL_MAX_HEIGHT; i++)
                {
                    level->elements[i] = calloc(sizeof(RogueElement), LEVEL_MAX_WIDTH);

                    if (level->elements[i] == NULL)
                    {
                        error = true;
                        fprintf(stderr, "Malloc error (RogueElement[]) in newLevel\n");
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
                fprintf(stderr, "Malloc error (RogueElement[][]) in newLevel\n");
                free(level->rooms);
                free(level);
                level = NULL;
            }
            
            if (error)
            {
                fprintf(stderr, "Malloc error (newLevel) in newLevel\n");
                free(level->elements);
                free(level->rooms);
                free(level);
                level = NULL;
            }
        }
        else
        {
            fprintf(stderr, "Malloc error (Room) in newLevel\n");
            free(level);
            level = NULL;
        }
    }
    else
    {
        fprintf(stderr, "Malloc error (Level) in newLevel\n");
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
        fprintf(stderr, "%d\n", level->nRooms);
        room = level->rooms[k];

        for (i=0;i<room->height; i++)
        {
            for (j=0;j<room->width; j++)
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

        for (i=0; i<room->nObjects; i++)
        {
            level->elements[room->position.x+room->objects[i].position.x][room->position.y+room->objects[i].position.y] = room->objects[i].element;
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
    case d_up:
        if(isWalkable(level->elements[level->hero.position.x-1][level->hero.position.y]))
        {
            level->hero.position.x -= 1;
        }
        break;
    case d_upRight:
        if(isWalkable(level->elements[level->hero.position.x-1][level->hero.position.y+1]))
        {
            level->hero.position.x -= 1;
            level->hero.position.y += 1;   
        }
        break;
    case d_right:
        if(isWalkable(level->elements[level->hero.position.x][level->hero.position.y+1]))
        {
            level->hero.position.y += 1;
        }
        break;
    case d_downRight:
        if(isWalkable(level->elements[level->hero.position.x+1][level->hero.position.y+1]))
        {
            level->hero.position.x += 1;
            level->hero.position.y += 1;
        }
        break;
    case d_down:
        if(isWalkable(level->elements[level->hero.position.x+1][level->hero.position.y]))
        {
            level->hero.position.x += 1;
        }
        break;
    case d_downLeft:
        if(isWalkable(level->elements[level->hero.position.x+1][level->hero.position.y-1]))
        {
            level->hero.position.x += 1;
            level->hero.position.y -= 1;
        }
        break;
    case d_left:
        if(isWalkable(level->elements[level->hero.position.x][level->hero.position.y-1]))
        {
            level->hero.position.y -= 1;
        }
        break;
    case d_upLeft:
        if(isWalkable(level->elements[level->hero.position.x-1][level->hero.position.y-1]))
        {
            level->hero.position.x -= 1;
            level->hero.position.y -= 1;
        }
        break;
    }
}

