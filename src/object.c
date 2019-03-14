/**
 * @brief Manages the game objects.
 *
 * @file object.c
 * @author Álvaro Rodríguez & Javier Romera
 * @version 1.0
 * @date 07/02/2019
 * @copyright GNU Public License
 */

#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Object {
  Id id;
  char name[ OBJ_MAX_NAME_LEN ];
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
  if ( !obj ) return;
  strcpy( obj->name, name );
}

const char *obj_get_name( Object *obj ) {
  if ( !obj )
    return NULL;
  return obj->name;
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
