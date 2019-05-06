#include "str.h"
#include "types.h"
#include "game.h"
#include "manager.h"
#include "game_rules.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

typedef Id (*get_id_proto)( void* );

/*!
* @brief Game structure
*/

struct _Game {
  Player* player; /*!< @brief players in game */
  Die *die; /*!< @brief game's die */
  Object* objects[ MAX_OBJECTS ]; /*!< @brief Objects in game */
  Space* spaces[ MAX_SPACES ]; /*!< @brief Spaces in game */
  Cmd *cmd; /*!< @brief Game commands */
  Link *links[ MAX_LINKS ]; /*!< @brief Links in game */
};

/****** PRIVATE FUNCTIONS ******/

/**
* @brief Informs that command introduced is unknown by the game.
* @param {Game*} - game
*/
void game_callback_unknown( Game *game );


/**
* @brief Defines the next movement to exit.
* @param {Game*} - game
*/
void game_callback_exit( Game *game );


/**
* @brief Sets the player's new position if n or next is introduced by keyboard.
* @param {Game*} - game
*/
void game_callback_next( Game *game );


/**
* @brief Sets the player's new position to the one before current.
* @param {Game*} - game
*/
void game_callback_back( Game *game );


/**
* @brief Asigns a object to a player and removes it from the current cell.
* @param {Game*} - game
*/
void game_callback_take( Game *game );


/**
* @brief Asigns a object to a cell and removes it from the player.
* @param {Game*} - game
*/
void game_callback_drop( Game *game );


/**
* @brief Rolls the die
* @param {Game*} - game
*/
void game_callback_roll( Game *game );


/**
* @brief Moves the player depending on user input
* @param {Game*} - game
*/
void game_callback_move( Game *game );

/**
* @brief Moves player towards left if possible
* @param {Game*} - game
*/
void game_callback_left( Game *game );


/**
* @brief Moves player towards right if possible
* @param {Game*} - game
*/
void game_callback_right( Game *game );

/**
* @brief Shows a help screen
* @param {Game*} - game
*/
void game_callback_help( Game *game );


/**
* @brief Shows info about game elements
* @param {Game*} - game
*/
void game_callback_inspect( Game *game );


/**
* @brief Turns on or off an object
* @param {Game*} - game
*/
void game_callback_turn( Game *game );


/**
* @brief Opens a link
* @param {Game*} - game
*/
void game_callback_open( Game *game );


/**
* @brief Saves into a file the current game status
* @param {Game*} - game
*/
void game_callback_save( Game *game );


/**
* @brief Load game data from command line
* @param {Game*} - game
*/
void game_callback_load( Game *game );

/*******************************/


Game* game_create() {

  int i;
  Game *game;

  game = (Game*) malloc( sizeof( Game ) );

  for ( i=0; i < MAX_SPACES; i++ ) {
    game->spaces[ i ] = NULL;
  }

  for ( i=0; i < MAX_OBJECTS; i++ ) {
    game->objects[ i ] = NULL;
  }

  for ( i=0; i < MAX_LINKS; i++ ) {
    game->links[ i ] = NULL;
  }

  game->cmd = NULL;
  game->player = NULL;
  game->die = NULL;

  /* set up command interface */
  cmd_build( UNKNOWN, "unknown", "unknown", (cmd_fn)game_callback_unknown );
  cmd_build( TAKE, "take", "t", (cmd_fn)game_callback_take );
  cmd_build( DROP, "drop", "d", (cmd_fn)game_callback_drop );
  cmd_build( NEXT, "next", "n", (cmd_fn)game_callback_next );
  cmd_build( BACK, "back", "b", (cmd_fn)game_callback_back );
  cmd_build( EXIT, "exit", "e", (cmd_fn)game_callback_exit );
  cmd_build( LEFT, "left", "l", (cmd_fn)game_callback_left );
  cmd_build( ROLL, "roll", "rl", (cmd_fn)game_callback_roll );
  cmd_build( MOVE, "move", "m", (cmd_fn)game_callback_move );
  cmd_build( RIGHT, "right", "r", (cmd_fn)game_callback_right );
  cmd_build( INSPECT, "inspect", "i", (cmd_fn)game_callback_inspect );
  cmd_build( HELP, "help", "h", (cmd_fn)game_callback_help );
  cmd_build( TURN, "turn", "trn", (cmd_fn)game_callback_turn );
  cmd_build( OPEN, "open", "o", (cmd_fn)game_callback_open );
  cmd_build( SAVE, "save", "s", (cmd_fn)game_callback_save );
  cmd_build( LOAD, "load", "ld", (cmd_fn)game_callback_load );

  return game;
}

