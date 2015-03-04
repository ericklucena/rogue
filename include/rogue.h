/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-02 15:36:16
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-04 17:31:19
*/

#ifndef _ELUCENAP_ROGUEH
#define _ELUCENAP_ROGUEH

#define MAX_NAME_SIZE 51
#define MAX_DESCRIPTION_SIZE 51
#define INVENTORY_SIZE 10

typedef struct position
{
	int x;
	int y;
} Position;

typedef enum rogueElement
{
	re_blank,
	re_floor,
	re_wall,
	re_stairs,
	re_gold,
	re_magic,
	re_hero,
	re_potion,
	re_weapon,
	re_monster
} RogueElement;

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
	RogueElement **elements;
} Room;

typedef struct level
{
	Hero hero;	
	Room *rooms;
} Level;

Room* newRoom (int width, int height, int x, int y);
void freeRoom (Room* room);
Level* newLevel (Hero hero, int nRooms);
void freeLevel (Level* level);


#endif // _ELUCENAP_ROGUEH
