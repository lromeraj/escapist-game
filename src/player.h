/**
 * @brief Player header
 *
 * @file player.h
 * @version 0.5.6
 * @date 07/02/2019
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

typedef struct _Player Player;


/**
* @brief This fuction initializes a player
* @author Miguel Rodríguez
* @param {Id} - Player identification
* @retval {Player*} - Returns a player's pointer
*/
Player* player_create( Id id );

/**
* @brief This fuction destroys a player
* @author Miguel Rodríguez
* @param {Player*} player - player's pointer
*/
STATUS player_destroy(Player* player);

/**
* @brief This fuction gets the palyer's id
* @author Miguel Rodríguez
* @param {Player*} player - player's pointer
* @retval {Id} - player's id
*/
Id player_get_id(Player* player);

/**
* @brief This fuction sets the palyer's id
* @author Miguel Rodríguez
* @param {Player*} player - player's pointer
* @param {Id} id - player's id
*/
void player_set_id( Player* player, Id id );

/**
* @brief This fuction sets the player's name
* @author Miguel Rodríguez
* @param {Player*} player - player's pointer
* @param {char*} name - player's name
* @retval {STATUS} - Returns a status code
*/
STATUS player_set_name(Player* player, char* name);


/**
* @brief This fuction gets the palyer's name
* @author Miguel Rodríguez
* @param {Player*} player - player's pointer
* @retval {char*} - Returns a pointer to the player's name
*/
const char* player_get_name(Player* player);

/**
* @brief This fuction sets the player's location
* @author Miguel Rodríguez
* @param {Player*} player - player's pointer
* @param {Id} id - player's identifier
* @retval {STATUS} - Returns a status code
*/
STATUS player_set_location(Player* player, Id id);

/**
* @brief This fuction gets the palyer's location
* @author Miguel Rodríguez
* @param {Player*} player - player's pointer
* @retval {Id} - player's location
*/
Id player_get_location(Player* player);

/**
* @brief This fuction adds an object to playes's inventory
* @author Miguel Rodríguez
* @param {Player*} player - player's pointer
* @param {Id} id - player's identifier
*@retval {STATUS} - Returns a status code
*/
STATUS player_add_object(Player* player, Id id);

/**
* @brief This fuction searches if an object is in the player's inventory
* @author Miguel Rodríguez
* @param {Player*} player - player's pointer
* @param {Id} id - player's identifier
* @retval {BOOL} - Returns a boolean code
*/
bool player_has_object( Player* player, Id id );

/**
* @brief This fuction removes an object from player's inventory
* @author Miguel Rodríguez
* @param {Player*} player - player's pointer
* @param {Id} id - player's identifier
*@retval {STATUS} - Returns a status code
*/
STATUS player_del_object(Player* player, Id id);

/**
* @brief This fuction prints the payer structure
* @author Miguel Rodríguez
* @param {Player*} player - player's pointer
* @retval {STATUS} - Returns a status code
*/
STATUS player_print(Player* player);

/**
* @brief Gets the current player object
*
* @param {Player*} player - Player to be checked
* @retval {Id} - Returns the id of the player's object
*/

#endif
