/**
 * @brief Object manager
 *
 * @file object.h
 * @version 0.9.1
 * @date 18/03/2019
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "set.h"
#include "types.h"

enum {
  OBJ_NONE=-999,
  OBJ_YES=-1,
  OBJ_NO=-2
};

typedef enum _Obj_attr {
  OBJ_IS_MOVABLE,
  OBJ_IS_MOVED,
  OBJ_IS_HIDDEN,
  OBJ_CAN_ILLUMINATE,
  OBJ_IS_ON,
  OBJ_USED,
  OBJ_MAX_USES
} Obj_attr;

#define MAX_OBJ_DESCRP 100 /*!< @brief Maximum number of characters that can have a description of an object */
#define MAX_OBJ_NAME 50 /*!< @brief Maximum number of characters that can have a name of an object */
#define MAX_OBJECTS 20 /*!< @brief Maximum number of objects */
#define MAX_OBJ_ATTRS 10 /*!< @brief Maximum quantity of object attributes */
#define MAX_OBJ_LINKS /*!< @brief Maximum number of links that an object can open */
#define MAX_OBJ_FILE_NAME 50 /*!< @brief Maximum length for object file names */

/*!
 * @brief Defines the type of object structure
 */
typedef struct _Object Object;


/**
* @brief This fuction initializes an object
* @author Miguel Rodríguez
* @param {Id} - Object identification
* @retval {Object*} - Returns an object's pointer
*/
Object *obj_create( Id id );


/**
* @brief This fuction destroys an object
* @author Miguel Rodríguez
* @param {Object*} obj - object pointer
*/
void obj_destroy( Object *obj );


/**
* @brief This fuction sets an object name
* @author Miguel Rodríguez
* @param {Object*} obj - object pointer
* @param {char*} name - object's name
*/
STATUS obj_set_name( Object *obj, const char *name );

/**
* @brief This fuction gets an object name
* @author Miguel Rodríguez
* @param {Object*} obj - object's pointer
* @retval {char*} - Returns a pointer to the object's name
*/
const char *obj_get_name( Object *obj );


/**
* @brief This fuction sets the description of an object
* @author Miguel Rodríguez
* @param {Object*} obj - object's pointer
* @param {char*} descrp - object's description
*/
STATUS obj_set_descrp( Object *obj, const char *descrp );


/**
* @brief This fuction sets the long description of an object
* @author Miguel Rodríguez
* @param {Object*} obj - object's pointer
* @param {char*} ldescrp - long description of the object
*/
STATUS obj_set_ldescrp( Object *obj, const char *ldescrp );


/**
* @brief This fuction gets the description of an object
* @author Miguel Rodríguez
* @param {Object*} obj - object's pointer
* @retval {char*} - Returns a pointer to the object's name
*/
const char *obj_get_descrp( Object *obj );


/**
* @brief This fuction gets the long description of an object
* @author Miguel Rodríguez
* @param {Object*} obj - object's pointer
* @retval {char*} - Returns the long description of the object
*/
const char *obj_get_ldescrp( Object *obj );


/**
* @brief This fuction sets the object id
* @author Miguel Rodríguez
* @param {Object*} obj - object's pointer
* @param {Id} id - Variable of Id type
*/
STATUS obj_set_id( Object *obj, const Id id );


/**
* @brief This fuction gets the object id
* @author Miguel Rodríguez
* @param {Object*} obj - object's pointer
* @retval {Id} - Returns an id
*/
const Id obj_get_id( Object *obj );


/**
* @brief This fuction open the link state
* @author Miguel Rodríguez
* @param {Object*} obj - object's pointer
* @param {Id} obj - Link's id
* @retval {bool} - Returns TRUE or FALSE
*/
bool obj_opens_link( Object *obj, Id id );


/**
* @brief This fuction gets the links that can open
* @author Miguel Rodríguez
* @param {Object*} obj - object's pointer
* @retval {Set*} - Returns a set pointer
*/
Set* obj_get_links( Object *obj );

/**
* @brief This fuction add the id of a link that the object can open
* @author Miguel Rodríguez
* @param {Object*} obj - object's pointer
* @param {Id} link - Link's id
* @retval {Status} - Returns OK or ERROR
*/
STATUS obj_add_link( Object *obj, Id id );

/**
* @brief This fuction set the attribute of an object
* @author Miguel Rodríguez
* @param {Object*} obj - object's pointer
* @param {long} obj - object's attribute
* @param {long} obj - object's number of attributes
* @retval {Status} - Returns OK or ERROR
*/
STATUS obj_set_attr( Object *obj, Obj_attr attr, long v );

/**
* @brief This fuction get's the attribute of an object
* @author Miguel Rodríguez
* @param {Object*} obj - object's pointer
* @param {long} obj - object's attribute
* @retval {long} - Returns the attribute of an object
*/
long obj_get_attr( Object *obj, Obj_attr attr );


STATUS obj_set_picture_file( Object *obj, const char *f_name );
const char *obj_get_picture_file( Object *obj );

#endif
