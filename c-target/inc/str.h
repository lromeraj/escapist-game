#ifndef STR_H
#define STR_H

#include <stdio.h>
#include <stdlib.h>


char* str_alloc( unsigned long len );
char* str_clone( const char *str );
void str_sdestroy( char **str );
void str_destroy( char *str );
int str_print( FILE *stream, const char *str );

#endif
