#include "player.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Player {
  Id id;
  char name[WORD_SIZE + 1];
  Id location;
  Id hand_object;
};

Player *player_init() {

  Player *newplayer = NULL;

  newplayer = (Player *)malloc(sizeof(Player));

  if ( !newplayer ) {
    return NULL;
  }

  newplayer->name[0] = '\0';
  newplayer->location = NO_ID;
  newplayer->hand_object = NO_ID;

  return newplayer;
}

STATUS player_destroy(Player *player) {

  if (!player)
    return ERROR;

  free( player );

  return OK;
}

STATUS player_set_name(Player *player, char *name) {
  if (!player || !name) {
    return ERROR;
  }

  if (!strcpy(player->name, name)) {
    return ERROR;
  }

  return OK;
}

STATUS player_set_location(Player *player, Id id) {
  if (!player || id == NO_ID) {
    return ERROR;
  }
  player->location = id;
  return OK;
}

STATUS player_set_object(Player *player, Id id) {
  if (!player) {
    return ERROR;
  }
  player->hand_object = id;
  return OK;
}

const char *player_get_name(Player *player) {
  if (!player) {
    return NULL;
  }
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
  return player->location;
}

bool player_has_object(Player *player) {
  if (!player || player->hand_object == NO_ID) {
    return false;
  }
  return true;
}

Id player_get_object(Player* player){
  if(!player || player->hand_object == NO_ID){
    return NO_ID;
  }
  return player->hand_object;
}

STATUS player_print(Player *player) {
  Id idaux = NO_ID;

  if (!player) {
    return ERROR;
  }

  fprintf(stdout, "--> player (Id: %ld; Name: %s)\n", player->id, player->name);

  idaux = player_get_location(player);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> Location link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No location link.\n");
  }

  if (player_has_object(player)) {
    fprintf(stdout, "---> Object in the player.\n");
  } else {
    fprintf(stdout, "---> No object in the player.\n");
  }

  return OK;
}
