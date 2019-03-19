/**
 * @brief Main player manager
 *
 * @file player.c
 * @author Miguel Rodríguez
 * @version 1.0
 * @date 18/03/2019
 */

#include "player.h"
#include "types.h"
#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
* @brief Player's structure
*
* This structure defines an player whose fields are an id, a name, a location and an inventary of objects
*/
struct _Player {
  Id id;	                   /*!< PLayer's Identifier */
  char name[WORD_SIZE + 1];  /*!< Player's name */
  Id loc;		                 /*!< Player's location */
  Inventory *inv;            /*!< Player's inventory */
};


Player *player_init() {

  Player *newplayer = NULL;

  newplayer = (Player *)malloc(sizeof(Player));

  if ( !newplayer ) {
    return NULL;
  }

  newplayer->name[0] = '\0';
  newplayer->loc = NO_ID;
  newplayer->inv = inventory_create();

  return newplayer;
}

STATUS player_destroy( Player *player ) {

  if ( !player )
    return ERROR;

  inventory_destroy( player->inv );

  free( player );

  return OK;
}

STATUS player_set_name( Player *player, char *name ) {

  if ( !player || !name ) {
    return ERROR;
  }

  if (!strcpy(player->name, name)) {
    return ERROR;
  }

  return OK;
}

STATUS player_set_location(Player *player, Id id) {

  if ( !player || id == NO_ID )
    return ERROR;

  player->loc = id;

  return OK;
}

STATUS player_add_object( Player *player, Id id ) {

  if ( !player )
    return ERROR;

  return inventory_add_id( player->inv, id );
}

STATUS player_del_object( Player* player, Id id ) {

  if ( !player )
    return ERROR;

  return inventory_del_id( player->inv, id );
}

const char *player_get_name(Player *player) {
  if ( !player )
    return NULL;

  return player->name;
}

void player_set_id( Player* player, Id id ) {
  if ( !player )
    return;

  player->id = id;
}

Id player_get_id(Player *player) {
  if (!player)
    return NO_ID;

  return player->id;
}

Id player_get_location(Player *player) {
  if (!player) {
    return NO_ID;
  }
  return player->loc;
}

bool player_has_object( Player *player, Id id ) {

  if ( !player )
    return false;

  return inventory_has_id( player->inv, id );

}
