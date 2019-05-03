#ifndef GAME_RULES
#define GAME_RULES

#include "game.h"

STATUS game_player_take_object( Game *game, Object *obj );
STATUS game_player_drop_object( Game *game, Object *obj );
STATUS game_obj_set_on( Game *game, Object *obj, long sts );
STATUS game_open_link_with_obj( Game *game, Link *ln, Object *obj );

#endif
