#include "types.h"
#include "game.h"
#include "reader.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

struct _Game {
  Player* player;
  Die *die;
  Object* objects[ MAX_OBJECTS ];
  Space* spaces[ MAX_SPACES + 1 ];
  Cmd *cmd;
};

/****** PRIVATE FUNCTIONS ******/

/**
* @name game_callback_unknown
* @brief informs that command introduced is unknown by the game.
*
* @param {Game*} - game;
* @return {void} - Do not return nothing;
*/
void game_callback_unknown( Game *game );

/**
* @name game_callback_exit
* @brief defines the next movement to exit.
*
* @param {Game*} - game;
* @return {void} - Do not return nothing;
*/
void game_callback_exit( Game *game );

/**
* @name game_callback_next
* @brief sets the player's new position if n or next is introduced by keyboard.
*
* @param {Game*} - game;
* @return {void} - Do not return nothing;
*/
void game_callback_next( Game *game );

/**
* @name game_callback_back
* @brief sets the player's new position to the one before current.
*
* @param {Game*} - game;
* @return {void} - Do not return nothing;
*/
void game_callback_back( Game *game );

/**
* @name game_callback_take
* @brief asigns a object to a player and removes it from the current cell.
*
* @param {Game*} - game;
* @return {void} - Do not return nothing;
*/
void game_callback_take( Game *game );

/**
* @name game_callback_drop
* @brief asigns a object to a cell and removes it from the player.
*
* @param {Game*} - game;
* @return {void} - Do not return nothing;
*/

void game_callback_drop( Game *game );

/**
* @name game_callback_roll
* @brief rolls the die
*
* @param {Game*} - game;
* @return {void} - Do not return nothing;
*/

void game_callback_roll( Game *game );

/**
* @name game_callback_left
* @brief moves player towards left if possible
*
* @param {Game*} - game;
* @return {void} - Do not return nothing;
*/

void game_callback_left( Game *game );

/**
* @name game_callback_right
* @brief moves player towards right if possible
*
* @param {Game*} - game;
* @return {void} - Do not return nothing;
*/

void game_callback_right( Game *game );

/**************************************************/

/**
* @name game_get_space_id
* @brief gets the id of an space cell.
*
* @param {Game*} - game, {int} - position;
* @return {Id} - Returns an Id;
*/

Id game_get_space_id_at(Game *game, int position);

/**************************************************/

Game* game_create() {

  int i;
  Die *die;
  Game *game;
  Player *player;

  game = (Game*)malloc(sizeof(Game));

  for ( i=0; i < MAX_SPACES; i++ ) {
    game->spaces[ i ] = NULL;
  }

  for ( i=0; i < MAX_OBJECTS; i++ ) {
    game->objects[ i ] = NULL;
  }

  game->cmd = NULL;
  game->player = NULL;
  game->die = NULL;

  /* load player */
  player = player_init();

  player_set_id( player, 1 );
  player_set_name( player, "player1" );
  player_set_location( player, 1 );

  game_set_player( game, player );

  /* load dice */
  die = die_init();
  game_set_die( game, die );

  /* set up commands */
  cmd_set( UNKNOWN, "unknown", "unknown", (cmd_fn)game_callback_unknown );
  cmd_set( TAKE, "take", "t", (cmd_fn)game_callback_take );
  cmd_set( DROP, "drop", "d", (cmd_fn)game_callback_drop );
  cmd_set( NEXT, "next", "n", (cmd_fn)game_callback_next );
  cmd_set( BACK, "back", "b", (cmd_fn)game_callback_back );
  cmd_set( EXIT, "exit", "e", (cmd_fn)game_callback_exit );
  cmd_set( ROLL, "roll", "rl", (cmd_fn)game_callback_roll );
  cmd_set( LEFT, "left", "l", (cmd_fn)game_callback_left );
  cmd_set( RIGHT, "right", "r", (cmd_fn)game_callback_right );

  return game;
}

STATUS game_create_from_file( Game *game, char *filename ) {

  if (reader_load_spaces( game, filename ) == ERROR)
    return ERROR;

  if (reader_load_objects( game, filename ) == ERROR)
    return ERROR;

  return OK;
}

STATUS game_destroy(Game *game) {

  int i;

  if ( !game )
    return ERROR;

  /* clean spaces */
  for (i=0; (i < MAX_SPACES) && (game->spaces[ i ] != NULL); i++) {
    space_destroy( game->spaces[ i ] );
  }

  /* clean objects */
  for (i=0; (i < MAX_OBJECTS) && (game->objects[ i ] != NULL); i++ ) {
    obj_destroy( game->objects[ i ] );
  }

  /* destroy die */
  die_destroy( game->die );

  /* destroy player */
  player_destroy( game->player );

  /* destroy commands */
  cmd_free();

  free( game );

  return OK;
}

STATUS game_add_space( Game *game, Space *space ) {

  int i;
  static int idx = 0;

  if ( !game || !space )
    return ERROR;

  for ( i = 0; i < MAX_SPACES; i++ ) {
    if ( space_get_id( game->spaces[ i ] ) == space_get_id( space ) ) {
      return ERROR;
    }
  }

  game->spaces[ idx ] = space;
  idx++;

  return OK;
}

Id game_get_space_id_at( Game *game, int idx ) {

  if ( idx < 0 || idx >= MAX_SPACES) {
    return NO_ID;
  }

  return space_get_id( game->spaces[ idx ] );
}

