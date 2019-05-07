/**
 * @brief Defines the enumeration and structure used by the command interpreter.
 *
 * @file command.h
 * @author Javier Romera
 * @version 1.0
 * @date 07/02/2019
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define MAX_CMD_LEN 50
#define MAX_CMDS 15
#define MAX_CMD_ARGC 5
#define MAX_CMD_ANS 500
#define MAX_CMD_IN 100

// command ids
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

typedef void (*cmd_fn)(void*);

typedef struct _Cmd Cmd;

void cmd_set( Cid id, const char* b_name, const char *s_name, cmd_fn fn );
void cmd_free();
Cmd *req_cmd();
void cmd_set_ans( Cmd *cmd, int errc, const char *str, ... );
const char *cmd_get_ans( Cmd *cmd );
const char *cmd_get_argv( Cmd *cmd, int idx );
const int cmd_get_argc( Cmd *cmd );
const int cmd_get_errc( Cmd *cmd );
const Cid cmd_get_cid( Cmd *cmd );
const char *cmd_get_bname( Cmd *cmd );
const char *cmd_get_sname( Cmd *cmd );
void cmd_cb( Cmd *cmd, void *vp );

#endif
