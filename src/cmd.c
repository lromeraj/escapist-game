/**
 * @brief It implements the game command interpreter.
 *
 * @file command.c
 * @author Álvaro Rodríguez & Javier Romera
 * @version 1.0
 * @date 07/02/2019
 * @copyright GNU Public License
 */

#include "cmd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

struct _Cmd {
  Cid id; /* id */
  int argc; /* number of arguments */
  char *argv[ MAX_CMD_ARGC ]; /* arguments */
  char b_name[ MAX_CMD_LEN ]; /* base name */
  char s_name[ MAX_CMD_LEN ]; /* short name */
  char input[ MAX_CMD_IN ]; /* cmd input */
  char answer[ MAX_CMD_ANS ]; /* command answer */
  int errc;
  cmd_fn fn; /* callback function */
};

Cmd *CMDS[ MAX_CMDS ];

void cmd_set( Cid id, const char* b_name, const char *s_name, cmd_fn fn ) {

  int i;
  Cmd *_cmd;
  static int idx = 0;

  if ( idx >= MAX_CMDS )
    return;

  _cmd = (Cmd*) malloc( sizeof( Cmd ) );

  if ( !_cmd )
    return;

  _cmd->id = id;
  strcpy( _cmd->b_name, b_name );
  strcpy( _cmd->s_name, s_name );

  _cmd->argc = 0;
  _cmd->errc = 0;
  _cmd->input[ 0 ] = 0;
  _cmd->answer[ 0 ] = 0;

  _cmd->fn = fn;

  for ( i=0; i < MAX_CMD_ARGC; i++ ) {
    _cmd->argv[ i ] = NULL;
  }

  CMDS[ idx ] = _cmd;

  idx++;
}


void cmd_argv_free( Cmd *cmd ) {

  int i;

  if ( !cmd )
    return;

  for ( i=0; i < MAX_CMD_ARGC; i++ ) {
    if ( cmd->argv[ i ] ) {
      free( cmd->argv[ i ] );
    }
  }

}

void cmd_free() {

  Cmd *_cmd;
  int i;

  for ( i=0; i < MAX_CMDS; i++ ) {
    _cmd = CMDS[ i ];
    if ( _cmd ) {
      cmd_argv_free( _cmd );
      free( _cmd );
    }
  }

}

const char *cmd_get_argv( Cmd *cmd, int idx ) {

  if ( !cmd )
    return NULL;


  if ( idx < 0 || idx >= MAX_CMD_ARGC )
    return NULL;

  if ( !cmd->argv[ idx ] )
    return NULL;

  return cmd->argv[ idx ];
}

const char *cmd_get_bname( Cmd *cmd ) {

  if ( !cmd )
    return NULL;

  return cmd->b_name;
}

const char *cmd_get_sname( Cmd *cmd ) {
  if ( !cmd )
    return NULL;

  return cmd->s_name;
}

const Cid cmd_get_cid( Cmd *cmd ) {

  if ( !cmd )
    return UNKNOWN;

  return cmd->id;
}

const int cmd_get_argc( Cmd *cmd ) {

  if ( !cmd )
    return 0;

  return cmd->argc;
}

void cmd_set_ans( Cmd *cmd, int errc, const char *frm, ... ) {

  va_list args;
  char buff[ MAX_CMD_ANS ];

  if ( !cmd || !frm )
    return;

  va_start( args, frm );
  vsprintf( buff, frm, args );
  va_end( args );

  cmd->errc = errc;
  strcpy( cmd->answer, buff );

}

const int cmd_get_errc( Cmd *cmd ) {

  if ( !cmd )
    return -1;

  return cmd->errc;
}

const char *cmd_get_ans( Cmd *cmd ) {

  if ( !cmd )
    return NULL;

  return cmd->answer;
}

Cmd *cmd_get( Cid id ) {
  int i;
  Cmd *_cmd = NULL;

  for (i=0; i < MAX_CMDS; i++) {
    _cmd = CMDS[ i ];
    if ( _cmd && _cmd->id == id  ) {
      return _cmd;
    }
  }

  return _cmd;
}

void cmd_cb( Cmd *cmd, void *vp ) {

  if ( !cmd )
    return;

  cmd->fn( vp );
}

Cmd *cmd_req() {

  Cmd *_cmd = NULL;
  int i, _i, j, len, argc;
  char c, in[ MAX_CMD_IN ], _buff[ MAX_CMD_IN ];

  if ( !fgets( in, MAX_CMD_IN - 1, stdin ) )
    return NULL;

  len = strlen( in );
  _i = 0;
  argc = 0;
  _buff[ 0 ] = 0;

  for ( i=0; i < len; i++ ) {

    c = in[ i ];
    bool addChar = true;
    bool addBuff = false;

    if ( c == ' ' || c == '\0' || c == '\n' ) {
      if ( _i ) {
        addBuff = true;
      }
      addChar = false;
    }

    if ( addChar ) {
      _buff[ _i ] = c;
      _buff[ _i + 1 ] = 0;
      _i++;
    }

    if ( addBuff ) {

      if ( !argc ) {

        _cmd = cmd_get( UNKNOWN );

        /* find the command */
        for ( j=0; (j < MAX_CMDS) && CMDS[ j ]; j++ ) {
          if ( !strcmp( _buff, CMDS[ j ]->b_name ) || !strcmp( _buff, CMDS[ j ]->s_name ) ) {
            _cmd = CMDS[ j ];
            break;
          }
        }

      }

      if ( _cmd ) { /* store the argument */

        if ( _cmd->argv[ argc ] ) {
          free( _cmd->argv[ argc ] );
          _cmd->argv[ argc ] = NULL;
        }

        _cmd->argv[ argc ] = (char*) malloc( (_i+1) * sizeof(char));
        strcpy( _cmd->argv[ argc ], _buff );

      }

      argc++;
      _buff[ 0 ] = 0;
      _i = 0;

      if ( argc >= MAX_CMD_ARGC )
        break;

    }

  }


  if ( _cmd ) { /* the command was found */
    _cmd->argc = argc;
    _cmd->answer[ 0 ] = 0;
    strcpy( _cmd->input, in );
  }


  return _cmd;
}
