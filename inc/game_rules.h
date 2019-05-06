#ifndef GAME_RULES
#define GAME_RULES

#include "game.h"

typedef enum _RuleAns {
  _BAG_IS_FULL, /*!< Rule to check if the bag is full */
  _OBJ_NOT_EXISTS, /*!< Rule to check if an object does not exists */
  _OBJ_NOT_IN_BAG, /*!< Rule to check if an object is not in the player bag */
  _OBJ_NOT_IN_SPACE, /*!< Rule to check if the object is not in the space */
  _OBJ_IMMOVABLE, /*!< Rule to check if the object can be moved */
  _OBJ_TAKEN, /*!< Rule to check if the object is already taken */
  _OBJ_IS_OUTWORN, /*!< Rule to check if the object can be used any more */
  _OBJ_CAN_NOT_OPEN_LINK, /*!< Rule to check if the object can open a link */
  _OBJ_CAN_NOT_ILLUMINATE, /*!< Rule to check if an object can illuminate */
  _OBJ_NOT_REACHABLE, /*!< Rule to check if the object is not reachble */
  _TAKE_SUCCESS, /*!< Rule to check if take action was success */
  _DROP_SUCCESS, /*!< Rule to check if drop action was success */
  _TURN_SUCCESS, /*!< Rule to check if turn action was success */
  _OPEN_SUCCESS, /*!< Rule to check if open action was success */
  _INSPECT_SUCCESS, /*!< Rule to check if inspect action was success */
  _RULE_ERROR /*!< This indicates an error in the rule process */
} RuleAns;

RuleAns game_inspect_space( Game *game, Space *sp );
RuleAns game_inspect_object( Game *game, Object *obj );
RuleAns game_player_take_object( Game *game, Object *obj );
RuleAns game_player_drop_object( Game *game, Object *obj );
RuleAns game_obj_set_on( Game *game, Object *obj, long sts );
RuleAns game_open_link_with_obj( Game *game, Link *ln, Object *obj );

#endif
