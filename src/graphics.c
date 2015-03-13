/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-04 17:36:51
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-13 03:21:10
*/

#include <ncurses.h>
#include "rogue.h"

void initGraphics()
{
    initscr();
    cbreak ();
    noecho ();
    curs_set(0);
}

void endGraphics()
{
    endwin();
}

void drawElement(int x, int y, RogueElement element)
{
    switch (element)
    {
    case re_blank:
        mvaddch(x, y, ' ');
        break;

    case re_floor:
        mvaddch(x, y, '.');
        break;

    case re_vertical_wall:
        mvaddch(x, y, '|');
        break;

    case re_horizontal_wall:
        mvaddch(x, y, '-');
        break;

    case re_door:
        mvaddch(x, y, '+');
        break;


    case re_corridor:
        mvaddch(x, y, '#');
        break;

    case re_stairs:
        mvaddch(x, y, '%');
        break;

    case re_gold:
        mvaddch(x, y, '*');
        break;

    case re_magic:
        mvaddch(x, y, '?');
        break;

    case re_hero:
        mvaddch(x, y, '@');
        break;

    case re_potion:
        mvaddch(x, y, '!');
        break;

    case re_weapon:
        mvaddch(x, y, ')');
        break;

    case re_monster:
        mvaddch(x, y, 'M');
        break;

    }
}

void drawMessage(Level* level)
{
    mvwprintw(stdscr, 0, 0, level->message);
    level->message[0] = '\0';
}

void drawLevel (Level* level)
{
    int i, j;

    for (i=0; i<LEVEL_MAX_HEIGHT; i++)
    {
        for (j=0; j<LEVEL_MAX_WIDTH; j++)
        {
            drawElement(i, j, level->elements[i][j]);
        }
    }

    drawElement(level->hero.position.x, level->hero.position.y, re_hero);
    drawMessage(level);
    refresh();
}

void getInput (Level* level)
{
    char input;

    input = getch();

    switch (input)
    {
    case 'w':
        moveHero(level, d_up);
        break;

    case 'a':
        moveHero(level, d_left);
        break;

    case 's':
        moveHero(level, d_down);
        break;

    case 'd':
        moveHero(level, d_right);
        break;
    }
}
