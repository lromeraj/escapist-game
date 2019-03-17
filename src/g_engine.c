/**
* @brief Graphic engine source code
*
* @file g_engine.c
* @version 0.7.2
* @date 17/03/2019
* @copyright GNU Public License
*/


#include "game.h"
#include "player.h"
#include "g_engine.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
* @brief Main graphic engine structure
*/
struct _G_engine {
  Ui *ui; /*!< @brief User interface */
};

/*! Box list */
enum _Boxes {
  _MAP, /*!< Map box */
  _OVERVIEW, /*!< Overview box */
  _TITLE, /*!< Title box */
  _HELP, /*!< Help box */
  _FEED /*!< Feedback box */
};

/****** PRIVATE FUNCTIONS ******/

/**
* @brief Parses a given space
* @param {Game*} game - Game pointer
* @param {G_engine*} ge - Graphic engine pointer
* @param {Space*} sp - Space to be drawn
* @param {int} id - Box id
* @param {int} x - Begin x position (relative to the box)
* @param {int} y - Begin y position (relative to the box)
*/
void parse_space( Game *game, G_engine *ge, Space *sp, int id, int x, int y );

/*******************************/

G_engine *g_engine_create() {

  static G_engine *ge = NULL;

  if (ge)
    return ge;

  ge = (G_engine*) malloc( sizeof( G_engine ) );

  if ( ge ) {

    // initialize user interface
    ge->ui = ui_init( 80, 23 );

    if ( ge->ui ) {

      ui_bg( ge->ui, BG_BLUE );

      ui_new_box( ge->ui, _TITLE, 0, 0, 80, 1 );
      ui_new_box( ge->ui, _MAP, 1, 2, 48, 14 );
      ui_new_box( ge->ui, _OVERVIEW, 50, 2, 29, 14 );
      ui_new_box( ge->ui, _HELP, 1, 17, 33, 5 );
      ui_new_box( ge->ui, _FEED, 35, 17, 44, 5 );

      ui_box_bg( ge->ui, _FEED, BG_BLACK );
      ui_frm( ge->ui, 3, FG_BLACK, BG_YELLOW, S_BOLD );
      ui_box_put( ge->ui, _FEED, " FEED\n");


    } else {
      g_engine_destroy( ge );
      ge = NULL;
    }

  }

  return ge;

}

void g_engine_destroy( G_engine *ge ) {

  if ( ge ) {
    ui_destroy( ge->ui );
    free( ge );
  }

}

void parse_space( Game *game, G_engine *ge, Space *sp, int id, int x, int y ) {

  int i;
  Ui *ui;
  char *pp;
  int _x, _y;
  Object *obj;
  Object **objs;
  Player *player;
  Id tid; // temp id

  if ( !game || !ge )
    return;

  _x = x;
  _y = y;
  ui = ge->ui;

  player = game_get_player( game );

  if ( space_get_id( sp ) == player_get_location( player ) ) {
    ui_frm( ui, 3, BG_WHITE, S_BOLD, FG_BLACK );
  }

  ui_box_seek( ui, id, _x, _y++ );
  ui_box_put( ui, id, "+----------------------+" );
  ui_box_seek( ui, id, _x, _y++ );
  ui_box_put( ui, id, "|                      |", space_get_id( sp ) );

  tid = space_get_east( sp );
  if ( tid != NO_ID ) {
    if ( space_get_id( sp ) == player_get_location( player) ) {
      ui_frm( ui, 3, BG_WHITE, S_BOLD, FG_RED );
    }
    ui_box_put( ui, id, " >%2d", tid );
    if ( space_get_id( sp ) == player_get_location( player ) ) {
      ui_frm( ui, 3, BG_WHITE, S_BOLD, FG_BLACK );
    }
  }
  ui_box_seek( ui, id, _x, _y++ );
  ui_box_put( ui, id, "|                      |" );
  ui_box_seek( ui, id, _x, _y++ );
  ui_box_put( ui, id, "|                      |" );
  ui_box_seek( ui, id, _x, _y++ );
  ui_box_put( ui, id, "|                      |" );
  ui_box_seek( ui, id, _x, _y++ );
  ui_box_put( ui, id, "+----------------------+" );

  if ( space_get_id( sp ) == player_get_location( player ) ) {
    ui_box_seek( ui, id, x+2, y+1 );
    ui_box_put( ui, id, ">8D");
  }

  ui_box_seek( ui, id, x+20, y+1 );
  ui_box_put( ui, id, "%2d", space_get_id( sp ) );

  // draw space picture
  _y=y+2;
  _x=x+15;
  pp = space_get_picture( sp );

  ui_box_seek( ui, id, _x, _y );

  for (i=0; i < strlen( pp ); i++ ) {

    if ( pp[ i ] == '\\' && pp[ i + 1 ] == 'n' ) {
      i++; _y++;
      ui_box_seek( ui, id, _x, _y );
    } else if ( pp[ i ] != '\n' ) {
      ui_box_put( ui, id, "%c", pp[ i ] );
    }

  }

  // draw space objects
  _x = x+2;
  _y = y+4;
  ui_box_seek( ui, id, _x, _y );

  // request game objects
  objs = game_get_objects( game );

  if ( objs ) {
    for ( i=0; i < MAX_OBJECTS; i++ ) {
      obj = objs[ i ];
      if ( !obj ) continue;
      if ( space_has_object( sp, obj_get_id( obj ) ) ) {
        ui_box_put( ui, id, "%ld ", obj_get_id( obj ) );
      }
    }

  }

  ui_rs( ui );

}

