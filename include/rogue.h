/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-02 15:36:16
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-05 00:23:52
*/

#ifndef _ELUCENAP_ROGUEH
#define _ELUCENAP_ROGUEH

#define LEVEL_MAX_HEIGHT 100
#define LEVEL_MAX_WIDTH 100
#define MAX_NAME_SIZE 51
#define MAX_DESCRIPTION_SIZE 51
#define INVENTORY_SIZE 10

#include <stdbool.h>

typedef struct position
{
	int x;
	int y;
} Position;

typedef enum direction
{
    up,
    upRight,
    right,
    downRight,
    down,
    downLeft,
    left,
    upLeft
} Direction;

typedef enum rogueElement
{
	re_blank,
    re_floor,
	re_corridor,
    re_horizontal_wall,
	re_vertical_wall,
    re_door,
	re_stairs,
	re_gold,
	re_magic,
	re_hero,
	re_potion,
	re_weapon,
	re_monster
} RogueElement;

typedef struct object
{
    Position position;
    RogueElement element;
} Object;

typedef struct item
{
	char name[MAX_NAME_SIZE];
	char description[MAX_DESCRIPTION_SIZE];
	int quantity;
} Item;

typedef struct hero
{
	Position position;
	Item inventory[INVENTORY_SIZE];
} Hero;

typedef struct room
{
	int height;
	int width;
	Position position;
    bool visible;
} Room;

typedef struct level
{
	Hero hero;
    int nRooms;
	Room** rooms;
    RogueElement** elements;
} Level;

Room* newRoom (int width, int height, int x, int y);
void freeRoom (Room* room);

Level* newLevel (Hero hero, int nRooms);
void freeLevel (Level* level);
void initLevel (Level* level);

void moveHero(Level* level, Direction direction);


#endif // _ELUCENAP_ROGUEH