STATUS game_load_from_file( Game *game, char *f_name ) {

  int errc = 0;

  errc+=manager_load( game, f_name, _RD_SPACES );
  errc+=manager_load( game, f_name, _RD_OBJS );
  errc+=manager_load( game, f_name, _RD_LINKS );
  errc+=manager_load( game, f_name, _RD_PLAYERS );

  return errc ? ERROR : OK;
}

STATUS game_clean( Game *game ) {

  int i;

  if ( !game )
    return ERROR;

  /* clean spaces */
  for ( i=0; i < MAX_SPACES; i++ ) {
    space_destroy( game->spaces[ i ] );
    game->spaces[ i ] = NULL;
  }

  /* clean objects */
  for ( i=0; i < MAX_OBJECTS; i++ ) {
    obj_destroy( game->objects[ i ] );
    game->objects[ i ] = NULL;
  }

  /* clean links */
  for (i=0; i < MAX_LINKS; i++ ) {
    link_destroy( game->links[ i ] );
    game->links[ i ] = NULL;
  }

  /* destroy player */
  player_destroy( game->player );
  game->player = NULL;
  game->die = NULL;

  return OK;

}

STATUS game_destroy( Game *game ) {

  if ( !game )
    return ERROR;

  game_clean( game );

  /* destroy commands */
  cmd_free();

  free( game );

  return OK;
}


/******************************** ADDERS ********************************/

STATUS game_add( Game *game, int max, void *__arr, void *vp, get_id_proto gid ) {

  int i, to = -1;
  STATUS sts;

  sts = OK;

  if ( !game || !__arr || !vp )
    return ERROR;

  for ( i=0; i < max; i++ ) {

    if ( gid( ((void**)__arr)[ i ] ) == gid( vp ) ) {
      sts = ERROR;
      break;
    }

    if ( to == -1 && ((void**)__arr)[ i ] == NULL ) to = i;
  }

  if ( to > -1 && sts == OK ) {
    ((void**)__arr)[ to ] = vp;
  } else {
    sts = ERROR;
  }

  return sts;

}

STATUS game_add_space( Game *game, Space *sp ) {

  if ( !game || !sp )
    return ERROR;

  return game_add( game, MAX_SPACES, game->spaces, sp, (get_id_proto)space_get_id );
}

STATUS game_add_object( Game *game, Object *obj ) {

  if ( !game || !obj )
    return ERROR;

  return game_add( game, MAX_OBJECTS, game->objects, obj, (get_id_proto)obj_get_id );

}

STATUS game_add_link( Game *game, Link *ln ) {

  if ( !game || !ln )
    return ERROR;

  return game_add( game, MAX_LINKS, game->links, ln, (get_id_proto)link_get_id );

}

/*************************************************************************/




/******************************** GETTERS ********************************/

Space* game_get_space( Game *game, Id id ) {

  int i;

  if ( id == NO_ID )
    return NULL;

  for (i=0; i < MAX_SPACES && game->spaces[ i ] != NULL; i++) {
    if ( id == space_get_id( game->spaces[ i ] ) ) {
      return game->spaces[i];
    }
  }

  return NULL;
}

