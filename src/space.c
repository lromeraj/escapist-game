/**
 * @briefImp Manages the cells player can move to.
 *
 * @file space.c
 * @version 1.0
 * @date 07/02/2019
 * @copyright GNU Public License
 */

#include "str.h"
#include "space.h"
#include "types.h"
#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!< @brief Space structure*/


struct _Space {
  Id id; /*!< @brief Space id */
  Id north; /*!< @brief Space north id */
  Id south; /*!< @brief Space south id */
  Id east; /*!< @brief Space east id */
  Id west; /*!< @brief Space west id */
  Id up; /*!< @brief Space up id */
  Id down; /*!< @brief Space down id */
  bool light; /*!< @brief Light state of the space */
  char name[ MAX_SPACE_NAME ]; /*!< @brief Space name */
  char descrp[ MAX_SPACE_DESCRP ]; /*!< @brief Space description */
  char *ldescrp; /*!< @brief Space long description */
  Set *objects; /*!< @brief Set of objects in the space */
  char picture[ MAX_SPACE_PICTURE ]; /*!< @brief Space picture */
  char picture_file[ MAX_SPACE_FILE_NAME ];  /*!< @brief Name of the file containing picture */
};

Space* space_create( Id id ) {

  Space *sp = NULL;

  if ( id == NO_ID )
    return NULL;

  sp = (Space*) malloc( sizeof( Space ) );

  if ( !sp )
    return NULL;

  sp->id = id; /* set up space identification */
  sp->name[0] = '\0';
  sp->picture[0] = '\0';
  sp->descrp[0] = '\0';
  sp->picture_file[ 0 ] = '\0';
  sp->ldescrp = NULL;
  sp->north = NO_ID;
  sp->south = NO_ID;
  sp->east = NO_ID;
  sp->west = NO_ID;
  sp->up = NO_ID;
  sp->down = NO_ID;
  sp->objects = set_create(); /* build objects set */
  sp->light = false; /* by default the space is dark */

  return sp;
}

STATUS space_destroy( Space *sp ) {

  if ( !sp ) {
    return ERROR;
  }

  str_destroy( sp->ldescrp );
  set_destroy( sp->objects );

  free( sp );

  return OK;
}

STATUS space_set_name( Space *space, char *name ) {

  if ( !space || !name ) {
    return ERROR;
  }

  strncpy( space->name, name, MAX_SPACE_NAME );
  space->name[ MAX_SPACE_NAME - 1 ] = 0;

  return OK;
}


STATUS space_set_picture_file( Space *space, char *f_name ) {

  if ( !space || !f_name ) {
    return ERROR;
  }

  strncpy( space->picture_file, f_name, MAX_SPACE_FILE_NAME );
  space->picture_file[ MAX_SPACE_FILE_NAME - 1 ] = 0;

  return OK;
}

STATUS space_set_descrp( Space *space, const char *descrp ) {

  if ( !space || !descrp )
    return ERROR;

  strncpy( space->descrp, descrp, MAX_SPACE_DESCRP );
  space->descrp[ MAX_SPACE_DESCRP - 1 ] = 0;

  return OK;
}


STATUS space_set_ldescrp( Space *sp, const char *ldescrp ) {

  if ( !sp || !ldescrp )
    return ERROR;

  str_destroy( sp->ldescrp );
  sp->ldescrp = str_clone( ldescrp );

  return OK;
}

const char *space_get_descrp( Space *space ) {
  if ( !space )
    return NULL;
  return space->descrp;
}

const char *space_get_ldescrp( Space *space ) {
  if ( !space )
    return NULL;
  return space->ldescrp;
}

const char *space_get_picture_file( Space *space ) {
  if ( !space )
    return NULL;
  return space->picture_file;
}

Set *space_get_objects( Space *space ) {
  if ( !space )
    return NULL;

  return space->objects;
}

Id space_get_link( Space *sp, CardinalPoint cp ) {


  Id ln_id;

  if ( !sp )
    return NO_ID;

  switch ( cp ) {

    case N:
      ln_id = sp->north;
      break;

    case E:
      ln_id = sp->east;
      break;

    case S:
      ln_id = sp->south;
      break;

    case W:
      ln_id = sp->west;
      break;

    case U:
      ln_id = sp->up;
      break;

    case D:
      ln_id = sp->down;
      break;

    default:
      return NO_ID;

  }

  return ln_id;


}

STATUS space_set_link( Space *sp, CardinalPoint cp, Id id ) {

  if ( !sp )
    return ERROR;

  switch ( cp ) {

    case N:
      sp->north = id;
      break;

    case E:
      sp->east = id;
      break;

    case S:
      sp->south = id;
      break;

    case W:
      sp->west = id;
      break;

    case U:
      sp->up = id;
      break;

    case D:
      sp->down = id;
      break;

    default:
      return ERROR;

  }

  return OK;
}

STATUS space_del_object( Space *space, Id id ) {
  if ( !space )
    return ERROR;
  return set_del_id( space->objects, id );
}

bool space_has_object( Space *space, Id id ) {

  if ( !space )
    return false;

  return set_has_id( space->objects, id );
}

STATUS space_add_object( Space *space, Id id ) {

  if ( !space )
    return ERROR;

  return set_add_id( space->objects, id );
}

const char *space_get_name(Space *space) {
  if ( !space )
    return NULL;

  return space->name;
}

Id space_get_id( Space *space ) {

  if ( !space )
    return NO_ID;

  return space->id;
}

Id space_get_object( Space *space, Id id ) {

  if ( !space ) {
    return NO_ID;
  }

  if ( id == NO_ID ) {
    return set_get_first( space->objects );
  }

  return set_has_id(space->objects, id ) ? id : NO_ID;
}

STATUS space_set_picture( Space *space, char *pict ){

  if ( !space || !pict )
    return ERROR;

  strncpy( space->picture, pict, MAX_SPACE_PICTURE );
  space->picture[ MAX_SPACE_PICTURE - 1 ] = 0;

  return OK;
}

char* space_get_picture( Space *space ) {

  if ( !space ) {
    return NULL;
  }

  return space->picture;
}

STATUS space_set_light( Space *space, bool l ){

  if ( !space )
    return ERROR;

  space->light = l;

  return OK;
}

STATUS space_toggle_light( Space *space ) {

  if ( !space )
    return ERROR;

  space->light = !space->light;

  return OK;
}

bool space_get_light( Space *space ) {

  if ( !space )
    return false;

  return space->light;
}

int space_print( Space* space ) {

  int bytes = 0;
  if ( !space )
    return 0;

  bytes+=fprintf(stdout, "--> Space {id: %ld; name: %s}\n", space->id, space->name);
  bytes+=fprintf(stdout, "---> North link: %ld.\n", space->north );
  bytes+=fprintf(stdout, "---> South link: %ld.\n", space->south );
  bytes+=fprintf(stdout, "---> East link: %ld.\n", space->east );
  bytes+=fprintf(stdout, "---> West link: %ld.\n", space->west );
  bytes+=fprintf(stdout, "---> Up link: %ld.\n", space->up );
  bytes+=fprintf(stdout, "---> Down link: %ld.\n", space->down );
  bytes+=fprintf(stdout, "---> Light is %s\n", space->light ? "on" : "off" );

  return OK;
}
