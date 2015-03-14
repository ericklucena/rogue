/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-02 15:36:16
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-13 19:54:51
*/

#ifndef _ELUCENAP_ROGUEH
#define _ELUCENAP_ROGUEH

#define LEVEL_MAX_HEIGHT 100
#define LEVEL_MAX_WIDTH 100
#define MESSAGE_MAX_LENGTH 101
#define MAX_NAME_SIZE 51
#define MAX_DESCRIPTION_SIZE 51
#define INVENTORY_SIZE 100
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
    re_corridor,
    re_door,
    re_vertical_wall,
    re_horizontal_wall,
    re_floor,
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
    bool marked;
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
	int inventory[4];
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
    char message[101];
	Room** rooms;
    RogueElement** elements;
} Level;

Room* newRoom (int width, int height, int x, int y, int nObjects);
void freeRoom (Room* room);
void printRoom (Room* room);

Level* newLevel (int nRooms);
void freeLevel (Level* level);
void initLevel (Level* level);
void initCorridors (Level* level);
void createCorridor (Level* level, Position a, Position b);

void moveHero(Level* level, Direction direction);

int calculateDistance(Position a, Position b);

#endif // _ELUCENAP_ROGUEH