void game_get( Game *game, int items, int max, void *__arr, int *total ) {

  int i, j, top=0;
  void **its, *it;

  if ( !game || !__arr || !total )
    return;

  switch ( items ) {
    case GAME_SPACES:
      top = MAX_SPACES;
      its = (void**)game->spaces;
      break;
    case GAME_LINKS:
      top = MAX_LINKS;
      its = (void**)game->links;
      break;
    case GAME_OBJECTS:
      top = MAX_OBJECTS;
      its = (void**)game->objects;
      break;
  }

  for ( i=0, j=0; i < top; i++ ) {

    it = its[ i ];
    if ( !it ) continue;
    if ( j >= max ) break;
    ((void**)__arr)[ j ] = it;
    j++;

  }

  *total = j;

}

void game_get_spaces( Game *game, int max, Space **spaces, int *total ) {
  game_get( game, GAME_SPACES, max, spaces, total );
}

void game_get_objects( Game *game, int max, Object **objs, int *total ) {
  game_get( game, GAME_OBJECTS, max, objs, total );
}

void game_get_links( Game *game, int max, Link **links, int *total ) {
  game_get( game, GAME_LINKS, max, links, total );
}

Space* game_get_object_space( Game *game, Id id ) {

  int i;
  Space *sp;

  if ( !game )
    return NULL;

  for ( i=0; i < MAX_SPACES; i++ ) {
    sp = game->spaces[ i ];
    if ( space_has_object( sp, id ) ) {
      return sp;
    }
  }

  return NULL;
}

Space *game_get_last_space( Game *game ) {
  int i;
  if ( !game )
    return NULL;

  for ( i=0; i < MAX_SPACES; i++ ) {
    if ( !game->spaces[ i ] && i )
      return game->spaces[ i-1 ];
  }

  return NULL;
}

Space *game_get_first_space( Game *game ) {

  if ( !game )
    return NULL;

  return game->spaces[ 0 ];
}


Player* game_get_player( Game *game ) {
  if ( !game )
    return NULL;
  return game->player;
}


Die* game_get_die( Game *game ){
  if (!game) {
    return NULL;
  }
  return game->die;
}

Cmd* game_get_cmd( Game *game ){
  if (!game) {
    return NULL;
  }
  return game->cmd;
}

Object* game_get_object_by_name( Game *game, const char *name ) {

  int i;
  Object *obj;

  if ( !game || !name )
    return NULL;

  for (i=0; i < MAX_OBJECTS; i++) {
    obj = game->objects[ i ];
    if ( !obj ) continue;
    if ( !strcmp( obj_get_name( obj ), name ) ) {
      return obj;
    }
  }

  return NULL;

}

Object* game_get_object_by_idx( Game *game, int idx ) {

  if ( !game )
    return NULL;

  if ( idx < 0 || idx >= MAX_OBJECTS )
    return NULL;

  return game->objects[ idx ];
}

Object* game_get_object_by_id( Game *game, Id id ) {

  int i;
  Object *obj;

  if ( !game || id == NO_ID )
    return NULL;

  for (i=0; i < MAX_OBJECTS; i++) {
    obj = game->objects[ i ];
    if ( !obj ) continue;
    if ( id == obj_get_id( obj ) ) {
      return obj;
    }
  }

  return NULL;
}


Link* game_get_link_by_id( Game *game, Id id ) {

  int i;
  Link *ln;

  if ( !game || id == NO_ID )
    return NULL;

  for (i=0; i < MAX_LINKS; i++) {
    ln = game->links[ i ];
    if ( !ln ) continue;
    if ( id == link_get_id( ln ) ) {
      return ln;
    }
  }

  return NULL;
}

/*************************************************************************/




/******************************** SETTERS ********************************/

STATUS game_set_player( Game *game, Player *player ){
  if ( !player || !game )
    return ERROR;

  game->player = player;

  return OK;
}

void game_set_die( Game *game, Die *d ) {

  if ( !game || !d )
    return;

  game->die = d;

}

/*************************************************************************/



STATUS game_update( Game *game, Cmd *cmd ) {

  game->cmd = cmd;

  if ( cmd ) {
    cmd_cb( cmd, game );
  }

  return OK;
}

bool game_is_over(Game *game) { return false; }

void game_callback_unknown( Game *game ) {
  cmd_set_ans( game->cmd, 0, "unknown command" );
}

