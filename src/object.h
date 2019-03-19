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

#define OBJ_MAX_NAME_LEN 50 /*!< @brief Maximum number of characters that can have a name of an object */
#define MAX_OBJECTS 4 /*!< @brief Maximum number of objects */

/*!
 * @brief Defines the type of object structure
 */
typedef struct _Object Object;

/**
* @brief This fuction initializes an object
* @author Miguel Rodríguez
* @retval {Object*} - Returns an object's pointer
*/
Object *obj_init();

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
void obj_set_name( Object *obj, const char *name );

/**
* @brief This fuction gets an object name
* @author Miguel Rodríguez
* @param {Object*} obj - object's pointer
* @retval {char*} - Returns a pointer to the object's name
*/
const char *obj_get_name( Object *obj );

/**
* @brief This fuction sets the object id
* @author Miguel Rodríguez
* @param {Object*} obj - object's pointer
* @param {Id} id - Variable of Id type
*/
void obj_set_id( Object *obj, const Id id );

/**
* @brief This fuction gets the object id
* @author Miguel Rodríguez
* @param {Object*} obj - object's pointer
* @retval {Id} - Returns an id
*/
const Id obj_get_id( Object *obj );

#endif
