/**
 * @brief Main game reader
 *
 * The main function of this module is read data from files
 *
 * @file reader.c
 * @version 1.0
 * @date 07/02/2019
 * @author Álvaro Rodríguez
 * @copyright GNU Public License
 */

#include "ui.h"
#include "reader.h"
#include "game.h"
#include "space.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFF 500
#define MAX_DATA_SIZE 10

/* parse callback */
typedef STATUS (*parse_cb)( Game *game, char **__data, int size );

void _free_data( char **__data, int size ) {

  int i;

  if ( !__data || size <= 0 )
    return;

  for ( i=0; i<MAX_DATA_SIZE; i++ ) {
    if ( __data[ i ] ) {
      free( __data[ i ] );
      __data[ i ] = NULL;
    }
  }

  free( __data );

}


STATUS _parse_link( Game *game, char **__data, int size ) {

  Link *ln;
  STATUS sts;

  sts = ERROR;

  if ( size == 5 ) {

    ln = link_create( atol( __data[ 0 ] ) );

    link_set_name( ln, __data[ 1 ] );
    link_set_from( ln, atol( __data[ 2 ] ) );
    link_set_to( ln, atol( __data[ 3 ] ) );
    link_set_state( ln, !atoi( __data[ 4 ] ) ? LINK_CLOSED : LINK_OPENED );

    if ( game_add_link( game, ln ) == ERROR ) {
      link_destroy( ln );
      sts = ERROR;
    } else {
      sts = OK;
    }

  }

  return sts;
}

STATUS _parse_space( Game *game, char **__data, int size ) {

  Space *sp;
  STATUS sts;

  sts = ERROR;

  if ( size > 6 ) { /* at least space needs 7 parameters */

    sp = space_create( atol( __data[ 0 ] ) );

    space_set_name( sp, __data[ 1 ] );
    space_set_descrp( sp, __data[ 2 ] );
    space_set_link( sp, N, atol( __data[3] ) );
    space_set_link( sp, E, atol( __data[4] ) );
    space_set_link( sp, S, atol( __data[5] ) );
    space_set_link( sp, W, atol( __data[6] ) );

    if ( size == 8 ) {
      space_set_picture( sp, __data[ 7 ] );
    }

    if ( game_add_space( game, sp ) == ERROR ) {
      space_destroy( sp );
      sts = ERROR;
    } else {
      sts = OK;
    }

  }

  return sts;
}

STATUS _parse_object( Game *game, char **__data, int size ) {

  Id id, loc;
  Object *obj;
  STATUS sts;

  sts = ERROR;

  if ( size == 4 ) {

    id = atol( __data[ 0 ] );
    loc = atol( __data[ 2 ] );

    obj = obj_create( id );
    obj_set_name( obj, __data[ 1 ] );
    space_add_object( game_get_space( game, loc ), id );
    obj_set_descrp( obj, __data[ 3 ] );

    if ( game_add_object( game, obj ) == ERROR ) {
      obj_destroy( obj );
      sts = ERROR;
    } else {
      sts = OK;
    }

  }

  return sts;

}

STATUS _parse(
  Game *game,
  const char *f_name,
  const char *pref,
  parse_cb cb
) {

  FILE *f; /* fiel stream */
  char *tok; /* token */
  char **__data; /* parsed data */
  char __buff[ MAX_BUFF ]; /* line buffer */
  int i,
      line,
      p_len, /* prefix legth */
      t_len; /* token length */

  STATUS sts = OK;

  if ( !game || !f_name || !pref || !cb )
    return ERROR;

  f = fopen( f_name, "r" );

  if ( !f )
    return ERROR;

  line = 0;
  p_len = strlen( pref );

  while ( fgets( __buff, MAX_BUFF, f ) && sts == OK ) {
    line++;
    if ( strncmp( __buff, pref, p_len ) )
      continue;

    __data = (char**) malloc( MAX_DATA_SIZE*sizeof(char*) );

    if ( !__data ) {
      sts = ERROR;
      break;
    }

    for ( i=0; i<MAX_DATA_SIZE; i++ ) {
      __data[ i ] = NULL;
    }

    tok = strtok( __buff+p_len, "|" );

    i=0;
    while ( tok && i < MAX_DATA_SIZE ) {

      t_len = strlen( tok );

      __data[ i ] = (char*) malloc( (t_len+1)*sizeof(char) );
      strcpy( __data[ i ], tok );

      tok = strtok( NULL, "|" );
      i++;
    }

    sts = cb( game, __data, i );

    if ( sts == ERROR ) {
      fprintf( stderr, "\033[1;31merror\033[0m: \033[35mreader\033[0m: parse error at \033[1m%s:%d\033[0m\n", f_name, line );
    }

    _free_data( __data, i );

  }

  fclose( f );

  return sts;

}

STATUS reader_load_links( Game *game, char *f_name ) {
  if ( !game || !f_name )
    return ERROR;
  return _parse( game, f_name, "@l:", (parse_cb)_parse_link );
}

STATUS reader_load_spaces( Game *game, char *f_name ) {
  if ( !game || !f_name )
    return ERROR;
  return _parse( game, f_name, "@s:", (parse_cb)_parse_space );
}


STATUS reader_load_objects( Game *game, char *f_name ) {
  if ( !game || !f_name )
    return ERROR;
  return _parse( game, f_name, "@o:", (parse_cb)_parse_object );
}
