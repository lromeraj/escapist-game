#include "str.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* str_alloc( unsigned long len ) {

  char *_str;

  if ( !len )
    return NULL;

  _str = (char*) calloc( len+1, sizeof( char ) );

  return _str;

}

char* str_clone( const char *str ) {

  char *_clone;
  unsigned long len;

  if ( !str )
    return NULL;

  len = strlen( str );
  _clone = str_alloc( len );

  if ( !_clone )
    return NULL;

  memcpy( _clone, str, len );

  return _clone;
}

void str_destroy( char *str ) {

  if ( !str )
    return;

  free( str );

}

void str_sdestroy( char **str ) {

  if ( !str || !(*str) )
    return;

  free( *str );

  *str = NULL;

}

int str_print( FILE *stream, const char *str ) {
  int bytes = 0;
  bytes+=fprintf( stream, "'\033[1m%s\033[0m' ", str );
  return bytes;
}

int strcmptok(
  const char *str,
  char *strl,
  const char *del
) {

  char *tok;
  char _buff[ 1024 ];

  if ( !str || !strl || !del )
    return 1;

  strncpy( _buff, strl, sizeof( _buff ) );
  _buff[ sizeof( _buff ) - 1 ] = 0;

  tok = strtok( _buff, del );

  while ( tok ) {

    if ( !strcmp( tok, str ) )
      return 0;
    tok = strtok( NULL, del );

  }

  return 1;
}
