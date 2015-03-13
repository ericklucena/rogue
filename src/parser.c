/************************************parser.c***********************************************
Student Name: Erick Lucena Palmeira Silva    Student Number:  0905100-
Date: 02/12/2015                             Course Name: cis2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
********************************************************************************************/

/* 
* CIS 2500 A2 Parser functions implementation
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-02-10 02:01:31
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-12 16:02:29
* This file contains the implementation of the functions used for parsing the user's inputs
*/

#include "parser.h"
#include "util.h"
#include <string.h>

char** parseLine (char* command, int *argc)
{
    int i;
    char *aux;
    char *arg;
    char **args;

    args = newArgs(1);
    aux = strtok(command, " ");
    
    for (i=0; aux != NULL;)
    {
        arg = copyString(aux);
        args[i++] = arg;
        args = expandArgs(args, i+1);
        aux = strtok(NULL, " ");
    }
    
    *argc = i;

    return args;
}
