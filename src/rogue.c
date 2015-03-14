/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-02 15:39:03
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-13 19:59:22
*/

#include "rogue.h"
#include <math.h>
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
            //fprintf(stderr, "Malloc error (Object) in newRoom\n");
            free(room);
            room = NULL;
        }
    }
    else
    {
        //fprintf(stderr, "Malloc error (Room) in newRoom\n");
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
        text = "gold piece";
        break;
    case re_magic:
        text = "magic scroll";
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
                        //fprintf(stderr, "Malloc error (RogueElement[]) in newLevel\n");
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
                //fprintf(stderr, "Malloc error (RogueElement[][]) in newLevel\n");
                free(level->rooms);
                free(level);
                level = NULL;
            }
            
            if (error)
            {
                //fprintf(stderr, "Malloc error (newLevel) in newLevel\n");
                free(level->elements);
                free(level->rooms);
                free(level);
                level = NULL;
            }
        }
        else
        {
            //fprintf(stderr, "Malloc error (Room) in newLevel\n");
            free(level);
            level = NULL;
        }
    }
    else
    {
        //fprintf(stderr, "Malloc error (Level) in newLevel\n");
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
        //fprintf(stderr, "%d\n", level->nRooms);
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
            room->objects[i].position.x += room->position.x;
            room->objects[i].position.y += room->position.y;
            level->elements[room->objects[i].position.x][room->objects[i].position.y] = room->objects[i].element;
        }
    }
}

void initCorridors (Level* level)
{
    int i;
    int j;
    int k;
    int l;
    int distance;
    int roomIndexB;
    int objectIndexB;
    Room *roomA;
    Room *roomB;

    for (i=0; i<ROOMS_PER_LEVEL; i++)
    {
        roomA = level->rooms[i];

        for (j=0; j<roomA->nObjects; j++)
        {
            if(roomA->objects[j].element == re_door && !roomA->objects[j].marked)
            {
                roomA->objects[j].marked = true;
                distance = LEVEL_MAX_WIDTH*LEVEL_MAX_HEIGHT;

                for (k=0; k<ROOMS_PER_LEVEL; k++)
                {
                    if (i==k)
                    {
                        continue;
                    }
                    roomB = level->rooms[k];

                    for (l=0; l<roomB->nObjects; l++)
                    {
                        if(roomB->objects[l].element == re_door && !roomB->objects[l].marked)
                        {
                            if (calculateDistance(roomA->objects[j].position, roomB->objects[l].position) < distance)
                            {
                                roomIndexB = k;
                                objectIndexB = l;
                                distance = calculateDistance(roomA->objects[j].position, roomB->objects[l].position);
                            }
                        }
                    }
                }
                //fprintf(stderr, "CORRIDOR\n");
                //fprintf(stderr, "(%d, %d) (%d, %d)\n", roomA->objects[j].position.x, roomA->objects[j].position.y, level->rooms[roomIndexB]->objects[objectIndexB].position.x, level->rooms[roomIndexB]->objects[objectIndexB].position.y);
                createCorridor(level, roomA->objects[j].position, level->rooms[roomIndexB]->objects[objectIndexB].position);
                level->rooms[roomIndexB]->objects[objectIndexB].marked = true;
            }
        }
    }
}

void createCorridor (Level* level, Position a, Position b)
{
    int i;
    int xDiff;
    int yDiff;
    bool moved;
    Direction preference[4];

    while ((a.x != b.x) || (a.y != b.y))
    {
        moved = false;
        xDiff = b.x - a.x;
        yDiff = b.y - a.y;

        if (abs(xDiff) > abs(yDiff))
        {
            preference[0] = (xDiff>0) ? d_down : d_up;
            preference[1] = (yDiff>0) ? d_right : d_left;
            preference[2] = (yDiff>0) ? d_left : d_right;        
            preference[3] = (xDiff>0) ? d_up : d_down;
        }
        else if (abs(xDiff) < abs(yDiff))
        {
            preference[0] = (yDiff>0) ? d_right : d_left;
            preference[1] = (xDiff>0) ? d_down : d_up;
            preference[2] = (xDiff>0) ? d_up : d_down;
            preference[3] = (yDiff>0) ? d_left : d_right;
        }

        for (i=0; i<4 && !moved; i++)
        {
            switch (preference[i])
            {
            case d_up:
                if (level->elements[a.x-1][a.y] <= re_door)
                {
                    a.x = a.x-1;
                    moved = true;
                }
                break;

            case d_right:
                if (level->elements[a.x][a.y+1] <= re_door)
                {
                    a.y = a.y+1;
                    moved = true;
                }
                break;

            case d_down:
                if (level->elements[a.x+1][a.y] <= re_door)
                {
                    a.x = a.x+1;
                    moved = true;
                }
                break;

            case d_left:
                if (level->elements[a.x-1][a.y] <= re_door)
                {
                    a.y = a.y-1;
                    moved = true;
                }
                break;

            default:
                //Not applicable
                break;
            }

        }

        if (moved && ((a.x != b.x) || (a.y != b.y)))
        {
            level->elements[a.x][a.y] = re_corridor;
        }
        else
        {
            //fprintf(stderr, "Cannot create corridor in createCorridor\n");
            return;
        }
    }
}

bool isWalkable (RogueElement element)
{
    bool walkable = false;
    
    switch (element)
    {
    case re_floor:
    case re_corridor:
    case re_door:
    case re_stairs:
    case re_gold:
    case re_magic:
    case re_potion:
    case re_weapon:
        walkable = true;
        break;
    case re_hero:
    case re_blank:
    case re_vertical_wall:
    case re_horizontal_wall:
    case re_monster:
        walkable = false;
        break;
    }

    return walkable;
}

bool isPickable (RogueElement element)
{
    bool walkable = false;
    
    switch (element)
    {
    case re_gold:
    case re_magic:
    case re_potion:
    case re_weapon:
        walkable = true;
        break;
    case re_floor:
    case re_corridor:
    case re_door:
    case re_stairs:
    case re_hero:
    case re_blank:
    case re_vertical_wall:
    case re_horizontal_wall:
    case re_monster:
        walkable = false;
        break;
    }

    return walkable;
}

void pickItem (Level* level, RogueElement element)
{
    switch (element)
    {
        case re_magic:
            level->hero.inventory[0]++;
            break;

        case re_potion:
            level->hero.inventory[1]++;
            break;

        case re_gold:
            level->hero.inventory[2]++;
            break;

        case re_weapon:
            level->hero.inventory[3]++;
            break;

        default:
            break;
    }
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

    if (isPickable(level->elements[level->hero.position.x][level->hero.position.y]))
    {
        sprintf(level->message, "You found a %s", elementText(level->elements[level->hero.position.x][level->hero.position.y]));
        pickItem(level, level->elements[level->hero.position.x][level->hero.position.y]);
        level->elements[level->hero.position.x][level->hero.position.y] = re_floor;
    }
}

int calculateDistance(Position a, Position b)
{
    int xDiff;
    int yDiff;

    xDiff = abs(b.x - a.x);
    yDiff = abs(b.y - a.y);

    return sqrt(xDiff*xDiff + yDiff*yDiff);
}
