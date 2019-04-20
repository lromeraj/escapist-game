/**
 * @briefImp Manages the cells player can move to.
 *
 * @file space.c
 * @version 1.0
 * @date 07/02/2019
 * @copyright GNU Public License
 */

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
  Set *objects; /*!< @brief Set of objects in the space */
  char picture[ MAX_SPACE_PICTURE ]; /*!< @brief Space picture */
};

Space* space_create( Id id ) {

  Space *newSpace = NULL;

  if ( id == NO_ID )
    return NULL;

  newSpace = (Space*) malloc(sizeof(Space));

  if ( !newSpace )
    return NULL;

  newSpace->id = id; /* set up space identification */
  newSpace->name[0] = '\0';
  newSpace->picture[0] = '\0';
  newSpace->descrp[0] = '\0';
  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  newSpace->up = NO_ID;
  newSpace->down = NO_ID;
  newSpace->objects = set_create(); /* build objects set */
  newSpace->light = false; /* by default the space is dark */

  return newSpace;
}

STATUS space_destroy( Space *space ) {

  if ( !space ) {
    return ERROR;
  }

  set_destroy( space->objects );

  free( space );

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

STATUS space_set_descrp( Space *space, const char *descrp ) {

  if ( !space || !descrp )
    return ERROR;

  strncpy( space->descrp, descrp, MAX_SPACE_DESCRP );
  space->descrp[ MAX_SPACE_DESCRP - 1 ] = 0;

  return OK;
}

const char *space_get_descrp( Space *space ) {
  if ( !space )
    return NULL;
  return space->descrp;
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
