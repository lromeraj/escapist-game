#include "game_rules.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

STATUS game_player_take_object( Game *game, Object *obj ) {

  Cmd *cmd;
  Player *player;
  Space *cu_sp;
  Id oid; /* object id */

  if ( !game || !obj )
    return ERROR;

  cmd = game_get_cmd( game );

  oid = obj_get_id( obj );
  player = game_get_player( game );
  cu_sp = game_get_space( game, player_get_location( player ) );

  if ( !space_has_object( cu_sp, oid ) ) {
    cmd_set_ans( cmd, 2, "object '%s' was not found on this space", obj_get_name( obj ) );
  } else if ( player_has_object( player, oid ) ) {
    cmd_set_ans( cmd, 2, "taken: '%s'", obj_get_name( obj ), oid );
  } else {

    if ( obj_get_attr( obj, OBJ_IS_MOVABLE ) == OBJ_YES ) {

      if ( player_add_object( player, oid ) == OK ) {
        space_del_object( cu_sp, oid );
        obj_set_attr( obj, OBJ_IS_MOVED, OBJ_YES );
        cmd_set_ans( cmd, 0, "taking: '%s'", obj_get_name( obj ), oid );
      } else {
        cmd_set_ans( cmd, 1, "bag is full" );
      }

    } else {
      cmd_set_ans( cmd, 1, "object '%s' can't be taken!", obj_get_name( obj ) );
    }

  }

  return ERROR;
}

STATUS game_obj_set_on( Game *game, Object *obj, long sts ) {

  Player *player;
  Space *cu_sp;
  Id  p_loc; /* player location */

  if ( !game || !obj )
    return ERROR;

  player = game_get_player( game );
  p_loc = player_get_location( player );
  cu_sp = game_get_space( game, p_loc );

  if ( obj_get_attr( obj, OBJ_CAN_ILLUMINATE ) == OBJ_YES ) {
    space_set_light( cu_sp, sts == OBJ_YES ? true : false );
    obj_set_attr( obj, OBJ_IS_ON, sts );
  }

  return OK;
}

STATUS game_player_drop_object( Game *game, Object *obj ) {

  Cmd *cmd;
  Player *player;
  Space *cu_sp;
  Id  p_loc, /* player location */
      oid; /* object id */

  if ( !game || !obj )
    return ERROR;

  cmd = game_get_cmd( game );

  oid = obj_get_id( obj );
  player = game_get_player( game );
  p_loc = player_get_location( player );
  cu_sp = game_get_space( game, p_loc );

  if ( !player_has_object( player, oid ) ) {
    cmd_set_ans( cmd, 1, "'%s': not in bag", obj_get_name( obj ) );
  } else {

    if ( space_add_object( cu_sp, oid ) == OK ) {

      game_obj_set_on( game, obj, OBJ_NO );

      player_del_object( player, oid );
      cmd_set_ans( cmd, 0, "dropping: '%s'", obj_get_name( obj) );
    } else {
      cmd_set_ans( cmd, 1, "could not drop" );
    }
  }

  return ERROR;
}

STATUS game_open_link_with_obj( Game *game, Link *ln, Object *obj ) {

  Cmd *cmd;
  Player *player;
  Id oid, lid;
  long used, max_uses;

  if ( !game || !ln || !obj )
    return ERROR;

  cmd = game_get_cmd( game );
  player = game_get_player( game );
  oid = obj_get_id( obj );
  lid = link_get_id( ln );

  if ( player_has_object( player, oid ) ) {

    if ( obj_opens_link( obj, lid ) ) {
      used = obj_get_attr( obj, OBJ_USED );
      max_uses = obj_get_attr( obj, OBJ_MAX_USES );

      if ( used < max_uses ) {
        link_set_state( ln, LINK_OPENED );
        obj_set_attr( obj, OBJ_USED, used + 1 );
        cmd_set_ans( cmd, 0, "link '%s' was opened", link_get_name( ln ) );
      } else {
        cmd_set_ans( cmd, 1, "you can't use '%s' any more", obj_get_name( obj ) );
      }

    } else {
      cmd_set_ans( cmd, 1, "object '%s' can't open '%s' ", obj_get_name( obj ), link_get_name( ln ) );
    }

  } else {
    cmd_set_ans( cmd, 1, "object '%s' not in bag", obj_get_name( obj ) );
  }

  return OK;

}