Space *game_get_space( Game *game, Id id ) {

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

Player* game_get_player( Game *game ) {
  if ( !game )
    return NULL;
  return game->player;
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

STATUS game_set_object( Game *game, Object *obj ) {

  int i;
  static int idx = 0;

  if ( !obj || !game )
    return ERROR;

  if ( idx >= MAX_OBJECTS )
    return ERROR;

  for ( i=0; i < MAX_OBJECTS; i++ ) {
    if ( obj_get_id( game->objects[ i ] ) == obj_get_id( obj ) )
      return ERROR;
  }

  game->objects[ idx ] = obj;
  idx++;

  return OK;
}

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

Die *game_get_die( Game *game ){
  if (!game) {
    return NULL;
  }
  return game->die;
}

Cmd *game_get_cmd( Game *game ){
  if (!game) {
    return NULL;
  }
  return game->cmd;
}

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
    cmd_set_ans( cmd, 0, "going to: C%ld", go_to );
  } else {
    cmd_set_ans( cmd, 1, "could not move", go_to );
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
    cmd_set_ans( cmd, 0, "going to: C%ld", go_to );
  } else {
    cmd_set_ans( cmd, 1, "could not move", go_to );
  }
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


Object **game_get_objects( Game *game ) {

  if (!game)
    return NULL;

  return game->objects;
}

void game_callback_take( Game *game ) {

  Space *sp;
  Player *player;
  Object *obj;
  Id p_loc, o_id;
  char *o_name, *_arg;
  Cmd *cmd;

  if ( !game )
    return;

  cmd = game->cmd;
  player = game_get_player( game );
  p_loc = player_get_location( player );
  sp = game_get_space( game, p_loc );

  if ( !sp )
    return;

  obj = NULL;
  _arg = NULL;
  o_name = NULL;

  if ( cmd_get_argc( cmd ) == 2 ) {

    _arg = (char*)cmd_get_argv( cmd, 1 );
    obj = game_get_object_by_name( game, _arg );

  } else if ( cmd_get_argc( cmd ) == 3 ) {

    _arg = (char*)cmd_get_argv( cmd, 2 );

    if ( !strcmp( cmd_get_argv( cmd, 1 ), "-i" ) ) {
      obj = game_get_object_by_id( game, atol( _arg ) );
    } else if ( !strcmp( cmd_get_argv( cmd, 1 ), "-n" ) ) {
      obj = game_get_object_by_name( game, _arg );
    }

  }

  if ( cmd_get_argc( cmd ) > 1 && _arg ) {

    o_id = obj_get_id( obj );
    o_name = (char*)obj_get_name( obj );

    if ( !space_has_object( sp, o_id ) ) {
      cmd_set_ans( cmd, 2, "'%s': not found", _arg );
    } else if ( player_has_object( player, o_id ) ) {
      cmd_set_ans( cmd, 2, "taken: %s#%ld", o_name, o_id );
    } else {
      player_add_object( player, o_id );
      space_del_object( sp, o_id );
      cmd_set_ans( cmd, 0, "taking: %s#%ld", o_name, o_id );
    }

  } else {
    cmd_set_ans( cmd, 1, "invalid args" );
  }

  return;
}

void game_callback_drop( Game *game ) {

  Player *player;
  Object *obj;
  Id p_loc, o_id;
  char *o_name, *_arg;
  Cmd *cmd;

  if ( !game )
    return;

  cmd = game->cmd;
  player = game_get_player( game );
  p_loc = player_get_location( player );

  obj = NULL;
  _arg = NULL;
  o_name = NULL;

  if ( cmd_get_argc( cmd ) == 2 ) {

    _arg = (char*)cmd_get_argv( cmd, 1 );
    obj = game_get_object_by_name( game, _arg );

  } else if ( cmd_get_argc( cmd ) == 3 ) {

    _arg = (char*)cmd_get_argv( cmd, 2 );

    if ( !strcmp( cmd_get_argv( cmd, 1 ), "-i" ) ) {
      obj = game_get_object_by_id( game, atol( _arg ) );
    } else if ( !strcmp( cmd_get_argv( cmd, 1 ), "-n" ) ) {
      obj = game_get_object_by_name( game, _arg );
    }

  }

  if ( cmd_get_argc( cmd ) > 1 && _arg ) {

    o_id = obj_get_id( obj );
    o_name = (char*)obj_get_name( obj );

    if ( !player_has_object( player, o_id ) ) {
      cmd_set_ans( cmd, 1, "'%s': not taken", _arg );
    } else {
      space_add_object( game_get_space( game, p_loc ), o_id );
      player_del_object( player, o_id );
      cmd_set_ans( cmd, 0, "dropping: %s#%ld in C%ld", o_name, o_id, p_loc );
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

void game_callback_left( Game *game ){

  Cmd *cmd;
  Space *space;
  char buff[100];
  Id go_to = NO_ID;
  int err = 0;

  if ( !game )
    return;

  cmd = game->cmd;
  space = game_get_space( game, player_get_location( game->player ) );
  go_to = space_get_west ( space );

  if (go_to == NO_ID) {
    sprintf( buff, "%s", "no west" );
    err = 1;
  } else {
    err = 0;
    sprintf( buff, "joining: %ld", go_to );
    player_set_location( game->player, go_to );
  }

  cmd_set_ans( cmd, err, buff );

}

void game_callback_right( Game *game ) {

  Cmd *cmd;
  Space *space;
  char buff[100];
  Id go_to = NO_ID;
  int err = 0;

  if ( !game )
    return;
  cmd = game->cmd;
  space = game_get_space( game, player_get_location( game->player ) );
  go_to = space_get_east( space );

  if (go_to == NO_ID) {
    err = 1;
    sprintf( buff, "%s", "no east" );
  } else {
    err = 0;
    sprintf( buff, "joining: %ld", go_to );
    player_set_location( game->player, go_to );
  }

  cmd_set_ans( cmd, err, buff );

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
