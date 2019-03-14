/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Álvaro Rodríguez & Javier Romera
 * @version 0.5.1
 * @date 14/03/2019
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "cmd.h"
#include "space.h"
#include "player.h"
#include "object.h"
#include "die.h"
#include <stdio.h>

typedef struct _Game {
  Player* player;
  Die *die;
  Object* objects[ MAX_OBJECTS ];
  Space* spaces[ MAX_SPACES + 1 ];
  Cmd *last_cmd;
} Game;

/** game_add_space adds a given space into the game.
*
* @param {Game*} - game, {Space*} - space;
* @return {STATUS} - Returns an status code;
*/
STATUS game_add_space(Game *game, Space *space);

/*Declaration of funcions used in game.c*/

/** game_create presets game initial state onto NULL.
*
* @param {Game*} - game;
* @return {STATUS} - Returns an status code (OK);
*/
STATUS game_create(Game* game);

/** game_create_from_file presets game state with the data value included in the save file.
*
* @param {Game*} - game, {char*} - filename,
* @return {STATUS} - Returns an status code;
*/
STATUS game_create_from_file(Game* game, char* filename);

/** game_update sets the last command value onto last key introduced.
*
* @param {Game*} - game; {T_Command} - cmd;
* @return {Status} - Returns an status code;
*/
STATUS game_update(Game* game, Cmd *cmd);

/** game_destroy frees dynamic memory reserved in game spaces.
*
* @param {Game*} - game;
* @return {STATUS} - Returns an status code (OK);
*/
STATUS game_destroy(Game* game);

/** game_is_over quits game.
*
* @param {Game*} - game;
* @return {BOOL} - Returns a boolean code (FALSE);
*/
bool game_is_over(Game* game);


/** game_print_screen prints game screen. Unused.
*
* @param {Game*} - game;
* @return {void} - Do not returns nothing;
*/
void game_print_screen(Game* game);

/** game_print_data prints by screen the message that indicates player_location
* where the command has to be introduced, as well as the spaces, object and
* player location.
*
* @param {Game*} - game;
* @return {void} - Do not returns nothing;
*/
void game_print_data(Game* game);

/** game_get_space gets all the existing spaces with the same id if the id passed as argument exist.
*
* @param {Game*} - game, {Id} - id;
* @return {Space*} - Returns a space or NULL;
*/
Space* game_get_space( Game* game, Id id );

/** Searches inside spaces array and if it founds an object
* it will return a pointer to the space containing that object
* There is no need to comapre id's by the moment becouse there is only one object and one player
* @param {Game*} - game
* @return {Space*} - Returns an space pointer or NULL;
*/
Space* game_get_object_space( Game *game, Id id );

/** game_set_object_location set the position of an object in the game.
*
* @param {Game*} - game;
* @return {Id} - Returns a pointer;
*/
STATUS game_set_object_location(Game* game, Id id);

/** game_get_player gets a pointer towards player.
*
* @param {Game*} - game;
* @return {T_Command} - Returns a player pointer;
*/
Player* game_get_player(Game *game);

/** game_get_object gets a pointer towards player.
*
* @param {Game*} - game;
* @return {T_Command} - Returns a object pointer;
*/
Object* game_get_object( Game *game, Id id );

/** game_set_player sets a new player.
*
* @param {Game*} - game; {Player*} - player;
* @return {T_Command} - Returns a state;
*/
STATUS game_set_player(Game *game, Player *player);

/** game_set_object sets a new object.
*
* @param {Game*} - game; {Object*} - object;
* @return {T_Command} - Returns a state;
*/
STATUS game_set_object(Game *game, Object *object);

/** game_set_die sets a new die.
*
* @param {Game*} - game; {Object*} - object;
* @return {T_Command} - Returns a state;
*/
void game_set_die( Game *game, Die *d );

Space *game_get_last_space( Game *game );
Space *game_get_first_space( Game *game );

#endif
