/**
 * @brief It defines the set interface
 *
 * @file set.h
 * @version 0.3.2
 * @date 19/03/2019
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H

#include <stdio.h>
#include "types.h"

#define MAX_SET 5 /*!< @brief Maximum number of sets */

/*!
* @brief Definition of Set structure
*/
typedef struct _Set Set;

/**
* @brief Initializates a set of objets
* @author Álvaro Rodríguez
* @retval Returns a pointer towards a new set
*/

Set* set_create();

/**
* @brief Destroys a set
* @author Álvaro Rodríguez
* @param {Set*} - Receives a set which is going to be freed
*/

void set_destroy( Set *set);

/**
* @brief Adds a new id to a set
* @author Álvaro Rodríguez
* @param {Set*} - Receives a set which is going to be freed
* @retval {STATUS} - Returns ok or error
*/

STATUS set_add_id( Set *set, Id id);

/**
* @brief Deletes an id from a set
* @author Álvaro Rodríguez
* @param {Set*} - Receives a set which is going to be freed
* @retval {STATUS} - Returns ok or error
*/

STATUS set_del_id( Set *set, Id id);

/**
* @brief Tells if an id is in a set or not
* @author Álvaro Rodríguez
* @param {Set*} - Receives a set which is going to be freed
* @retval {bool} - Returns a boolean value
*/

bool set_has_id( Set *set, Id id );

/**
* @brief Tells the number of id's in a set
* @author Álvaro Rodríguez
* @param {Set*} - Receives a set which is going to be freed
* @retval {int} - Returns an integer
*/

int set_get_total( Set *set);

/**
* @brief Tells if a set is full or not
* @author Álvaro Rodríguez
* @param {Set*} - Receives a set which is going to be freed
* @retval {bool} - Returns a boolean value
*/

bool set_is_full( Set *set);

/**
* @brief Tells if a set is empty or not
* @author Álvaro Rodríguez
* @param {Set*} - Receives a set which is going to be freed
* @retval {bool} - Returns ok or error
*/

bool set_is_empty( Set *set);

/**
* @brief Gets the first Id of a set, just for testing
* @author Javier Romera
* @param {Set*} - Receives a set
* @retval {Id} - Returns a Id
*/

Id set_get_first( Set *set );

/**
* @brief Prints a set
* @author Álvaro Rodríguez
* @param {Set*} - Receives a set which is going to be freed
* @retval {int} - Returns an integer which contains the number of bytes
*/

int set_print( FILE *stream, Set *set);

#endif
