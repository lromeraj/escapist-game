/**
 * @brief Defines objects.
 *
 * @file object.h
 * @author Álvaro Rodríguez & Javier Romera
 * @version 1.0
 * @date 07/02/2019
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

/* Defines the maximum name of all objects as 50 characters, the Id of the first object as 1 and the maximum number of objects as 100 (as the maxumum player number). */

#define OBJ_MAX_NAME_LEN 50
#define FIRST_OBJECT 1
#define MAX_OBJECTS 4

#include "types.h"

typedef struct _Object Object;

/* Initializes an object
* @return {Object*} - returns a pointer
* to the new allocated object
*/
Object *obj_init();

/* - - - - - - - - - - - - - - - - - - - - - - */

/* Sets an object location, unused as it's implemented in space module.
* @return {STATUS*} - returns a state;
* @param {Object*} - obj; {Id} - id;
*/

//STATUS obj_set_location(Object *obj, Id id);

/* Gets an object location, unused as it's implemented in space module.
* @return {STATUS*} - returns a state;
* @param {Object*} - obj; {Id} - id;
*/

//Id obj_get_location(Object *obj);

/* - - - - - - - - - - - - - - - - - - - - - - */

/* Destroys an object
* @param {Object*} - object to be freed
*/

void obj_destroy( Object *obj );

/* Sets a name to an object
* @param {Object*} - object to be updated
* @param {const char*} name - new name
*/
void obj_set_name( Object *obj, const char *name );

/* Gets the name of given object
* @param {Object*} - object to request name
* @return {const char*} - returns the requested object's name
*/
const char *obj_get_name( Object *obj );

/* Sets an id to an object
* @param {Object*} - object to be updated
* @param {const char*} name - new name
*/
void obj_set_id( Object *obj, const Id id );

/* Gets the id of given object
* @param {Object*} - object to request id
* @return {const Id*} - returns the requested object's id
*/
const Id obj_get_id( Object *obj );

#endif
