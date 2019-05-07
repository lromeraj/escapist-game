/**
 * @brief Manages the game objects.
 *
 * @file object.c
 * @author Miguel Rodríguez
 * @version 1.0
 * @date 18/03/2019
 */

#include "str.h"
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
  char *ldescrp; /*!< Long description of the object */
  char name[ MAX_OBJ_NAME ]; /*!< Object's name */
  char descrp[ MAX_OBJ_DESCRP ]; /*!< Object's description */
  long attr[ MAX_OBJ_ATTRS ]; /*!< Object attributes */
  char picture_file[ MAX_OBJ_FILE_NAME ]; /*!< Object's picture file name */
  Set *links; /*!< Links that the object can open */
};

Object *obj_create( Id id ) {

  int i;
  Object *obj;

  if ( id == NO_ID )
    return NULL;

  obj = (Object*) malloc( sizeof( Object ) );

  if ( !obj )
    return NULL;

  obj->id = id;
  obj->name[0] = '\0';
  obj->descrp[0] = '\0';
  obj->picture_file[ 0 ] = '\0';
  obj->ldescrp = NULL;

  for ( i=0; i < MAX_OBJ_ATTRS; i++ ) {
    obj->attr[ i ] = OBJ_NONE;
  }

  obj->attr[ OBJ_CAN_ILLUMINATE ] = OBJ_NO;
  obj->attr[ OBJ_IS_HIDDEN ] = OBJ_YES;
  obj->attr[ OBJ_IS_MOVABLE ] = OBJ_NO;
  obj->attr[ OBJ_IS_MOVED ] = OBJ_NO;
  obj->attr[ OBJ_IS_ON ] = OBJ_NO;
  obj->attr[ OBJ_USED ] = 0;
  obj->attr[ OBJ_MAX_USES ] = 0;

  obj->links = set_create();

  return obj;
}

bool obj_opens_link( Object *obj, Id id ) {
  if ( !obj || id == NO_ID )
    return false;
  return set_has_id( obj->links, id );
}

Set* obj_get_links( Object *obj ) {
  if ( !obj )
    return NULL;
  return obj->links;
}

STATUS obj_add_link( Object *obj, Id id ) {

  if ( !obj || id == NO_ID )
    return ERROR;

  return set_add_id( obj->links, id );
}


void obj_destroy( Object *obj ) {

  if ( !obj )
    return;

  str_destroy( obj->ldescrp ); /* free long description */
  set_destroy( obj->links ); /* destroy set of links */

  free( obj );

}

STATUS obj_set_ldescrp( Object *obj, const char *ldescrp ) {

  if ( !obj || !ldescrp )
    return ERROR;

  str_destroy( obj->ldescrp );
  obj->ldescrp = str_clone( ldescrp );

  return OK;
}

STATUS obj_set_name( Object *obj, const char *name ) {

  if ( !obj || !name )
    return ERROR;

  strncpy( obj->name, name, MAX_OBJ_NAME );
  obj->name[ MAX_OBJ_NAME - 1 ] = 0;

  return OK;
}

STATUS obj_set_picture_file( Object *obj, const char *f_name ) {

  if ( !obj || !f_name )
    return ERROR;

  strncpy( obj->picture_file, f_name, MAX_OBJ_FILE_NAME );
  obj->picture_file[ MAX_OBJ_FILE_NAME - 1 ] = 0;

  return OK;
}

const char *obj_get_name( Object *obj ) {
  if ( !obj )
    return NULL;
  return obj->name;
}

const char *obj_get_picture_file( Object *obj ) {
  if ( !obj )
    return NULL;
  return obj->picture_file;
}

STATUS obj_set_descrp( Object *obj, const char *descrp ) {

  if ( !obj || !descrp )
    return ERROR;

  strncpy( obj->descrp, descrp, MAX_OBJ_DESCRP );
  obj->descrp[ MAX_OBJ_DESCRP - 1 ] = 0;

  return OK;
}

STATUS obj_set_attr( Object *obj, Obj_attr attr, long v ) {

  if ( !obj || attr < 0 || attr >= MAX_OBJ_ATTRS )
    return ERROR;

  obj->attr[ attr ] = v;

  return OK;
}

const char *obj_get_descrp( Object *obj ) {
  if ( !obj )
    return NULL;
  return obj->descrp;
}

const char *obj_get_ldescrp( Object *obj ) {
  if ( !obj )
    return NULL;
  return obj->ldescrp;
}


long obj_get_attr( Object *obj, Obj_attr attr ) {

  if ( !obj || attr < 0 || attr >= MAX_OBJ_ATTRS )
    return -1;

  return obj->attr[ attr ];
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
