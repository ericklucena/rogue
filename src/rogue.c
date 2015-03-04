/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-02 15:39:03
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-04 17:31:30
*/

#include "rogue.h"
#include <stdlib.h>
#include <stdbool.h>

Room* newRoom (int height, int width, int x, int y)
{
	int i, j;
	bool error = false;

	Room *room;

	room = malloc (sizeof(Room));

	if (room != NULL)
	{
		room->elements = malloc(sizeof(RogueElement*)*height);

		if (room->elements != NULL)
		{
			for (i=0; i<height; i++)
			{
				room->elements[i] = malloc(sizeof(RogueElement)*width);

				if (room->elements[i] == NULL)
				{
					error = true;
					for (i-=1; i>=0; i--)
					{
						free(room->elements[i]);
					}
					break;
				}
			}
		}
		else
		{
			error = true;
		}

		if (error)
		{
			free(room);
			room = NULL;
		}
		else
		{
			room->position.x = x;
			room->position.y = y;
			for ( i=0; i<height; i++)
			{
				room->elements[i][0] = re_wall;
				room->elements[i][width-1] = re_wall;
			}
			for ( i=0; i<width; i++)
			{
				room->elements[0][i] = re_wall;
				room->elements[height-1][i] = re_wall;
			}

			for (i=1; i<height-1; i++)
			{
				for (j=1; j<width-1; j++)
				{
					room->elements[i][j] = re_floor;
				}				
			}

		}
	}
	return room;
}

void freeRoom(Room* room)
{
	int i;

	for ( i=0; i<room->width; i++) 
	{
		free(room->elements[i]);
	}
	free(room->elements);
	free(room);
}

Level* newLevel (Hero hero, int nRooms)
{
	Level* level;

	level = malloc(sizeof(Level));

	if (level != NULL)
	{
		level->rooms = malloc(sizeof(Room)*nRooms);

		if(level->rooms == NULL)
		{
			free(level);
			level = NULL;
		}
	}

	return level;
}

void freeLevel (Level* level)
{
	free(level->rooms);
	free(level);
}
