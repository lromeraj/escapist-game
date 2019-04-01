/**
 * @brief link functions
 *
 * @file link.c
 * @version 0.0.3
 * @date 19/03/2019
 * @author Gonzalo Serrano
 * @copyright GNU Public License
 */

#include "link.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct _Link {
  Id id; /*!< Id of the link */
  char name[ MAX_LINK_NAME ]; /*!< Name of the link */
  Id from; /*!< Id sucessor of the link */
  Id to; /*!< Id destination of the link */
  LinkState state; /*!< State of the link OPEN or CLOSE */
};

Link* link_create( Id id ) {

  Link *link;

  link = (Link*) malloc( sizeof( Link ) );

  if ( !link )
    return NULL;

  link->id = id;
  link->name[0] = '\0';
  link->from = NO_ID;
  link->to = NO_ID;
  link->state = LINK_OPENED;

  return link;
}

STATUS link_destroy( Link *link ) {

  if( !link )
    return ERROR;

  free( link );

  return OK;
}

Id link_get_id( Link *link ) {

  if ( !link )
    return NO_ID;

  return link->id;
}

Id link_get_from( Link *link ) {

  if ( !link )
    return NO_ID;

  return link->from;
}

Id link_get_to( Link *link ) {

  if ( !link )
    return NO_ID;

  return link->to;
}

const char* link_get_name( Link *link ) {

  if ( !link )
    return NULL;

  return link->name;
}

LinkState link_get_state( Link *link ) {

  if ( !link )
    return LINK_CLOSED;

  return link->state;
}

STATUS link_set_state( Link *link, LinkState state ) {

  if( !link )
    return ERROR;

  link->state = state;

  return OK;
}

STATUS link_set_id( Link *link, Id id ) {

  if( !link )
    return ERROR;

  link->id = id;

  return OK;
}

STATUS link_set_from(Link *link, Id id ){

  if( !link )
    return ERROR;

  link->from = id;

  return OK;
}

STATUS link_set_to( Link *link, Id id ) {

  if ( !link )
    return ERROR;

  link->to = id;

  return OK;
}

STATUS link_set_name(Link *link, const char* name){

  if( !link )
    return ERROR;

  strncpy( link->name, name, MAX_LINK_NAME );

  return OK;
}

STATUS link_print( FILE *stream, Link *link ) {

  if ( !link )
    return ERROR;

  fprintf(stream, "--->Id del link: %ld\n", link->id);
  fprintf(stream, "--->Id del link from: %ld\n", link->from);
  fprintf(stream, "--->Id del link to: %ld\n", link->to);
  fprintf(stream, "--->Nombre del link: %s\n", link->name);
  fprintf(stream, "--->Estado del link: %d\n", link->state);

  return OK;
}
