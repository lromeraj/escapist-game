/**
 * @brief It defines a textual graphic engine.
 *
 * @file G_engine.h
 * @author Álvaro Rodríguez & Javier Romera
 * @version 1.0
 * @date 07/02/2019
 * @copyright GNU Public License
 */

#ifndef G_ENGINE_H
#define G_ENGINE_H

#include "game.h"

/**
* Private structure for graphic engine.
*/
typedef struct _G_engine G_engine;

/** @brief Creates a new graphic engine
*
* @retval {G_engine*} - Returns a graphic engine pointer
*/
G_engine* g_engine_create();

/** g_engine_destroy deletes the paramters defined by G_engine_create
* if and only if a graphic engine has been started.
*
* @param {G_engine*} - ge;
* @return {void} - Do not return nothing;
*/
void g_engine_destroy( G_engine *ge );

/** g_engine_paint_game draws the parameters of the game map's area on the interface.
*
* @param {G_engine*} - ge; {Game*}- game;
* @return {void} - Do not return nothing;
*/
void g_engine_paint_game( G_engine *ge, Game *game );

/** g_engine_write_command ------
*
* @param {G_engine*} - ge; {char*} - str;
* @return {void} - Do not return nothing;
*/
void g_engine_write_command( G_engine *ge, char *str );

#endif
