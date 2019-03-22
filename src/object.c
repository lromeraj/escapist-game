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

Object *obj_init() {

  Object *obj = (Object*) malloc( sizeof( Object ) );

  if ( obj ) {
    obj->id = NO_ID;
    obj->name[0] = '\0';
  }

  return obj;

}

void obj_destroy( Object *obj ) {
  if ( !obj ) return;
  free( obj );
}


void obj_set_name( Object *obj, const char *name ) {
  if ( !obj )
    return;
  strcpy( obj->name, name );
}

const char *obj_get_name( Object *obj ) {
  if ( !obj )
    return NULL;
  return obj->name;
}

void obj_set_descrp( Object *obj, const char *descrp ) {
  if ( !obj )
    return;
  strcpy( obj->descrp, descrp );
}

const char *obj_get_descrp( Object *obj ) {
  if ( !obj )
    return NULL;
  return obj->descrp;
}

void obj_set_id( Object *obj, const Id id ) {
  if ( !obj ) return;
  obj->id = id;
}


const Id obj_get_id( Object *obj ) {
  if ( !obj )
    return NO_ID;
  return obj->id;
}
