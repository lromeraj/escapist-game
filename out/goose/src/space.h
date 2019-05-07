/**
 * @brief Space module
 *
 * @file space.h
 * @author Álvaro Rodríguez || Javier Romera
 * @version 1.0
 * @date 07/02/2019
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"

/* Public structure space contains and id, name, the position of the cell (current space; north, south, east, west) and the id of the objects on it. */


#define MAX_SPACES 200
#define FIRST_SPACE 1

#define PICTURE_LEN 100

typedef struct _Space Space;

/** space_create defines a new space in the game area.
*
* @param {Id} - id;
* @return {Space} - returns an space pointer;
*/

Space* space_create(Id id);

/** space_destroy sets to null a space area.
*
* @param {Space*} - space;
* @return {STATUS} - Returns a state;
*/

STATUS space_destroy(Space* space);

/** space_get_id takes the id of a space.
*
* @param {Space*} - space;
* @return {Id} - Returns an id;
*/

Id space_get_id(Space* space);

/** space_set_name defines the name of a space.
*
* @param {Space*} - space; {Char*} - name;
* @return {STATUS} - Returns an state;
*/

STATUS space_set_name(Space* space, char* name);

/** space_get_name takes the name of a space.
*
* @param {Space*} - space;
* @return {const char*} - Returns a constant character array;
*/

const char* space_get_name(Space* space);

/** space_set_north sets the id of a space to north.
*
* @param {Space*} - space; {Id} - id;
* @return {STATUS} - Returns an state;
*/

STATUS space_set_north(Space* space, Id id);

/** space_get_north gets a pointer towards north.
*
* @param {Space*} - space;
* @return {STATUS} - Returns an state;
*/

Id space_get_north(Space* space);

/** space_set_south sets the id of a space to south.
*
* @param {Space*} - space; {Id} - id;
* @return {STATUS} - Returns an state;
*/

STATUS space_set_south(Space* space, Id id);

/** space_get_south gets a pointer towards south.
*
* @param {Space*} - space;
* @return {STATUS} - Returns an state;
*/

Id space_get_south(Space* space);

/** space_set_east sets the id of a space to east.
*
* @param {Space*} - space; {Id} - id;
* @return {STATUS} - Returns an state;
*/

STATUS space_set_east(Space* space, Id id);

/** space_get_east gets a pointer towards east.
*
* @param {Space*} - space;
* @return {STATUS} - Returns an state;
*/

Id space_get_east(Space* space);

/** space_set_west sets the id of a space to west.
*
* @param {Space*} - space; {Id} - id;
* @return {STATUS} - Returns an state;
*/

STATUS space_set_west(Space* space, Id id);

/** space_get_west gets a pointer towards west.
*
* @param {Space*} - space;
* @return {STATUS} - Returns an state;
*/

Id space_get_west(Space* space);


STATUS space_del_object(Space* space, Id id);
STATUS space_add_object(Space* space, Id id);



/** space_has_object gets a pointer towads an object.
*
* @param {Game*} - game;
* @return {void} - Do not returns nothing;
*/

Id space_get_object( Space* space, Id id );

/** space_print prints a space.
*
* @param {Game*} - game;
* @return {void} - Do not returns nothing;
*/

STATUS space_print(Space* space);

bool space_has_object( Space *space, Id id );

STATUS space_set_picture( Space *space, char *pict );
char* space_get_picture( Space *space );


#endif
