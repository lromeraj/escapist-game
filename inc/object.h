/**
 * @brief Object manager
 *
 * @file object.h
 * @version 0.9.1
 * @date 18/03/2019
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

#define MAX_OBJ_DESCRP 100 /*!< @brief Maximum number of characters that can have a description of an object */
#define MAX_OBJ_NAME 50 /*!< @brief Maximum number of characters that can have a name of an object */
#define MAX_OBJECTS 4 /*!< @brief Maximum number of objects */

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
* @param {char*} name - object's description
*/
STATUS obj_set_descrp( Object *obj, const char *descrp );


/**
* @brief This fuction gets the description of an object
* @author Miguel Rodríguez
* @param {Object*} obj - object's pointer
* @retval {char*} - Returns a pointer to the object's name
*/
const char *obj_get_descrp( Object *obj );


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

#endif
