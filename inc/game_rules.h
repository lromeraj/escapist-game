#ifndef GAME_RULES
#define GAME_RULES

#include "game.h"

typedef enum _RuleAns {
  _BAG_IS_FULL,
  _OBJ_NOT_EXISTS,
  _OBJ_NOT_IN_BAG,
  _OBJ_NOT_IN_SPACE,
  _OBJ_IMMOVABLE,
  _OBJ_TAKEN,
  _OBJ_IS_OUTWORN,
  _OBJ_CAN_NOT_OPEN_LINK,
  _OBJ_CAN_NOT_ILLUMINATE,
  _OBJ_NOT_REACHABLE,
  _TAKE_SUCCESS,
  _DROP_SUCCESS,
  _TURN_SUCCESS,
  _OPEN_SUCCESS,
  _INSPECT_SUCCESS,
  _RULE_ERROR
} RuleAns;

RuleAns game_inspect_space( Game *game, Space *sp );
RuleAns game_inspect_object( Game *game, Object *obj );
RuleAns game_player_take_object( Game *game, Object *obj );
RuleAns game_player_drop_object( Game *game, Object *obj );
RuleAns game_obj_set_on( Game *game, Object *obj, long sts );
RuleAns game_open_link_with_obj( Game *game, Link *ln, Object *obj );

#endif
