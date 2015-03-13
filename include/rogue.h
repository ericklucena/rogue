/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-02 15:36:16
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-12 18:57:25
*/

#ifndef _ELUCENAP_ROGUEH
#define _ELUCENAP_ROGUEH

#define LEVEL_MAX_HEIGHT 100
#define LEVEL_MAX_WIDTH 100
#define MAX_NAME_SIZE 51
#define MAX_DESCRIPTION_SIZE 51
#define INVENTORY_SIZE 10
#define ROOMS_PER_LEVEL 6

#include <stdbool.h>

typedef struct position
{
	int x;
	int y;
} Position;

typedef enum direction
{
    d_up,
    d_upRight,
    d_right,
    d_downRight,
    d_down,
    d_downLeft,
    d_left,
    d_upLeft
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
    RogueElement element;
    Position position;
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
    bool visible;
    Position position;
    int nObjects;
    Object* objects;
} Room;

typedef struct level
{
	Hero hero;
    int nRooms;
	Room** rooms;
    RogueElement** elements;
} Level;

Room* newRoom (int width, int height, int x, int y, int nObjects);
void freeRoom (Room* room);
void printRoom (Room* room);

Level* newLevel (int nRooms);
void freeLevel (Level* level);
void initLevel (Level* level);

void moveHero(Level* level, Direction direction);


#endif // _ELUCENAP_ROGUEH
