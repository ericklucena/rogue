/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-02 15:36:16
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-13 20:53:22
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

/**
 NewRoom: Allocates memory for a new room with the selected $width, $height, ($x, $y) position and $nObjects number
 Pre: Pass the parameters
 Post: Returns a pointer to room if successful, NULL otherwise
*/
Room* newRoom (int width, int height, int x, int y, int nObjects);

/**
 FreeRoom: Frees the memory occupied by $room
 Pre: Pass the parameter
 Post: The memory occupied by room is freed
*/
void freeRoom (Room* room);

/**
 PrintRoom: Prints the contents of a $room
 Pre: Pass the parameter
 Post: The contents of the room are printed on the screen
*/
void printRoom (Room* room);


/**
 NewLevel: Allocates memory for a new level with the selected $nRooms
 Pre: Pass the parameter
 Post: Returns a pointer to Level if successful, NULL otherwise
*/
Level* newLevel (int nRooms);

/**
 FreeLevel: Frees the memory occupied by $level
 Pre: Pass the parameter
 Post: The memory occupied by room is freed
*/
void freeLevel (Level* level);

/**
 InitLevel: Initializes $level to be used by the graphic library
 Pre: Pass the parameter
 Post: The level is ready to be used by the graphic library
*/
void initLevel (Level* level);

/**
 InitCorridors: Creates the  $level corridors between the rooms
 Pre: Pass the parameter
 Post: The level has corridors connecting the rooms
*/
void initCorridors (Level* level);

/**
 CreateCorridor: Creates a corridor in the $level connecting the positions $a and $b
 Pre: Pass the parameter
 Post: The level has corridors connecting the positions
*/
void createCorridor (Level* level, Position a, Position b);

/**
 MoveHero: Move the hero in the $level in the selected $direction
 Pre: Pass the parameters
 Post: If it is possible, the hero is moved
*/
void moveHero(Level* level, Direction direction);

/**
 CalculateDistance: Calculates and return the distance between the postions $a and $b
 Pre: Pass the parameters
 Post: Returns the distance
*/
int calculateDistance(Position a, Position b);

#endif // _ELUCENAP_ROGUEH
