/**
 * @brief Defines a game reader.
 *
 * Contains the implementation of the functions that are associated to the reading of the file
 * To obtain its values
 *
 * @file manager.h
 * @version 1.0
 * @date 07/02/2019
 * @author Álvaro Rodríguez
 * @copyright GNU Public License
 */

#ifndef MANAGER_H
#define MANAGER_H

#include "game.h"


/*!< @brief Reader structure
 *!< @brief contains the elements that can be read from the data file
 */

typedef enum _Rd_item {
  _RD_OBJS,   /*!< @brief Manager object*/
  _RD_SPACES, /*!< @brief Manager spaces*/
  _RD_LINKS,  /*!< @brief Manager links*/
  _RD_PLAYERS /*!< @brief Manager players*/
} Rd_item;


/**
* @brief This fuction load a file saved previously
* @author Javier Romera
* @param  game - game's pointer
* @param  f_name - char name
* @param  its - item read
* @retval - Returns an integer
*/
int manager_load( Game *game, const char *f_name, Rd_item its );


/**
* @brief This fuction save the game on a file
* @author Javier Romera
* @param obj - object's pointer
* @param  f_name - char name
* @retval - Returns a set pointer
*/
int manager_save( Game *game, const char *f_name );

#endif
