#include "game_rules.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

RuleAns game_player_take_object( Game *game, Object *obj ) {

  Player *player;
  Space *cu_sp;
  Id oid; /* object id */
  RuleAns ans;

  ans = _RULE_ERROR;

  if ( !game || !obj )
    return _RULE_ERROR;

  oid = obj_get_id( obj );
  player = game_get_player( game );
  cu_sp = game_get_space( game, player_get_location( player ) );

  if ( !space_has_object( cu_sp, oid ) ) {
    ans = _OBJ_NOT_IN_SPACE;
  } else if ( player_has_object( player, oid ) ) {
    ans = _OBJ_TAKEN;
  } else {

    if ( obj_get_attr( obj, OBJ_IS_MOVABLE ) == OBJ_YES ) {

      if ( obj_get_attr( obj, OBJ_IS_HIDDEN ) == OBJ_YES ) {
        ans = _OBJ_NOT_IN_SPACE;
      } else {

        if ( player_add_object( player, oid ) == OK ) {
          space_del_object( cu_sp, oid );
          obj_set_attr( obj, OBJ_IS_MOVED, OBJ_YES );
          ans = _TAKE_SUCCESS;
        } else {
          ans= _BAG_IS_FULL;
        }

      }

    } else {
      ans = _OBJ_IMMOVABLE;
    }

  }

  return ans;
}

RuleAns game_obj_set_on( Game *game, Object *obj, long sts ) {

  Player *player;
  Space *cu_sp;
  Id  p_loc, oid; /* player location */
  RuleAns ans;

  if ( !game || !obj )
    return _RULE_ERROR;

  player = game_get_player( game );
  p_loc = player_get_location( player );
  cu_sp = game_get_space( game, p_loc );
  oid = obj_get_id( obj );

  if ( player_has_object( player, oid ) ) {

    if ( obj_get_attr( obj, OBJ_CAN_ILLUMINATE ) == OBJ_YES ) {
      space_set_light( cu_sp, sts == OBJ_YES ? true : false );
      obj_set_attr( obj, OBJ_IS_ON, sts );
      ans = _TURN_SUCCESS;
    } else {
      ans = _OBJ_CAN_NOT_ILLUMINATE;
    }

  } else {
    ans = _OBJ_NOT_IN_BAG;
  }

  return ans;
}

RuleAns game_player_drop_object( Game *game, Object *obj ) {

  Player *player;
  Space *cu_sp;
  Id  p_loc, /* player location */
      oid; /* object id */
  RuleAns ans;

  ans = _RULE_ERROR;

  if ( !game || !obj )
    return _RULE_ERROR;

  oid = obj_get_id( obj );
  player = game_get_player( game );
  p_loc = player_get_location( player );
  cu_sp = game_get_space( game, p_loc );

  if ( !player_has_object( player, oid ) ) {
    ans = _OBJ_NOT_IN_BAG;
  } else {

    if ( space_add_object( cu_sp, oid ) == OK ) {
      game_obj_set_on( game, obj, OBJ_NO );
      player_del_object( player, oid );
      ans = _DROP_SUCCESS;
    } else {
      ans = _RULE_ERROR;
    }

  }

  return ans;
}

RuleAns game_inspect_space( Game *game, Space *sp ) {

  RuleAns ans;
  Object *obj;
  int i, total;
  Set *set;
  Id ids[ MAX_SET ];

  if ( !game || !sp )
    return _RULE_ERROR;

  ans = can_show_space_descrp( game );

  if ( ans == _RULE_YES ) {

    set = space_get_objects( sp );
    set_get_ids( set, MAX_SET, ids, &total );

    for ( i=0; i < total; i++ ) { /* unhide all space objects */
      obj = game_get_object_by_id( game, ids[ i ] );
      obj_set_attr( obj, OBJ_IS_HIDDEN, OBJ_NO );
    }

    ans = _INSPECT_SUCCESS;
  }

  return ans;

}


RuleAns game_inspect_object( Game *game, Object *obj ) {

  RuleAns ans;
  Object *book;
  char *o_name, *b_name;

  if ( !game || !obj )
    return _RULE_ERROR;

  book = game_get_object_by_name( game, "book" );

  ans = can_show_object_descrp( game );

  if ( ans == _RULE_YES ) {

    o_name = (char*)obj_get_name( obj );
    b_name = (char*)obj_get_name( book );

    if ( o_name && b_name ) {

      if ( strcmp( o_name, b_name ) ) {
        obj_set_attr( book, OBJ_USED, obj_get_attr( book, OBJ_USED ) + 1 );
      }
    }

    ans = _INSPECT_SUCCESS;
  }

  return ans;

}

RuleAns game_open_link_with_obj( Game *game, Link *ln, Object *obj ) {

  Player *player;
  Id oid, lid;
  long used, max_uses;
  RuleAns ans;

  ans = _RULE_ERROR;

  if ( !game || !ln || !obj )
    return _RULE_ERROR;

  player = game_get_player( game );
  oid = obj_get_id( obj );
  lid = link_get_id( ln );

  if ( player_has_object( player, oid ) ) {

    if ( obj_opens_link( obj, lid ) ) {

      used = obj_get_attr( obj, OBJ_USED );
      max_uses = obj_get_attr( obj, OBJ_MAX_USES );

      if ( used < max_uses || !max_uses ) {
        link_set_state( ln, LINK_OPENED );
        obj_set_attr( obj, OBJ_USED, used + 1 );
        ans = _OPEN_SUCCESS;
      } else {
        ans = _OBJ_IS_OUTWORN;
      }

    } else {
      ans = _OBJ_CAN_NOT_OPEN_LINK;
    }

  } else {
    ans = _OBJ_NOT_IN_BAG;
  }

  return ans;

}


RuleAns can_show_object_descrp( Game *game ) {

  Player *player;
  Object *book;
  RuleAns ans;

  if ( !game )
    return _RULE_ERROR;

  book = game_get_object_by_name( game, "book" );

  ans = _RULE_ERROR;
  player = game_get_player( game );

  if ( player_has_object( player, obj_get_id( book ) ) ) {

    if ( obj_get_attr( book,  OBJ_USED ) < obj_get_attr( book, OBJ_MAX_USES ) ) {
      ans = _RULE_YES;
    } else {
      ans = _OBJ_IS_OUTWORN;
    }

  } else {
    ans = _OBJ_NOT_IN_BAG;
  }

  return ans;

}

RuleAns can_show_space_descrp( Game *game ) {

  Player *player;
  Object *map;
  RuleAns ans;

  if ( !game )
    return _RULE_ERROR;

  map = game_get_object_by_name( game, "map" );

  ans = _RULE_ERROR;
  player = game_get_player( game );

  if ( player_has_object( player, obj_get_id( map ) ) ) {
    ans = _RULE_YES;
  } else {
    ans = _OBJ_NOT_IN_BAG;
  }

  return ans;

}
