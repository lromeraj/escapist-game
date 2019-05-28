#ifndef STR_H
#define STR_H

#include <stdio.h>
#include <stdlib.h>

/**
* @brief creates a str
* @author Gonzalo Serrano
* @param  len - unsigned long
* @retval - Returns a char pointer
*/
char* str_alloc( unsigned long len );

/**
* @brief clones a str
* @author Gonzalo Serrano
* @param  str - const char pointer
* @retval - Returns a char pointer
*/
char* str_clone( const char *str );

/**
* @brief destrois a str
* @author Gonzalo Serrano
* @param  str - char pointer pointer
*/
void str_sdestroy( char **str );

/**
* @brief destrois a str
* @author Gonzalo Serrano
* @param  str - char pointer
*/
void str_destroy( char *str );

/**
* @brief print a str
* @author Gonzalo Serrano
* @param  stream - FILE to print
* @param  str - const char pointer
* @retval - Returns the number of characters printed
*/
int str_print( FILE *stream, const char *str );

/**
* @brief read a str
* @author Gonzalo Serrano
* @param  str - const char pointer
* @param  strl - char pointer
* @param  del - const char pointer
* @retval - Returns a integer
*/
int strcmptok( const char *str, char *strl, const char *del );

#endif