void game_callback_exit( Game *game ) {
  cmd_set_ans( game->cmd, 0, "exit success" );
}


void game_callback_inspect( Game *game ) {

  Cmd *cmd;
  Id p_loc;
  Player *player;
  Space *cu_sp;
  char *opt;
  Object *obj;

  if ( !game )
    return;

  cmd = game_get_cmd( game );
  player = game_get_player( game );
  p_loc = player_get_location( player );
  cu_sp = game_get_space( game, p_loc );

  if ( cmd_get_argc( cmd ) > 1 ) {

    opt = (char*)cmd_get_argv( cmd, 1 );

    if ( !strcmp( "-o", opt ) ) {

      if ( cmd_get_argc( cmd ) == 3 ) {

        obj = game_get_object_by_name( game, cmd_get_argv( cmd, 2 ) );

        if ( obj ) {
          game_inspect_object( game, obj );
          cmd_set_ans( cmd, 0, "inspecting object '%s' ...", cmd_get_argv( cmd, 2 ) );
        } else {
          cmd_set_ans( cmd, 1, "object '%s' not exists", cmd_get_argv( cmd, 2 ) );
        }

      } else {
        cmd_set_ans( cmd, 1, "expected object name" );
      }

    } else if ( !strcmp( "-s", opt ) ) {
      game_inspect_space( game, cu_sp );
      cmd_set_ans( cmd, 0, "inspecting current space ..." );
    } else {
      cmd_set_ans( cmd, 1, "invalid argument key" );
    }

  } else {
    cmd_set_ans( cmd, 1, "too few args" );
  }


}

void game_callback_help( Game *game ) { }

void game_callback_next( Game *game ) {

  Space *sp;
  Player *player;
  Id go_to = NO_ID;
  Cmd *cmd = game->cmd;

  if ( !game )
    return;

  player = game_get_player( game );
  go_to = player_get_location( player );

  if ( cmd_get_argc( cmd ) == 2 ) {
    go_to+=atoi( cmd_get_argv( cmd, 1 ) );
  } else {
    go_to++;
  }

  sp = game_get_space( game, go_to );

  if ( sp ) {
    player_set_location( player, go_to );
    cmd_set_ans( cmd, 0, "going to: S%ld", go_to );
  } else {
    cmd_set_ans( cmd, 1, "could not move down" );
  }

}

void game_callback_back( Game *game ) {

  Space *sp;
  Player *player;
  Id go_to = NO_ID;
  Cmd *cmd = game->cmd;

  if ( !game )
    return;

  player = game_get_player( game );
  go_to = player_get_location( player );

  if ( cmd_get_argc( cmd ) == 2 ) {
    go_to-=atoi( cmd_get_argv( cmd, 1 ) );
  } else {
    go_to--;
  }

  sp = game_get_space( game, go_to );

  if ( sp ) {
    player_set_location( player, go_to );
    cmd_set_ans( cmd, 0, "going to: S%ld", go_to );
  } else {
    cmd_set_ans( cmd, 1, "could not move up" );
  }
}

void game_callback_take( Game *game ) {

  Cmd *cmd;
  Object *obj;
  char *_arg;
  RuleAns ans;

  if ( !game )
    return;

  cmd = game->cmd;

  obj = NULL;
  _arg = NULL;

  if ( cmd_get_argc( cmd ) == 2 ) {

    _arg = (char*)cmd_get_argv( cmd, 1 );
    obj = game_get_object_by_name( game, _arg );

    if ( !obj ) {
      obj = game_get_object_by_id( game, atol( _arg ) );
    }

    if ( obj ) {

      ans = game_player_take_object( game, obj );

      if ( ans == _OBJ_TAKEN ) {
        cmd_set_ans( cmd, 2, "already taken: '%s'", obj_get_name( obj ) );
      } else if ( ans == _OBJ_NOT_IN_SPACE ) {
        cmd_set_ans( cmd, _OBJ_NOT_IN_SPACE, "object '%s' was not found on this space", obj_get_name( obj ) );
      } else if ( ans == _BAG_IS_FULL ) {
        cmd_set_ans( cmd, _BAG_IS_FULL, "bag is full" );
      } else if ( ans == _OBJ_IMMOVABLE ) {
        cmd_set_ans( cmd, 1, "object '%s' can't be moved!", obj_get_name( obj ) );
      } else if ( ans == _TAKE_SUCCESS ) {
        cmd_set_ans( cmd, _TAKE_SUCCESS, "taking: '%s'", obj_get_name( obj ) );
      }

    } else {
      cmd_set_ans( cmd, 1, "object '%s' does not exists", _arg );
    }

  } else {
    cmd_set_ans( cmd, 1, "invalid args" );
  }

  return;
}

