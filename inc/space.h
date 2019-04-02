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

#define MAX_SPACE_NAME 50 /*!< @brief Maximum length of the space name */
#define MAX_SPACES 200 /*!< @brief Maximum number of spaces */
#define PICTURE_LEN 100 /*!< @brief Maximum lenght of the space's picture */


/*!
* @brief Definition of the Space structure
*/
typedef struct _Space Space;

/**
* @brief creates a new space
* @author Javier Romera
* @param {Id} - Space identification
* @retval {Space*} - returns an space pointer
*/
Space* space_create( Id id );


/**
* @brief sets to null a space area
* @author Javier Romera
* @version 2.0
* @param {Space*} space - Space pointer
* @retval {STATUS} - Returns a state
*/
STATUS space_destroy(Space* space);


/**
* @brief takes the id of a space
* @author Javier Romera
* @version 2.0
* @param {Space*} space - Space pointer
* @retval {Id} - Returns an id
*/
Id space_get_id(Space* space);


/**
* @brief defines the name of a space
* @author Javier Romera
* @param {Space*} - space
* @param {Char*} - name
* @retval {STATUS} - Returns an state
*/

STATUS space_set_name(Space* space, char* name);

/**
*
* @brief takes the name of a space
* @author Javier Romera
* @version 2.0
* @date 07/02/2019
* @param {Space*} - space
* @retval {char*} - Returns an array of characters
*/

const char* space_get_name(Space* space);


/**
* @brief Get a link from the space
* @param {Sapce*} sp - Space pointer
* @param {CardinalPoint} cp - Cardinal point of the space
*/
Id space_get_link( Space *sp, CardinalPoint cp );


/**
* @brief Sets a links id in a given space
* @param {Sapce*} sp - Space pointer
* @param {CardinalPoint} cp - Cardinal point of the space
* @param {Id} id - Link's id
* @retval {STATUS} - Returns an status
*/
STATUS space_set_link( Space *sp, CardinalPoint cp, Id id );


/**
* @brief it deletes the object with the specified id from the space
* @author Javier Romera
* @param {Space*} - space
* @param {Id} - id
* @retval {STATUS} - Returns an state
*/

STATUS space_del_object(Space* space, Id id);

/**
* @brief it adds the object with the specified id to the space
* @author Javier Romera
* @param {Space*} - space
* @param {Id} - id
* @retval {STATUS} - Returns an state
*/

STATUS space_add_object(Space* space, Id id);

/**
* @brief gets a pointer towads an object
* @author Javier Romera
* @param {Game*} - game
*/

Id space_get_object( Space* space, Id id );

/**
* @brief prints a space
* @author Javier Romera
* @param {Game*} - game
*/

STATUS space_print(Space* space);

/**
* @brief checks if the space has an object with the specified id
* @author Javier Romera
* @param {Space} - space
* @param {Id} - id
* @retval {bool} - Returns TRUE or FALSE
*/

bool space_has_object( Space *space, Id id );

/**
* @brief it paints the figure associated to the space
* @author Javier Romera
* @param {Space*} - space
* @param {char*} - pict
* @retval {STATUS} - Returns an state
*/

STATUS space_set_picture( Space *space, char *pict );

/**
* @brief it gets the figure associated to the specified space
* @author Javier Romera
* @param {Space*} - space
* @retval {char*} - Returns a pointer to char
*/

char* space_get_picture( Space *space );


#endif