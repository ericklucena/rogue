/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-02 15:06:34
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-13 20:54:43
*/

#ifndef _ELUCENAP_IOH
#define _ELUCENAP_IOH

#include <stdio.h>
#include "rogue.h"

#define IO_BUFFER_SIZE 151

/**
 ReadFile: Reads $filename and returns a Level with the read values
 Pre: Pass the parameter
 Post: Returns a pointer to Level 
*/
Level* readFile (char* filename);

#endif // _ELUCENAP_IOH
