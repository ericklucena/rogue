/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-02 14:52:32
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-12 22:16:29
*/

#include "graphics.h"
#include "rogue.h"
#include "io.h"

int main(int argc, char** argv) {

    Level* level;

    level = readFile(argv[1]);

    initLevel(level);
    initGraphics();

    while (1)
    {
        drawLevel(level);
        getInput(level);
    }

    endGraphics();

    return 0;
}