void game_callback_drop( Game *game ) {

  Object *obj;
  char *_arg;
  Cmd *cmd;
  RuleAns ans;

  if ( !game )
    return;

  cmd = game->cmd;

  obj = NULL;
  _arg = NULL;

  if ( cmd_get_argc( cmd ) == 2 ) {

    _arg = (char*)cmd_get_argv( cmd, 1 );
    obj = game_get_object_by_name( game, _arg );

    if ( !obj ) {
      obj = game_get_object_by_id( game, atol( _arg ) );
    }

    if ( obj ) {

      ans = game_player_drop_object( game, obj );

      if ( ans == _OBJ_NOT_IN_BAG ) {
        cmd_set_ans( cmd, _OBJ_NOT_IN_BAG, "'%s': not in bag", obj_get_name( obj ) );
      } else if ( ans == _DROP_SUCCESS ) {
        cmd_set_ans( cmd, _DROP_SUCCESS, "dropping: '%s'", obj_get_name( obj) );
      } else if ( ans == _RULE_ERROR ) {
        cmd_set_ans( cmd, _RULE_ERROR, "could not drop" );
      }

    } else {
      cmd_set_ans( cmd, 1, "object '%s' does not exits", _arg );
    }

  } else {
    cmd_set_ans( cmd, 1, "invalid args" );
  }

  return;
}

void game_callback_roll( Game *game ) {
  int n;
  n = die_roll( game->die );
  cmd_set_ans( game->cmd, 0, "%d", n );
}


void game_callback_move( Game *game ) {

  Cmd *cmd;
  Link *ln;
  Object *obj;
  Player *player;
  Space *cu_sp, *to_sp;
  Id tid, go_to = NO_ID, ln_id = NO_ID;
  char *cp = NULL; /* cardinal point */

  if ( !game )
    return;

  cmd = game->cmd;
  cp = (char*)cmd_get_argv( cmd, 1 );
  cu_sp = game_get_space( game, player_get_location( game->player ) );
  player = game_get_player( game );

  if ( cp ) {

    if ( !strcmptok( cp, "north,n,N", "," ) ) {
      ln_id = space_get_link( cu_sp, N );
    } else if ( !strcmptok( cp, "east,e,E", "," ) ) {
      ln_id = space_get_link( cu_sp, E );
    } else if ( !strcmptok( cp, "south,s,S", "," ) ) {
      ln_id = space_get_link( cu_sp, S );
    } else if ( !strcmptok( cp, "west,w,W", "," ) ) {
      ln_id = space_get_link( cu_sp, W );
    } else if ( !strcmptok( cp, "down,d,D", "," ) ) {
      ln_id = space_get_link( cu_sp, D );
    } else if ( !strcmptok( cp, "up,u,U", "," ) ) {
      ln_id = space_get_link( cu_sp, U );
    } else {
      cmd_set_ans( cmd, 1, "'%s': invalid cardinal point", cp );
      return;
    }

    ln = game_get_link_by_id( game, ln_id );

    if ( ln && link_get_state( ln ) == LINK_OPENED ) {

      go_to = link_get_to( ln );
      to_sp = game_get_space( game, go_to );

      player_set_location( game->player, go_to );
      space_set_light( cu_sp, false );

      obj = game_get_object_by_name( game, "torch" );
      tid = obj_get_id( obj );

      if ( player_has_object( player, tid ) && obj_get_attr( obj, OBJ_IS_ON ) == OBJ_YES ) {
        space_set_light( to_sp, true );
      }

      cmd_set_ans( cmd, 0, "going to: S%ld", go_to );

    } else if ( ln && link_get_state( ln ) == LINK_CLOSED ) {
      cmd_set_ans( cmd, 1, "link is closed" );
    } else {
      cmd_set_ans( cmd, 1, "invalid move" );
    }

  } else {
    cmd_set_ans( cmd, 1, "invalid args" );
  }


}


