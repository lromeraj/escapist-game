/**
 * @brief Defines a game reader.
 *
 * @file reader.h
 * @author Álvaro Rodríguez & Javier Romera
 * @version 1.0
 * @date 07/02/2019
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"

/**
* @brief Loads spaces from a file
*
* @param {Game*} game - Pointer to game data
* @poram {char*} filename - name of the source file
* @retval {STATUS} - Returns an status
*/
STATUS reader_load_spaces( Game *game , char *f_name );

/**
* @brief Loads objects from a file
*
* @param {Game*} game - Pointer to game data
* @poram {char*} filename - name of the source file
* @retval {STATUS} - Returns an status
*/
STATUS reader_load_objects( Game *game , char *f_name );

#endif
