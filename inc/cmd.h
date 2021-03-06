/**
* @brief Command interpreter
*
* @file cmd.h
* @author Javier Romera
* @version 0.8.3
* @date 14/03/2019
* @copyright GNU Public License
*/

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define MAX_CMD_LEN 50 /*!< @brief Maximum command length */
#define MAX_CMDS 25 /*!< @brief Maximum quantity of commands*/
#define MAX_CMD_ARGC 5 /*!< @brief Maximum command arguments */
#define MAX_CMD_ANS 200 /*!< @brief Maximum command answer length */
#define MAX_CMD_IN 100  /*!< @brief Maximum command input length */

/*!
* @brief Command identification
*/
typedef enum enum_Cid {
  UNKNOWN, /*!< Unknown command */
  EXIT,  /*!< Exit command */
  NEXT,  /*!< Next command */
  BACK, /*!< Back command */
  TAKE, /*!< Take command */
  DROP, /*!< Drop command */
  ROLL, /*!< Roll command */
  MOVE, /*!< Move command */
  LEFT, /*!< Left command */
  RIGHT, /*!< Right command */
  INSPECT, /*!< Inspect command */
  HELP, /*!< Help command */
  TURN, /*!< Turn command */
  OPEN, /*!< Open command */
  SAVE, /*!< Save command */
  LOAD /*!< Load command */
} Cid;

/*!
* @brief Command callback
*/
typedef void (*cmd_fn)(void*);

typedef struct _Cmd Cmd; /*!< @brief Main cmd struct definition */

/**
* @brief Sets up a new command and stores it inside a private array
* @param id - Command identification
* @param b_name - The base name of the command
* @param s_name - The short name of the command
* @param fn - Command callback function
*/
void cmd_build( Cid id, const char* b_name, const char *s_name, cmd_fn fn );

/**
* @brief Gets a command by its id
* @param id - Command identification
* @retval {Cmd*} - Returns a pointer to the requested command
*/
Cmd *cmd_get_by_cid( Cid id );


/**
* @brief Gets a command by its id
* @param n - Short name or base name
* @retval {Cmd*} - Returns a pointer to the requested command
*/
Cmd *cmd_get_by_name( const char *n );

/**
* @brief Destroy all the setted commands
*/
void cmd_free();

/**
* @brief Requests a new command from stdin
* @retval - Returns a pointer of the parsed command
*/
Cmd *cmd_req();

/**
* @brief Calls to the callback function stored in the given command
* @param cmd - command pointer
* @param vp - command callback
*/
void cmd_cb( Cmd *cmd, void *vp );

/**
* @brief Sets an answer to the given command
* @param cmd - Command pointer
* @param errc - Error code
* @param str - String format
* @param - String format arguments
*/
void cmd_set_ans( Cmd *cmd, int errc, const char *frm, ... ) __attribute__ ( ( format(printf, 3, 4 ) ) );

/**
* @brief Gets a previus answer of the given command
* @param cmd - Command pointer
* @retval {char*} - Command answer
*/
const char *cmd_get_ans( Cmd *cmd );

/**
* @brief Gets the desired indexed argument
* @param cmd - Command pointer
* @retval {int} idx - Argument index
* @retval {char*} - Returns the requested indexed argument
*/
const char *cmd_get_argv( Cmd *cmd, int idx );

/**
* @brief Gets the number of arguemnts of a given command
* @param cmd - Command pointer
* @retval {int} - Number of arguments
*/
const int cmd_get_argc( Cmd *cmd );

/**
* @brief Gets the error code of a given command
* @param cmd - Command pointer
* @retval {int} - Error code
*/
const int cmd_get_errc( Cmd *cmd );

/**
* @brief Gets the command id
* @param cmd - Command pointer
* @retval {Cid} - Command id
*/
const Cid cmd_get_cid( Cmd *cmd );

/**
* @brief Gets the base name of a given command
* @param cmd - Command pointer
* @retval {char*} - Command base name
*/
const char *cmd_get_bname( Cmd *cmd );

/**
* @brief Gets the short name of a given command
* @param cmd - Command pointer
* @retval {char*} - Command short name
*/
const char *cmd_get_sname( Cmd *cmd );

#endif