void game_callback_left( Game *game ){

  Cmd *cmd;
  Link *ln;
  Space *space;
  char buff[100];
  Id go_to = NO_ID;
  int err = 0;

  if ( !game )
    return;

  cmd = game->cmd;
  space = game_get_space( game, player_get_location( game->player ) );
  ln = game_get_link_by_id( game, space_get_link( space, W ) );
  go_to = link_get_to( ln );

  if (go_to == NO_ID) {
    sprintf( buff, "%s", "no west" );
    err = 1;
  } else {
    err = 0;
    sprintf( buff, "joining: %ld", go_to );
    player_set_location( game->player, go_to );
  }

  cmd_set_ans( cmd, err, "%s", buff );

}

void game_callback_right( Game *game ) {

  Cmd *cmd;
  Link *ln;
  Space *space;
  char buff[100];
  Id go_to = NO_ID;
  int err = 0;

  if ( !game )
    return;

  cmd = game->cmd;
  space = game_get_space( game, player_get_location( game->player ) );
  ln = game_get_link_by_id( game, space_get_link( space, E ) );
  go_to = link_get_to( ln );

  if (go_to == NO_ID) {
    err = 1;
    sprintf( buff, "%s", "no east" );
  } else {
    err = 0;
    sprintf( buff, "joining: %ld", go_to );
    player_set_location( game->player, go_to );
  }

  cmd_set_ans( cmd, err, "%s", buff );

}

void game_callback_turn( Game *game ){

  Cmd *cmd;
  Object *obj;
  char *sts; /* on or off arg */
  char *name; /* object name */
  RuleAns ans;
  bool onff;

  if( !game )
    return;

  cmd = game->cmd;
  ans = _RULE_ERROR;

  if ( cmd_get_argc( cmd ) > 2 ) {

    sts = (char*)cmd_get_argv( cmd, 1 );
    name = (char*)cmd_get_argv( cmd, 2 );

    obj = game_get_object_by_name( game, name );

    if ( obj ) {

      if ( !strcmptok( sts, "on,ON", "," ) ) {
        ans = game_obj_set_on( game, obj, OBJ_YES );
        onff = true;
      } else if ( !strcmptok( sts, "off,OFF", "," ) ) {
        ans = game_obj_set_on( game, obj, OBJ_NO );
        onff = false;
      } else {
        cmd_set_ans( cmd, 1, "invalid status flag" );
      }

      if ( ans == _OBJ_NOT_IN_BAG ) {
        cmd_set_ans( cmd, _OBJ_NOT_IN_BAG, "object '%s' not in bag", name );
      } else if ( ans == _OBJ_CAN_NOT_ILLUMINATE ) {
        cmd_set_ans( cmd, _OBJ_CAN_NOT_ILLUMINATE, "object '%s' can not illuminate", name );
      } else if ( ans == _TURN_SUCCESS ) {
        if ( onff ) {
          cmd_set_ans( cmd, _TURN_SUCCESS, "turning ON '%s'", name );
        } else {
          cmd_set_ans( cmd, _TURN_SUCCESS, "turning OFF '%s'", name );
        }
      }

    } else {
      cmd_set_ans( cmd, 1, "object '%s' does not exists", name );
    }

  } else {
    cmd_set_ans( cmd, 1, "too few args" );
  }

}

