/**
 * @brief Command interpreter
 *
 * @file command.h
 * @author Javier Romera
 * @version 0.8.3
 * @date 14/03/2019
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define MAX_CMD_LEN 50 /* maximum command length */
#define MAX_CMDS 15 /* maximum quantity of commands*/
#define MAX_CMD_ARGC 5 /* maximum command arguments */
#define MAX_CMD_ANS 200 /* maximum command answer length */
#define MAX_CMD_IN 100  /* maximum command input length */

/* command identification */
typedef enum enum_Cid {
  UNKNOWN,
  EXIT,
  NEXT,
  BACK,
  TAKE,
  DROP,
  ROLL,
  LEFT,
  RIGHT
} Cid;

/* command callback */
typedef void (*cmd_fn)(void*);

typedef struct _Cmd Cmd;

/** Sets up a new command and stores it inside a private array
* @param {Cid} id - Command id
* @param {const char*} b_name - The base name of the command
* @param {const char*} s_name - The short name of the command
* @param {cmd_fn} fn - Command callback function
*/
void cmd_set( Cid id, const char* b_name, const char *s_name, cmd_fn fn );

/** Gets a command by its id
* @param {Cid} id - Command id
* @return - Command pointer
*/
Cmd *cmd_get( Cid id );

/** Destroy all the setted commands */
void cmd_free();

/** Requests a new command from stdin
* @return - Returns a pointer of the parsed command
*/
Cmd *cmd_req();

/** Calls to the callback function stored in the given command
* @param {Cmd*} cmd - Command pointer
*/
void cmd_cb( Cmd *cmd, void *vp );

/** Sets an answer to the given command
* @param {Cmd*} cmd - Command pointer
* @param {int} errc - Error code
* @param {const char*} str - String format
* @param {...} - String format arguments
*/
void cmd_set_ans( Cmd *cmd, int errc, const char *str, ... );

/** Gets a previus answer of the given command
* @param {Cmd*} cmd - Command pointer
* @return {const char*} - Command answer
*/
const char *cmd_get_ans( Cmd *cmd );

/** Gets the desired indexed argument
* @param {Cmd*} cmd - Command pointer
* @return {int} idx - Argument index
* @return {const char*} - Returns the requested indexed argument
*/
const char *cmd_get_argv( Cmd *cmd, int idx );

/** Gets the number of arguemnts of a given command
* @param {Cmd*} cmd - Command pointer
* @return {const int} - Number of arguments
*/
const int cmd_get_argc( Cmd *cmd );

/** Gets the error code of a given command
* @param {Cmd*} cmd - Command pointer
* @return {const int} - Error code
*/
const int cmd_get_errc( Cmd *cmd );

/** Gets the command id
* @param {Cmd*} cmd - Command pointer
* @return {const Cid} - Command id
*/
const Cid cmd_get_cid( Cmd *cmd );

/** Gets the base name of a given command
* @param {Cmd*} cmd - Command pointer
* @return {const char*} - Command base name
*/
const char *cmd_get_bname( Cmd *cmd );

/** Gets the short name of a given command
* @param {Cmd*} cmd - Command pointer
* @return {const char*} - Command short name
*/
const char *cmd_get_sname( Cmd *cmd );

#endif
