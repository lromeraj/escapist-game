/**
 * @brief It defines a player.
 *
 * @file player.h
 * @version 1.0
 * @date 07/02/2019
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

/* Public structure Player contains the id, name, location and the object of a player. */

typedef struct _Player Player;

/* Defines maximum number of players as 100 and the first player Id as 1. */

#define MAX_PLAYERS 100
#define FIRST_PLAYER 1

/** player_create defines a new player.
*
* @param {} - do not receive arguments;
* @return {Player*} - returns a player pointer;
*/

Player* player_init();

/** player_destroy destroys a player.
*
* @param {Player*} - player;
* @return {STATUS} - Returns a state;
*/

STATUS player_destroy(Player* player);

/** player_get_id takes the id of a player.
*
* @param {Player*} - player;
* @return {Id} - Returns an id;
*/

Id player_get_id(Player* player);

/** player_set_id sets te id of a player.
*
* @param {Player*} - player; {Id} - id;
* @return {void} - Do not return nothing;
*/

void player_set_id( Player* player, Id id );

/** player_set_name defines the name of a player.
*
* @param {Player*} - player; {Char*} - name;
* @return {STATUS} - Returns an state;
*/

STATUS player_set_name(Player* player, char* name);

/** player_get_name takes the name of a player.
*
* @param {Player*} - player;
* @return {const char*} - Returns a constant character array;
*/

const char* player_get_name(Player* player);

/** player_set_north sets the location of a player.
*
* @param {Player*} - player; {Id} - id;
* @return {STATUS} - Returns an state;
*/

STATUS player_set_location(Player* player, Id id);

/** player_get_north gets the location of a players.
*
* @param {Player*} - player;
* @return {Id} - Returns an id;
*/

Id player_get_location(Player* player);

/** player_set_object sets an id to a player's object.
*
* @param {Player*} - player; {Id} - id;
* @return {STATUS} - Returns an state;
*/

STATUS player_set_object(Player* player, Id id);

/** player_has_object gets a pointer towards an object.
*
* @param {Game*} - game;
* @return {void} - Do not returns nothing;
*/
bool player_has_object(Player* player);

/** player_print prints a player on the game screen.
*
* @param {Game*} - game;
* @return {void} - Do not returns nothing;
*/

STATUS player_print(Player* player);

/** player_get_object gets the id of a player's object.
*
* @param {Player*} - player;
* @return {Id} - Returns id;
*/

Id player_get_object(Player* player);

#endif
