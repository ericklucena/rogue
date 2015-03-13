/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-01-26 01:40:01
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-05 00:37:31
*/

#ifndef _ELUCENAP_UTILH
#define _ELUCENAP_UTILH

#include <stdbool.h>

/**
 IsEqual: Checks if $stringA is equal to $stringB
 Pre: Pass the parameters
 Post: Returns true if equal, false otherwise
*/
bool isEqual (char* stringA, char* stringB);

/**
 NewString: Allocates memory for a new string with the selected ax $length
 Pre: Pass the parameter
 Post: Returns a string (pointer to char) if successful, NULL otherwise
*/
char* newString (int lenght);

/**
 CopyString: Creates a copy of a given $string
 Pre: Pass the parameter
 Post: Returns a pointer to the copy string if successful, NULL otherwise
*/
char* copyString (char* string);

/**
 NewArgs: Allocates an array of strings with $argc positions
 Pre: Pass the parameter
 Post: Returns the pointer to an array of structs if successful, NULL otherwise
*/
char** newArgs (int argc);

/**
 ExpandArgs: Increases the size of $args to $argc+1
 Pre: Pass the parameters
 Post: Returns the new pointer value of args if successfull, NULL otherwise
*/
char** expandArgs (char** args, int argc);

/**
 FreeArgs: Frees the memory occupied by $args, using $argc as control
 Pre: Pass the parameters
 Post: The memory occupied by args is freed
*/
void freeArgs (char** args, int argc);

#endif  // _ELUCENAP_UTILH
