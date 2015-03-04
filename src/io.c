/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-02 15:37:58
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-04 14:40:25
*/

#include "io.h"

void readFile (char* filename)
{
	FILE* file;
	char buffer[IO_BUFFER_SIZE];

	file = fopen(filename, "r");

	while (fgets(buffer, IO_BUFFER_SIZE-1, file) != NULL)
	{

	}

}

