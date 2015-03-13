/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-02-10 01:55:56
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-05 00:42:49
*/

#ifndef _ELUCENAP_PARSERH
#define _ELUCENAP_PARSERH

/**
 ParseLine: Tokenize the items on $command, and stores the number of tokens in $argc
 Pre: Pass the parameters
 Post: Returns an array of strings (char**) with the tokens, and stores the number of tokens on $argc
*/
char** parseLine (char* command, int *argc);

#endif // _ELUCENAP_PARSERH
