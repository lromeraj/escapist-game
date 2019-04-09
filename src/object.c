/**
 * @brief Manages the game objects.
 *
 * @file object.c
 * @author Miguel Rodríguez
 * @version 1.0
 * @date 18/03/2019
 */

#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*!
* @brief Main object structure
*
* This structure defines an object whose fields are an id and a name
*/
struct _Object {
  Id id; /*!< Identifier */
  char name[ MAX_OBJ_NAME ]; /*!< Object's name */
  char descrp[ MAX_OBJ_DESCRP ]; /*!< Object's description */
};

Object *obj_create( Id id ) {

  Object *obj;

  if ( id == NO_ID )
    return NULL;

  obj = (Object*) malloc( sizeof( Object ) );

  if ( !obj )
    return NULL;

  obj->id = id;
  obj->name[0] = '\0';
  obj->descrp[0] = '\0';

  return obj;
}

void obj_destroy( Object *obj ) {

  if ( !obj )
    return;

  free( obj );

}


STATUS obj_set_name( Object *obj, const char *name ) {

  if ( !obj || !name )
    return ERROR;

  strncpy( obj->name, name, MAX_OBJ_NAME );
  obj->name[ MAX_OBJ_NAME - 1 ] = 0;

  return OK;
}

const char *obj_get_name( Object *obj ) {
  if ( !obj )
    return NULL;
  return obj->name;
}

STATUS obj_set_descrp( Object *obj, const char *descrp ) {

  if ( !obj || !descrp )
    return ERROR;

  strncpy( obj->descrp, descrp, MAX_OBJ_DESCRP );
  obj->descrp[ MAX_OBJ_DESCRP - 1 ] = 0;

  return OK;
}

const char *obj_get_descrp( Object *obj ) {
  if ( !obj )
    return NULL;
  return obj->descrp;
}

STATUS obj_set_id( Object *obj, const Id id ) {

  if ( !obj || id == NO_ID )
    return ERROR;

  obj->id = id;

  return OK;

}

const Id obj_get_id( Object *obj ) {
  if ( !obj )
    return NO_ID;
  return obj->id;
}
