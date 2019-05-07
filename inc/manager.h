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

typedef enum _Rd_item {
  _RD_OBJS,
  _RD_SPACES,
  _RD_LINKS,
  _RD_PLAYERS
} Rd_item;

int manager_load( Game *game, const char *f_name, Rd_item its );
int manager_save( Game *game, const char *f_name );

#endif
