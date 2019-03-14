/**
 * @brief Space module
 *
 * @file space.h
 * @author Javier Romera
 * @version 1.0
 * @date 14/03/2019
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"

#define MAX_SPACES 200
#define FIRST_SPACE 1
#define PICTURE_LEN 100

typedef struct _Space Space;

/**
* @brief creates a new sapce
*
* @author Javier Romera
* @param {Id} - id;
* @return {Space} - returns an space pointer;
*/
Space* space_create(Id id);

/**
* @name space_destroy
* @brief sets to null a space area.
*
* @author Javier Romera
* @version 2.0
* @date 07/02/2019
* @param {Space*} - space;
* @return {STATUS} - Returns a state;
*/

STATUS space_destroy(Space* space);

/**

* @brief takes the id of a space.
*
* @author Javier Romera
* @version 2.0
* @date 07/02/2019
* @param {Space*} - space;
* @return {Id} - Returns an id;
*/

Id space_get_id(Space* space);

/**

* @brief defines the name of a space.
*
* @author Javier Romera
* @version 2.0
* @date 07/02/2019
* @param {Space*} - space; {Char*} - name;
* @return {STATUS} - Returns an state;
*/

STATUS space_set_name(Space* space, char* name);

/**
*
* @brief takes the name of a space.
*
* @author Javier Romera
* @version 2.0
* @date 07/02/2019
* @param {Space*} - space;
* @return {const char*} - Returns a constant character array;
*/

const char* space_get_name(Space* space);

/**
* @brief sets the id of a space to north.
*
* @author Javier Romera
* @param {Space*} - space; {Id} - id;
* @return {STATUS} - Returns an state;
*/

STATUS space_set_north(Space* space, Id id);

/**
* @brief gets a pointer towards north.
*
* @author Javier Romera
* @param {Space*} - space;
* @return {STATUS} - Returns an state;
*/

Id space_get_north(Space* space);

/**
* @brief sets the id of a space to south.
*
* @author Javier Romera
* @param {Space*} - space; {Id} - id;
* @return {STATUS} - Returns an state;
*/

STATUS space_set_south(Space* space, Id id);

/**
* @brief gets a pointer towards south.
*
* @author Javier Romera
* @param {Space*} - space;
* @return {STATUS} - Returns an state;
*/

Id space_get_south(Space* space);

/**
* @brief sets the id of a space to east.
*
* @author Javier Romera
* @param {Space*} - space; {Id} - id;
* @return {STATUS} - Returns an state;
*/

STATUS space_set_east(Space* space, Id id);

/**
* @brief gets a pointer towards east.
*
* @author Javier Romera
* @param {Space*} - space;
* @return {STATUS} - Returns an state;
*/

Id space_get_east(Space* space);

/**
* @brief sets the id of a space to west.
*
* @author Javier Romera
* @param {Space*} - space; {Id} - id;
* @return {STATUS} - Returns an state;
*/

STATUS space_set_west(Space* space, Id id);

/**
* @brief gets a pointer towards west.
*
* @author Javier Romera
* @param {Space*} - space;
* @return {STATUS} - Returns an state;
*/

Id space_get_west(Space* space);

/**
* @brief it deletes the object with the specified id from the space
*
* @author Javier Romera
* @param {Space*} - space; {Id} - id;
* @return {STATUS} - Returns an state;
*/
STATUS space_del_object(Space* space, Id id);

/**
* @brief it adds the object with the specified id to the space
*
* @author Javier Romera
* @param {Space*} - space; {Id} - id;
* @return {STATUS} - Returns an state;
*/
STATUS space_add_object(Space* space, Id id);

/**
* @brief gets a pointer towads an object.
*
* @author Javier Romera
* @param {Game*} - game;
* @return {void} - Do not returns nothing;
*/
Id space_get_object( Space* space, Id id );

/**
* @brief prints a space.
*
* @author Javier Romera
* @param {Game*} - game;
* @return {void} - Do not returns nothing;
*/
STATUS space_print(Space* space);

/**
* @brief checks if the space has an object with the specified id
*
* @author Javier Romera
* @version 2.0
* @date 07/02/2019
* @param {Space} - space; {Id} - id;
* @return {bool} - Returns TRUE or FALSE;
*/
bool space_has_object( Space *space, Id id );

/**
* @brief it paints the figure associated to the space
*
* @author Javier Romera
* @param {Space*} - space; {char*} - pict;
* @return {STATUS} - Returns an state;
*/
STATUS space_set_picture( Space *space, char *pict );

/**
* @brief it gets the figure associated to the specified space
*
* @author Javier Romera
* @param {Space*} - space;
* @return {char*} - Returns a pointer to char;
*/
char* space_get_picture( Space *space );


#endif
