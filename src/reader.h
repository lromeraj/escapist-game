/**
 * @brief Defines a game reader.
 *
 * Contains the implementation of the functions that are associated to the reading of the file
 * To obtain its values
 *
 * @file reader.h
 * @version 1.0
 * @date 07/02/2019
 * @author Álvaro Rodríguez
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"

/**
 * @brief Loads spaces from a file
 *
 * @date 07/02/2019
 * @author Álvaro Rodríguez
 *
 * @param {Game*} game - Pointer to game data
 * @param {char*} f_name - name of the source file
 * @retval {STATUS} - Returns an status
 */
STATUS reader_load_spaces( Game *game , char *f_name );

/**
 * @brief Loads objects from a file
 *
 * @date 07/02/2019
 * @author Álvaro Rodríguez
 *
 * @param {Game*} game - Pointer to game data
 * @poram {char*} filename - name of the source file
 * @retval {STATUS} - Returns an status
 */
STATUS reader_load_objects( Game *game , char *f_name );

#endif
