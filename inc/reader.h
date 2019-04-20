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

enum {
  _RD_OBJS,
  _RD_SPACES,
  _RD_LINKS
};

int reader_load( Game *game, const char *f_name, int its );

#endif
