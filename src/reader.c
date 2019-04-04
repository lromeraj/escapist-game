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


#include "reader.h"
#include "game.h"
#include "space.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


STATUS reader_load_links( Game *game, char *f_name ) {

  int plen; /* prefix length */
  FILE *file = NULL;
  char del[] = "|"; /* delimeter */
  char lnp[] = "@l:"; /* link prefix */
  Link *ln = NULL; /* link pointer */
  char *toks = NULL; /* string token */
  STATUS sts = OK; /* process status */
  char line[WORD_SIZE] = "";
  char ln_name[ MAX_LINK_NAME ] = ""; /* link name */
  Id  ln_id = NO_ID, /* link id */
      ln_from = NO_ID, /* link origin */
      ln_to = NO_ID; /* link destination */
  LinkState ln_state; /* link state */

  if ( !f_name ) return ERROR;

  file = fopen( f_name , "r");

  if ( !file ) return ERROR;


  plen = strlen( lnp );

  while ( fgets(line, WORD_SIZE, file) ) {

    if ( !strncmp( lnp, line, plen ) ) {
      toks = strtok( line + plen, del); ln_id = atol( toks );
      toks = strtok(NULL, del); strncpy( ln_name, toks, MAX_LINK_NAME );
      toks = strtok(NULL, del); ln_from = atol(toks);
      toks = strtok(NULL, del); ln_to = atol(toks);
      toks = strtok(NULL, del); ln_state = !atoi(toks) ? LINK_CLOSED : LINK_OPENED;

      ln = link_create( ln_id );

      if ( ln ) {

        link_set_name( ln, ln_name );
        link_set_from( ln, ln_from );
        link_set_to( ln, ln_to );
        link_set_state( ln, ln_state );

        if ( game_add_link( game, ln ) == ERROR ) {
          link_destroy( ln );
        }

      }

    }

  }

  if ( ferror( file ) ) {
    sts = ERROR;
  }

  fclose( file );

  return sts;
}

STATUS reader_load_spaces( Game *game, char *f_name ) {

  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[ MAX_SPACE_NAME ] = "";
  char descrp[ MAX_SPACE_DESCRP ] = "";
  char del[] = "|";
  char pref_sp[] = "@s:";
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

      toks = strtok(line + strlen(pref_sp), del); sp_id = atol(toks);
      toks = strtok(NULL, del); strncpy(name, toks, MAX_SPACE_NAME );
      toks = strtok(NULL, del); strncpy(descrp, toks, MAX_SPACE_DESCRP );
      toks = strtok(NULL, del); north = atol(toks);
      toks = strtok(NULL, del); east = atol(toks);
      toks = strtok(NULL, del); south = atol(toks);
      toks = strtok(NULL, del); west = atol(toks);
      toks = strtok(NULL, del);

      /* clear the picture */
      pict[0] = 0;

      if ( toks ) {
        strcpy( pict, toks );
      }

      /* init space */
      space = space_create( sp_id );

      if (space != NULL) {

        space_set_name( space, name );
        space_set_descrp( space, descrp );
        space_set_link( space, N, north );
        space_set_link( space, E, east );
        space_set_link( space, S, south );
        space_set_link( space, W, west );
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
  char line[ WORD_SIZE ] = "";
  char name[ MAX_OBJ_NAME ] = "";
  char descrp[ MAX_OBJ_DESCRP ] = "";
  char del[] = "|";
  char pref_obj[] = "@o:";
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
      toks = strtok(line + strlen(pref_obj), del); obj_id = atol( toks );
      toks = strtok(NULL, del); strncpy( name, toks, MAX_OBJ_NAME );
      toks = strtok(NULL, del); obj_pos = atol( toks );
      toks = strtok(NULL, del); strncpy( descrp, toks, MAX_OBJ_DESCRP );

      obj = obj_create( obj_id );

      if (obj != NULL) {

        obj_set_name( obj, name );
        obj_set_descrp( obj, descrp );

        if ( game_add_object( game, obj ) == OK ) {
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
