/**
 * @brief It defines the game interface
 *
 * @file game.h
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
#include "link.h"
#include <stdio.h>

#define MIN_WIN_COLS 80 /*!< @brief Minimum width of the screen */
#define MIN_WIN_ROWS 24 /*!< @brief Minimum height of the screen */

enum {
  GAME_SPACES,
  GAME_LINKS,
  GAME_OBJECTS
};

/*
* @brief Definition of Game structure
*/
typedef struct _Game Game;


/**
* @brief Adds a given space into the game
* @param {Game*} game - Game pointer
* @param {Space*} space - Space pointer
* @retval {STATUS} - Returns an status code
*/
STATUS game_add_space( Game *game, Space *space );

/**
* @brief Adds a given link into the game
* @param {Game*} game - Game where the link should be added
* @param {Space*} ln - Link to be added
* @retval {STATUS} - Returns an status code
*/
STATUS game_add_link( Game *game, Link *ln );


/**
* @brief presets game initial state onto NULL
* @author Javier Romera
* @param {Game*} - game
* @retval {Game*} - Returns a game pointer
*/
Game* game_create();


/**
* @brief presets game state with the data value included in the save file
* @author Álvaro Rodríguez
* @param {Game*} - game
* @param {char*} - filename
* @retval {STATUS} - Returns an status code
*/
STATUS game_load_from_file(Game* game, char* filename);


/**
* @brief sets the last command value onto last key introduced
* @author Javier Romera
* @param {Game*} - game
* @param {Cmd*} - cmd
* @retval {STATUS} - Returns an status code
*/
STATUS game_update(Game* game, Cmd *cmd);


/**
* @brief frees dynamic memory reserved in game
* @author Álvaro Rodríguez
* @param {Game*} - game
* @retval {STATUS} - Returns an status code
*/
STATUS game_destroy(Game* game);


/**
* @brief quits game
* @author Javier Romera
* @param {Game*} - game
* @retval {bool} - Returns a boolean value
*/
bool game_is_over(Game* game);


/**
* @brief gets all the existing spaces with the same id if the id passed as argument exist
* @author Álvaro Rodríguez
* @param {Game*} - game, {Id} - id
* @retval {Space*} - Returns a space pointer
*/
Space* game_get_space( Game* game, Id id );


/**
* @brief gets the space of an object
* @author Javier Romera
* @param {Game*} - game
* @retval {Space*} - Returns an space pointer
*/
Space* game_get_object_space( Game *game, Id id );


/**
* @brief set the position of an object in the game
* @author Javier Romera
* @param {Game*} - game
* @retval {STATUS} - Returns a state
*/
STATUS game_set_object_location(Game* game, Id id);


/**
* @brief gets a pointer towards player
* @author Álvaro Rodríguez
* @param {Game*} - game
* @retval {Player*} - Returns a player pointer
*/
Player* game_get_player(Game *game);


/**
* @brief gets a object by id
* @author Javier Romera
* @param {Game*} - game
* @retval {Object*} - Returns a player pointer
*/
Object* game_get_object_by_id( Game *game, Id id );


/**
* @brief gets a object by idx
* @author Javier Romera
* @param {Game*} - game
* @retval {Object*} - Returns a player pointer
*/
Object* game_get_object_by_idx( Game *game, int idx );


/**
* @brief gets a object by name
* @author Javier Romera
* @param {Game*} - game
* @param {char*} name - The name of the object
* @retval {Object*} - Returns a player pointer
*/
Object* game_get_object_by_name( Game *game, const char *name );


/**
* @brief Gets a link by it's id
* @author Javier Romera
* @param {Game*} - game
* @oaram {Id} id - The id of the link
* @retval {Link*} - Returns a link pointe or null
*/
Link* game_get_link_by_id( Game *game, Id id );


/**
* @brief sets a new player
* @author Álvaro Rodríguez
* @param {Game*} - game
* @param {Player*} - player
* @retval {STATUS} - Returns a state
*/
STATUS game_set_player(Game *game, Player *player);


/**
* @brief sets a new object
* @author Javier Romera
* @param {Game*} - game
* @param {Object*} - object
* @retval {STATUS} - Returns a state
*/
STATUS game_add_object(Game *game, Object *object);


/**
* @brief sets a new die
* @author Javier Romera
* @param {Game*} - game
*/
void game_set_die( Game *game, Die *d );


/**
* @brief gets a pointer towards last space
* @author Javier Romera
* @param {Game*} - game
* @retval {Space} - Returns a space pointer
*/
Space *game_get_last_space( Game *game );

void game_get_spaces( Game *game, int max, Space **spaces, int *total );
void game_get_links( Game *game, int max, Link **links, int *total );
void game_get_objects( Game *game, int max, Object **objs, int *total );


/**
* @brief gets a pointer towards first space
* @author Javier Romera
* @param {Game*} - game
* @retval {Space} - Returns a space pointer
*/
Space *game_get_first_space( Game *game );


/**
* @brief gets a pointer towards die
* @author Javier Romera
* @param {Game*} - game
* @retval {Player} - Returns a die pointer
*/
Die *game_get_die( Game *game );


/**
* @brief gets a pointer towards cmd
* @author Javier Romera
* @param {Game*} - game
* @retval {Player} - Returns a cmd pointer
*/
Cmd *game_get_cmd( Game *game );

STATUS game_clean( Game *game );

#endif