void g_engine_paint_game( G_engine *ge, Game *game ) {

  int i, x, y;
  Ui *ui = ge->ui;
  Id  sp_id = NO_ID,
      sp_cu_id = NO_ID,
      sp_south_id = NO_ID;
  Space *cu_sp = NULL;
  Object *obj;
  Object **objs;
  char *answer;
  Cmd *cmd = game_get_cmd( game );

  // title box
  ui_clear_box( ui, _TITLE );
  ui_box_bg( ui, _TITLE, BG_YELLOW );
  ui_frm( ui, 4, BG_YELLOW, FG_BLACK, S_REVERSE, S_BOLD );
  ui_box_put( ui, _TITLE, " Goose game ");
  ui_frm( ui, 2, BG_YELLOW, FG_BLACK );
  ui_box_put( ui, _TITLE, " by Javier Romera & Alvaro Rodriguez");
  ui_rs( ui );

  // map box
  ui_clear_box( ui, _MAP );
  ui_box_bg( ui, _MAP, BG_WHITE );

  ui_frm( ui, 3, BG_GREEN, FG_WHITE, S_BOLD );
  ui_box_put( ui, _MAP, "                     MAP\n");
  ui_rs( ui );

  // get current player location
  sp_cu_id = player_get_location( game_get_player( game ) );
  cu_sp = game_get_space( game, sp_cu_id ); // current space
  sp_south_id = space_get_south( cu_sp ); // south id

  if ( sp_cu_id != NO_ID ) {
    parse_space( game, ge, cu_sp, _MAP, 1, 1 );
  }
  if ( sp_south_id != NO_ID ) {
    ui_box_seek( ui, _MAP, 12, 7 );
    ui_box_put( ui, _MAP, "v");
    parse_space( game, ge, game_get_space( game, sp_south_id ), _MAP, 1, 8 );
  }

  x=42;
  y=1;
  ui_box_seek( ui, _MAP, x, y++ );
  ui_box_put( ui, _MAP, "+---+");
  ui_box_seek( ui, _MAP, x, y++ );
  ui_box_put( ui, _MAP, "| %1d |", die_get_lastn( game_get_die( game ) ) );
  ui_box_seek( ui, _MAP, x, y++ );
  ui_box_put( ui, _MAP, "+---+");

  // overview box
  ui_clear_box( ui, _OVERVIEW );
  ui_box_bg( ui, _OVERVIEW, BG_WHITE );
  ui_frm( ui, 3, BG_RED, FG_WHITE, S_BOLD );
  ui_box_put( ui, _OVERVIEW, "          OVERVIEW\n");
  ui_rs( ui );


  objs = game_get_objects( game );

  if ( objs ) {

    // object data
    for ( i=0; i < MAX_OBJECTS; i++ ) {

      obj = objs[ i ];

      if ( !obj ) continue;

      sp_id = space_get_id( game_get_object_space( game, obj_get_id( obj ) ) );

      ui_frm( ui, 3, S_BOLD, BG_WHITE, FG_BLACK );
      ui_box_put( ui, _OVERVIEW, " O%ld: ", obj_get_id( obj ) );
      if ( sp_id == -1 ) {
        ui_frm( ui, 4, S_BLINK, BG_WHITE, FG_RED, S_BOLD );
        ui_box_put( ui, _OVERVIEW, "(taken)" );
      } else {
        ui_rs( ui );
        ui_box_put( ui, _OVERVIEW, "%d", (int)sp_id );
      }

      ui_box_put( ui, _OVERVIEW, "\n" );

    }

  }

  // player data
  ui_box_put( ui, _OVERVIEW, "\n" );

  // player name
  ui_frm( ui, 3, BG_WHITE, FG_BLACK, S_BOLD );
  ui_box_put( ui, _OVERVIEW, " P%d", player_get_id( game_get_player( game ) ) );
  ui_rs( ui );

  ui_box_put( ui, _OVERVIEW, ": %ld\n", player_get_location( game_get_player( game ) ) );

  // help box
  ui_clear_box( ui, _HELP );
  ui_box_bg( ui, _HELP, BG_WHITE );
  ui_frm( ui, 3, FG_WHITE, BG_PURPLE, S_BOLD );
  ui_box_put( ui, _HELP, " HELP\n" );
  ui_rs( ui );

  ui_box_put( ui, _HELP, " next: n  back: b  take: t\n" );
  ui_box_put( ui, _HELP, " drop: d  exit: e  roll: rl\n" );
  ui_box_put( ui, _HELP, " left: l  rigth: r\n" );
  ui_rs( ui );

  // feedback box
  if ( cmd ) {

    ui_frm( ui, 3, S_BOLD, BG_BLACK, FG_WHITE );
    ui_box_put( ui, _FEED, " $ " );
    ui_rs( ui );

    ui_frm( ui, 3, FG_YELLOW, S_BOLD, BG_BLACK  );

    if ( cmd_get_cid( cmd ) == UNKNOWN ) {
      ui_box_put( ui, _FEED, "%s", cmd_get_argv( cmd, 0 ) );
    } else {
      ui_box_put( ui, _FEED, "%s", cmd_get_bname( cmd ) );
      ui_frm( ui, 2, FG_WHITE, BG_BLACK  );
    }

    ui_frm( ui, 2, FG_WHITE, BG_BLACK  );

    // draw command answer
    answer = (char*)cmd_get_ans( cmd );

    if ( strlen( answer ) ) {
      ui_box_put( ui, _FEED, " - %s", answer );
    }

    ui_box_put( ui, _FEED, "\n" );
  }


  // prints all the data into stdout
  ui_draw( ui );

  printf("\e[0;1m\emcmd:>\e[0m ");
}
