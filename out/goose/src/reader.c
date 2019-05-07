/**
 * @brief Game file reader
 *
 * @file reader.c
 * @author Álvaro Rodríguez & Javier Romera
 * @version 1.0
 * @date 07/02/2019
 * @copyright GNU Public License
 */

#include "reader.h"
#include "game.h"
#include "space.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

STATUS reader_load_spaces( Game *game, char *f_name ) {

  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char del[] = "|"; // line delimeter
  char pref_sp[] = "@s:"; // linre prefix
  Id sp_id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space *space = NULL;
  char *toks = NULL;
  STATUS status = OK;
  char pict[PICTURE_LEN] = "";

  if ( !f_name ) return ERROR;

  file = fopen( f_name , "r");

  if ( !file ) return ERROR;

  while ( fgets(line, WORD_SIZE, file) ) {

    if ( !strncmp( pref_sp, line, 3 ) ) {

      toks = strtok(line + strlen(pref_sp), del); sp_id = atol(toks); // space id
      toks = strtok(NULL, del); strcpy(name, toks); // name
      toks = strtok(NULL, del); north = atol(toks); // north
      toks = strtok(NULL, del); east = atol(toks); // east
      toks = strtok(NULL, del); south = atol(toks); // south
      toks = strtok(NULL, del); west = atol(toks); // west
      toks = strtok(NULL, del); // picture

      // clear the picture
      pict[0] = 0;

      if ( toks ) {
        strcpy( pict, toks );
      }

      // init space
      space = space_create( sp_id );

      if (space != NULL) {

        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        space_set_picture( space, pict );

        if ( game_add_space(game, space) == ERROR ) {
          space_destroy( space );
        }

      }

    }

  }

  if ( ferror( file ) ) {
    status = ERROR;
  }

  fclose( file );

  return status;
}


STATUS reader_load_objects( Game *game, char *f_name ) {

  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char del[] = "|"; // line delimeter
  char pref_obj[] = "@o:"; // object prefix
  Id obj_id = NO_ID;
  Id obj_pos;
  Object *obj = NULL;
  char *toks = NULL;
  STATUS status = OK;

  if ( !f_name ) return ERROR;

  file = fopen( f_name , "r");

  if ( !file ) return ERROR;

  while ( fgets(line, WORD_SIZE, file) ) {

    if ( !strncmp(pref_obj, line, 3) ) {
      toks = strtok(line + strlen(pref_obj), del); obj_id = atol(toks); // object id
      toks = strtok(NULL, del); strcpy(name, toks); // name
      toks = strtok(NULL, del); obj_pos = atol(toks); // default position

      obj = obj_init();

      if (obj != NULL) {
        obj_set_id( obj, obj_id );
        obj_set_name( obj, name );
        if ( game_set_object( game, obj ) == OK ) {
          space_add_object( game_get_space( game, obj_pos ), obj_get_id( obj ) );
        } else {
          obj_destroy( obj );
        }
      }
    }

  }

  if ( ferror( file ) ) {
    status = ERROR;
  }

  fclose( file );

  return status;
}
