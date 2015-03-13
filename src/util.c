/************************************util.c*************************************************
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
* CIS 2500 A3 Util functions implementation
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-01-26 01:42:25
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-13 01:38:55
* This file contains the implementation of the functions used by the libraries
*/


#include "util.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

bool isEqual (char* stringA, char* stringB)
{
    return strcmp(stringA, stringB) == 0;
}

char* newString (int lenght)
{
    char *string;

    string = malloc (sizeof(char)*lenght+1);
    if (string != NULL)
    {
        string[0]= '\0';
    }

    return string;
}

char* copyString (char* string)
{
    char* newStr;

    newStr = newString(strlen(string));

    if (newStr != NULL)
    {
        strcpy(newStr, string);
    }

    return newStr;
}


char** newArgs (int argc)
{
    char ** args;

    args = calloc (sizeof(char*), argc);

    return args;
}

char** expandArgs (char** args, int argc)
{
    char** newArgs;

    newArgs = realloc (args, sizeof(char*)*argc);

    return newArgs;
}

void freeArgs (char **args, int argc)
{
    int i;

    for (i=0; i<argc; i++)
    {
        free(args[i]);
    }

    free(args);
}