void game_callback_open( Game *game ){

  Cmd *cmd;
  Object *obj; /* object */
  Link *ln; /* link */
  Id ln_id; /* link id */
  char *obj_name; /* object name */
  char *arg; /* temporary argument */
  RuleAns ans; /* rule answer */

  if( !game )
    return;

  cmd = game->cmd;

  if ( cmd_get_argc( cmd ) > 3 ) {

    arg = (char*)cmd_get_argv( cmd, 2 );

    if ( !strcmp( arg, "with" ) ) {

      ln_id = atol( (char*)cmd_get_argv( cmd, 1 ) );
      obj_name = (char*)cmd_get_argv( cmd, 3 );

      obj = game_get_object_by_name( game, obj_name );
      ln = game_get_link_by_id( game, ln_id );

      if ( !ln ) {
        cmd_set_ans( cmd, 1, "link '%s' does not exists", cmd_get_argv( cmd, 1 ) );
      } else if ( !obj ) {
        cmd_set_ans( cmd, 1, "object '%s' does not exists", obj_name );
      } else {
        ans = game_open_link_with_obj( game, ln, obj );

        if ( ans == _OBJ_NOT_IN_BAG ) {
          cmd_set_ans( cmd, 1, "object '%s' not in bag", obj_get_name( obj ) );
        } else if ( ans == _OBJ_CAN_NOT_OPEN_LINK ) {
          cmd_set_ans( cmd, 1, "object '%s' can't open '%s' ", obj_get_name( obj ), link_get_name( ln ) );
        } else if ( ans == _OBJ_IS_OUTWORN ) {
          cmd_set_ans( cmd, 1, "you can't use '%s' any more", obj_get_name( obj ) );
        } else if ( ans == _OPEN_SUCCESS ) {
          cmd_set_ans( cmd, 0, "link '%s' was opened", link_get_name( ln ) );
        }

      }

    } else {
      cmd_set_ans( cmd, 1, "unknown option '%s'", arg );
    }

  } else {
    cmd_set_ans( cmd, 1, "too few args" );
  }

}

void game_callback_save( Game *game ) {

  FILE *f;
  Cmd *cmd;
  time_t rawtime;
  struct tm *tinfo;
  char _buff[ 256 ];

  if ( !game )
    return;

  cmd = game_get_cmd( game );

  if ( cmd_get_argc( cmd ) == 1 ) {

    time( &rawtime );
    tinfo = localtime( &rawtime );

    sprintf( _buff, "save_%d%02d%02d_%02d%02d.dat", tinfo->tm_year + 1900, tinfo->tm_mday, tinfo->tm_mon, tinfo->tm_hour, tinfo->tm_min );
    manager_save( game, _buff );

    cmd_set_ans( cmd, 0, "file saved: '%s'", _buff );

  } else if ( cmd_get_argc( cmd ) == 2 ) {

    sprintf( _buff, "%s", cmd_get_argv( cmd, 1 ) );
    f = fopen( _buff, "r" );

    if ( f ) {
      cmd_set_ans( cmd, 1, "file '%s' already exists", _buff );
      fclose( f );
    } else {
      manager_save( game, _buff );
      cmd_set_ans( cmd, 0, "file saved: '%s'", _buff );
    }

  } else {
    cmd_set_ans( cmd, 1, "invalid args" );
  }

}

void game_callback_load( Game *game ) {

  FILE *f;
  Cmd *cmd;
  char *f_name;

  if ( !game )
    return;

  cmd = game_get_cmd( game );

  if ( cmd_get_argc( cmd ) == 2 ) {

    f_name = (char*)cmd_get_argv( cmd, 1 );
    f = fopen( f_name, "r" );

    if ( f ) {
      fclose( f );

      game_clean( game );

      if ( game_load_from_file( game, f_name ) == OK ) {
        cmd_set_ans( cmd, 0, "data was loaded correctly" );
      } else {
        cmd_set_ans( cmd, 1, "error while loading data" );
      }
    } else {
      cmd_set_ans( cmd, 1, "file '%s' does not exists", f_name );
    }

  } else {
    cmd_set_ans( cmd, 1, "invalid args" );
  }

}
