/**
 * @brief link functions
 *
 * @file link.h
 * @version 0.0.3
 * @date 19/03/2019
 * @author Gonzalo Serrano
 * @copyright GNU Public License
 */

#ifndef LINK_H
#define LINK_H

#include "types.h"
#include <stdio.h>

#define MAX_LINKS 100
#define MAX_LINK_NAME 100 /*!< @brief Maximum length of the link name */

/**
 * @brief The enum of the state
 *
 */
typedef enum { LINK_OPENED, LINK_CLOSED } LinkState;

typedef struct _Link Link;

/**
 * @brief initializes a new link
 *
 * @date 19/03/2019
 * @author: Gonzalo Serrano
 *
 * @param {Id} id - Link identification
 * @retval {Link*} - returns a pointer to the new link
 */
Link *link_create( Id id );

/**
 * @brief destroys a link
 *
 * @date 19/03/2019
 * @author Gonzalo Serrano
 *
 * @param {Link*} link - Link pointer
 * @retval {void} - Do not returns nothing
 */
STATUS link_destroy( Link *link );

/**
 * @brief Gets the id of a link
 *
 * @date 19/03/2019
 * @author Gonzalo Serrano
 *
 * @param {Link*} link - Link pointer
 * @retval {Id} - Returns the id of a link
 */
Id link_get_id( Link *link );

/**
 * @brief Gets the destination id of a link
 *
 * @date 19/03/2019
 * @author Gonzalo Serrano
 *
 * @param {Link*} link - Link pointer
 * @retval {Id} - Returns the idFrom of a link
 */
Id link_get_from( Link *link );

/**
 * @brief gets the idTo of a link
 *
 * @date 19/03/2019
 * @author Gonzalo Serrano
 *
 * @param {Link*} link - Link pointer
 * @retval {Id} - Returns the idTo of a link
 */
Id link_get_to( Link *link );

/**
 * @brief gets the name of a link
 *
 * @date 19/03/2019
 * @author Gonzalo Serrano
 *
 * @param {Link*} link - Link pointer
 * @retval {Id} - Returns the name of a link
 */
const char* link_get_name( Link *link );

/**
 * @brief gets the state of a link OPEN or CLOSE
 *
 * @date 19/03/2019
 * @author Gonzalo Serrano
 *
 * @param {Link*} link - Link pointer
 * @retval {LinkState} - Returns the state of a link
 */
LinkState link_get_state( Link *link );

/**
 * @brief Sets the state of a given link
 *
 * @date 19/03/2019
 * @author Gonzalo Serrano
 *
 * @param {Link*} link - Link pointer
 * @param {LinkState} id - New state of the link
 * @return {STATUS} - Returns an status
 */
STATUS link_set_state( Link *link, LinkState state );

/**
 * @brief it set the id of a link on the structure
 *
 * @date 19/03/2019
 * @author Gonzalo Serrano
 *
 * @param {Link*} link - Link pointer
 * @param {Id} id - id of a link
 * @return {STATUS} - Returns an status
 */
STATUS link_set_id( Link *link, Id id );

/**
 * @brief it set the idFrom of a link on the structure
 *
 * @date 19/03/2019
 * @author Gonzalo Serrano
 *
 * @param {Link*} link - Link pointer
 * @param {Id} idFrom - idFrom of a link
 * @return {STATUS} - Returns an status
 */
STATUS link_set_from( Link *link, Id idFrom );

/**
 * @brief it set the idTo of a link on the structure
 *
 * @date 19/03/2019
 * @author Gonzalo Serrano
 *
 * @param {Link*} link - Link pointer
 * @param {Id} idTo - idTo of a link
 * @return {STATUS} - Returns an status
 */
STATUS link_set_to( Link *link, Id idTo );

/**
 * @brief it set the id of a link on the structure
 *
 * @date 19/03/2019
 * @author Gonzalo Serrano
 *
 * @param {Link*} link - Link pointer
 * @param {name} - Link name
 * @return {STATUS} - Returns an status
 */
STATUS link_set_name( Link *link, const char* name );

/**
 * @brief prints a link.
 *
 * @date 19/03/2019
 * @author Gonzalo Serrano
 *
 * @param {FILE*} stream - Streaming output
 * @param {Link*} link - Link pointer
 * @return {STATUS} - Returns an status
 */
STATUS link_print( FILE *stream, Link *link );

#endif
