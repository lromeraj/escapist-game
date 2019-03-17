/**
 * @brief It defines a textual graphic engine.
 *
 * @file g_engine.h
 * @version 0.7.1
 * @date 10/03/2019
 * @copyright GNU Public License
 */

#ifndef G_ENGINE_H
#define G_ENGINE_H

#include "game.h"

typedef struct _G_engine G_engine;

/**
* @brief Creates a new graphic engine
* @retval {G_engine*} - Returns a graphic engine pointer
*/
G_engine* g_engine_create();

/**
* @brief deletes the paramters defined by G_engine_create
* @param {G_engine*} ge - Graphic engine pointer
*/
void g_engine_destroy( G_engine *ge );

/**
* @brief Draws the user interface
* @param {G_engine*} ge - Graphic engine pointer
* @param {Game*} - Game pointer
*/
void g_engine_paint_game( G_engine *ge, Game *game );

#endif
