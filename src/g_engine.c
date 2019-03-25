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
#include "link.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
* @brief Main graphic engine structure
*/
struct _G_engine {
  Ui *game_ui; /*!< @brief Game interface */
  Ui *help_ui; /*!< @brief Help interface */
};

/*! Box list */
enum _Boxes {
  GAME_MAP, /*!< Map box */
  GAME_OVERVIEW, /*!< Overview box */
  GAME_TITLE, /*!< Title box */
  GAME_HELP, /*!< Help box */
  GAME_FEED, /*!< Feedback box */
  HELP_TITLE, /*!< Help title */
  HELP_BODY /*!< Help body */
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

  Ui *_ui;
  if (ge)
    return ge;

  ge = (G_engine*) malloc( sizeof( G_engine ) );

  if ( ge ) {

    _ui = ui_init( 80, 23 );

    if ( _ui ) {


      ui_bg( _ui, BG_BLACK ); 

      ui_new_box( _ui, GAME_TITLE, 0, 0, 80, 1 );
      ui_new_box( _ui, GAME_MAP, 0, 2, 49, 14 );
      ui_new_box( _ui, GAME_OVERVIEW, 50, 2, 30, 14 );
      ui_new_box( _ui, GAME_HELP, 0, 17, 30, 6 );
      ui_new_box( _ui, GAME_FEED, 31, 17, 49, 6 );

      ui_box_bg( _ui, GAME_FEED, BG_BLACK );
      ui_frm( _ui, 3, FG_BLACK, BG_YELLOW, S_BOLD );
      ui_box_put( _ui, GAME_FEED, " FEED\n");

      ge->game_ui = _ui;

    }

    _ui = ui_init( 80, 23 );

    if ( _ui ) {

      ui_new_box( _ui, HELP_TITLE, 0, 0, 80, 1 );
      ui_new_box( _ui, HELP_BODY, 0, 1, 80, 22);

      ge->help_ui = _ui;

    }

    if ( !ge->game_ui || !ge->help_ui ) {
      g_engine_destroy( ge );
      ge = NULL;
    }

  }

  return ge;

}

void g_engine_paint_help( G_engine *ge, Game *game ) {


  Ui *ui;
  Cmd *cmd, *_cmd;
  char *arg, *b_name;

  if ( !ge || !game )
    return;

  ui = ge->help_ui;
  cmd = game_get_cmd( game );

  ui_clear_box( ui, HELP_TITLE );
  ui_clear_box( ui, HELP_BODY );

  ui_frm( ui, 3, BG_YELLOW, FG_BLACK, S_BOLD );
  ui_box_put( ui, HELP_TITLE, "HELP DESK" );

  ui_box_bg( ui, HELP_BODY, BG_BLACK );

  if ( cmd_get_argc( cmd ) > 1 ) {

    arg = (char*)cmd_get_argv( cmd, 1 );
    _cmd = cmd_get_by_name( arg );

    ui_box_put( ui, HELP_TITLE, "\n" );

    if ( _cmd ) {

      b_name = (char*)cmd_get_bname( _cmd );

      ui_frm( ui, 3, S_BOLD, BG_BLUE, FG_WHITE );
      ui_box_put( ui, HELP_BODY, "%s, %s - ", b_name, cmd_get_sname( _cmd ) );

      if ( !strcmp( b_name, "move" ) ) {

        ui_box_put( ui, HELP_BODY, "<direction> \n" );

        ui_frm( ui, 2, BG_BLACK, FG_WHITE );

        ui_box_put( ui, HELP_BODY, "This command allows you to move over the map.\n" );
        ui_box_put( ui, HELP_BODY, " (*) <direction> [north n] [east e] [south s] [west w]\n");
        ui_box_put( ui, HELP_BODY, "\t\t@ [north n] goes to the north if possible\n");
        ui_box_put( ui, HELP_BODY, "\t\t@ [east e] goes to the east if possible\n");
        ui_box_put( ui, HELP_BODY, "\t\t@ [south s] goes to the south if possible\n");
        ui_box_put( ui, HELP_BODY, "\t\t@ [west w] goes to the west if possible\n");
        ui_box_put( ui, HELP_BODY, "\nNOTE: this command consideres the links of the spaces.\n");

      } else if ( !strcmp( b_name, "take" ) ) {

        ui_box_put( ui, HELP_BODY, "<search_type> <key> \n" );

        ui_frm( ui, 2, BG_BLACK, FG_WHITE );

        ui_box_put( ui, HELP_BODY, "This command allows you to take objects located inside spaces.\n" );
        ui_box_put( ui, HELP_BODY, " (*) <search_type> [-i] [-n]\n");
        ui_box_put( ui, HELP_BODY, "\t\t@ [-i] search by id\n");
        ui_box_put( ui, HELP_BODY, "\t\t@ [-n] search by name\n");
        ui_box_put( ui, HELP_BODY, " (*) <key> searh key\n");
        ui_box_put( ui, HELP_BODY, "\nIf there is only one argument, the default search type used is the name.\n");

      } else if ( !strcmp( b_name, "drop" ) ) {

        ui_box_put( ui, HELP_BODY, "<search_type> <key> \n" );

        ui_frm( ui, 2, BG_BLACK, FG_WHITE );

        ui_box_put( ui, HELP_BODY, "This command allows you to drop objects inside spaces.\n" );
        ui_box_put( ui, HELP_BODY, " (*) <search_type> [-i] [-n]\n");
        ui_box_put( ui, HELP_BODY, "\t\t@ [-i] search by id\n");
        ui_box_put( ui, HELP_BODY, "\t\t@ [-n] search by name\n");
        ui_box_put( ui, HELP_BODY, " (*) <key> search key\n");
        ui_box_put( ui, HELP_BODY, "\nIf there is only one argument, the default search type used is the name.\n");

      } else if ( !strcmp( b_name, "help" ) ) {

        ui_box_put( ui, HELP_BODY, "<command>\n" );

        ui_frm( ui, 2, BG_BLACK, FG_WHITE );

        ui_box_put( ui, HELP_BODY, "This command allows you to see more information about a command.\n" );
        ui_box_put( ui, HELP_BODY, " (*) <command> command to check\n");
        ui_box_put( ui, HELP_BODY, "\nIf no argument is passed, it will show an overall about all available commands.\n");

      } else if ( !strcmp( b_name, "exit" ) ) {

        ui_box_put( ui, HELP_BODY, "...\n" );

        ui_frm( ui, 2, BG_BLACK, FG_WHITE );

        ui_box_put( ui, HELP_BODY, "This command allows you to exit from the game.\n" );
        ui_box_put( ui, HELP_BODY, "The game will be closed securely and all reserved memory will be freed.\n" );
      } else if ( !strcmp( b_name, "next" ) ) {

        ui_box_put( ui, HELP_BODY, "<n>\n" );

        ui_frm( ui, 2, BG_BLACK, FG_WHITE );

        ui_box_put( ui, HELP_BODY, "This command allows you to move to the south direction.\n" );
        ui_box_put( ui, HELP_BODY, " (*) <n> number of south jumps\n");
        ui_box_put( ui, HELP_BODY, "\nIf there is no argument, the default number of jumps is 1.\n");
        ui_box_put( ui, HELP_BODY, "NOTE: this command ignores the space links.\n");

      } else if ( !strcmp( b_name, "back" ) ) {

        ui_box_put( ui, HELP_BODY, "<n>\n" );

        ui_frm( ui, 2, BG_BLACK, FG_WHITE );

        ui_box_put( ui, HELP_BODY, "This command allows you to move to the north direction.\n" );
        ui_box_put( ui, HELP_BODY, " (*) <n> number of north jumps\n");
        ui_box_put( ui, HELP_BODY, "\nIf there is no argument, the default number of jumps is 1.\n");
        ui_box_put( ui, HELP_BODY, "NOTE: this command ignores the space links.\n");

      } else if ( !strcmp( b_name, "rigth" ) ) {

        ui_box_put( ui, HELP_BODY, "...\n" );
        ui_frm( ui, 2, BG_BLACK, FG_WHITE );
        ui_box_put( ui, HELP_BODY, "This command allows you to move to the east direction.\n" );

      } else if ( !strcmp( b_name, "left" ) ) {

        ui_box_put( ui, HELP_BODY, "...\n" );
        ui_frm( ui, 2, BG_BLACK, FG_WHITE );
        ui_box_put( ui, HELP_BODY, "This command allows you to move to the west direction.\n" );

      }

    } else { /* other cases */
      ui_frm( ui, 3, S_BOLD, BG_RED, FG_BLACK );
      ui_box_put( ui, HELP_BODY, "There are no estries for '%s'\n", arg );
      ui_frm( ui, 2, BG_BLACK, FG_WHITE );
      ui_box_put( ui, HELP_BODY, "Sorry, that didn't work :(\n" );
      ui_box_put( ui, HELP_BODY, "Try using other key words\n" );

    }



  } else {
    ui_box_put( ui, HELP_TITLE, " - Overall\n" );

    ui_frm( ui, 2, FG_WHITE, BG_BLACK );

    ui_box_put( ui, HELP_BODY, "\n");
    ui_box_put( ui, HELP_BODY, "help, h -> show this help desk\n" );
    ui_box_put( ui, HELP_BODY, "next, n -> go to the south\n" );
    ui_box_put( ui, HELP_BODY, "back, b -> go to the north\n" );
    ui_box_put( ui, HELP_BODY, "rigth, r -> go to the east\n" );
    ui_box_put( ui, HELP_BODY, "left, l -> go to the west\n" );
    ui_box_put( ui, HELP_BODY, "move, m -> go to a given direction\n" );
    ui_box_put( ui, HELP_BODY, "take, t -> take an object\n" );
    ui_box_put( ui, HELP_BODY, "drop, d -> drop an object\n" );
    ui_box_put( ui, HELP_BODY, "exit, e -> game exit\n" );

  }

  ui_box_put( ui, HELP_BODY, "\nPress ENTER key to exit help\n" );

  ui_draw( stdout, ui );

}

void g_engine_destroy( G_engine *ge ) {

  if ( ge ) {
    ui_destroy( ge->game_ui );
    ui_destroy( ge->help_ui );
    free( ge );
  }

}

void parse_space( Game *game, G_engine *ge, Space *sp, int id, int x, int y ) {

  int i;
  Ui *ui;
  char *pp;
  int _x, _y;
  Id tid; /* temporary id */
  Link *ln;
  Object *obj;
  Object **objs;
  Player *player;
  int off[4]={0,0,0,5};

  if ( !game || !ge )
    return;

  _x = x;
  _y = y;
  ui = ge->game_ui;

  player = game_get_player( game );

  if ( space_get_id( sp ) == player_get_location( player ) ) {
    ui_frm( ui, 3, BG_WHITE, S_BOLD, FG_BLACK );
  }

  _x=x+off[3];
  ui_box_seek( ui, id, _x, _y++ );
  ui_box_put( ui, id, "+----------------------+" );
  ui_box_seek( ui, id, _x, _y++ );
  ui_box_put( ui, id, "|                      |", space_get_id( sp ) );

  /* east link */
  ln = game_get_link_by_id( game, space_get_link( sp, E ) );
  tid = link_get_to( ln );

  if ( tid != NO_ID ) {

    ui_frm( ui, 2, BG_WHITE, FG_BLACK );
    ui_box_seek( ui, id, x+off[3]+25, y );
    ui_box_put( ui, id, "%-2d", link_get_id( ln ) );
    ui_box_seek( ui, id, x+off[3]+24, y+1 );
    ui_box_put( ui, id, "->" );
    if ( space_get_id( sp ) == player_get_location( player) ) {
      ui_frm( ui, 3, BG_WHITE, S_BOLD, FG_RED );
    }
    ui_box_put( ui, id, "%2d", tid );
  }

  ln = game_get_link_by_id( game, space_get_link( sp, W ) );
  tid = link_get_to( ln );

  /* west link */
  if ( tid != NO_ID ) {

    ui_box_seek( ui, id, x, y+1 );

    if ( space_get_id( sp ) == player_get_location( player) ) {
      ui_frm( ui, 3, BG_WHITE, S_BOLD, FG_RED );
    }
    ui_box_put( ui, id, "%2d", tid );

    ui_frm( ui, 2, BG_WHITE, FG_BLACK );
    ui_box_put( ui, id, " <-");
    ui_box_seek( ui, id, x+off[3]-3, y );
    ui_box_put( ui, id, "%2d", link_get_id( ln ) );
  }

  if ( space_get_id( sp ) == player_get_location( player ) ) {
    ui_frm( ui, 3, BG_WHITE, S_BOLD, FG_BLACK );
  }

  ui_box_seek( ui, id, _x, _y++ );
  ui_box_put( ui, id, "|                      |" );
  ui_box_seek( ui, id, _x, _y++ );
  ui_box_put( ui, id, "|                      |" );
  ui_box_seek( ui, id, _x, _y++ );
  ui_box_put( ui, id, "|                      |" );
  ui_box_seek( ui, id, _x, _y++ );
  ui_box_put( ui, id, "+----------------------+" );

  ln = game_get_link_by_id( game, space_get_link( sp, S ) );
  tid = link_get_to( ln );

  if ( tid != NO_ID ) {
    ui_box_seek( ui, id, x+off[3]+11, 7 );
    ui_frm( ui, 3, S_BOLD, BG_WHITE, FG_BLACK );
    ui_box_put( ui, id, "v " );
    ui_frm( ui, 2, BG_WHITE, FG_BLACK );
    ui_box_put( ui, id, "%d", link_get_id( ln ) );
    ui_rs( ui );
  }

  if ( space_get_id( sp ) == player_get_location( player ) ) {
    ui_box_seek( ui, id, x+off[3]+2, y+1 );
    ui_box_put( ui, id, "☻" );
  }

  /* space id */
  ui_box_seek( ui, id, x+off[3]+20, y+1 );
  ui_box_put( ui, id, "%2d", space_get_id( sp ) );

  /* draw space picture */
  _y=y+2;
  _x=x+off[3]+15;
  pp = space_get_picture( sp );

  if ( pp ) {

    ui_box_seek( ui, id, _x, _y );

    for (i=0; i < strlen( pp ); i++ ) {

      if ( pp[ i ] == '\\' && pp[ i + 1 ] == 'n' ) {
        i++; _y++;
        ui_box_seek( ui, id, _x, _y );
      } else if ( pp[ i ] != '\n' ) {
        ui_box_put( ui, id, "%c", pp[ i ] );
      }

    }

  }

  /* draw space objects */
  _x = x+off[3]+2;
  _y = y+4;
  ui_box_seek( ui, id, _x, _y );

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
  Ui *ui = ge->game_ui;
  Id  sp_id = NO_ID,
      sp_cu_id = NO_ID,
      sp_south_id = NO_ID;
  Player *player;
  Link *ln = NULL;
  Space *cu_sp = NULL;
  Object *obj;
  Object **objs;
  char *answer;
  Cmd *cmd;

  if ( !ge || !game )
    return;

  cmd = game_get_cmd( game );
  player = game_get_player( game );

  /* title box */
  ui_clear_box( ui, GAME_TITLE );
  ui_box_bg( ui, GAME_TITLE, BG_YELLOW );
  ui_frm( ui, 4, BG_YELLOW, FG_BLACK, S_REVERSE, S_BOLD );
  ui_box_put( ui, GAME_TITLE, " Goose game ");
  ui_frm( ui, 2, BG_YELLOW, FG_BLACK );
  ui_box_put( ui, GAME_TITLE, " by lromeraj, Mikel04, alvarorp00 and Gosma00");
  ui_rs( ui );

  /* map box */
  ui_clear_box( ui, GAME_MAP );
  ui_box_bg( ui, GAME_MAP, BG_WHITE );

  ui_frm( ui, 3, BG_GREEN, FG_WHITE, S_BOLD );
  ui_box_put( ui, GAME_MAP, "                     MAP\n");
  ui_rs( ui );

  /* !!! IMPROVE START */
  sp_cu_id = player_get_location( game_get_player( game ) );
  cu_sp = game_get_space( game, sp_cu_id );

  ln = game_get_link_by_id( game, space_get_link( cu_sp, S ) );
  sp_south_id = link_get_to( ln );


  if ( sp_cu_id != NO_ID ) {
    parse_space( game, ge, cu_sp, GAME_MAP, 0, 1 );
  }

  /* check if there is a space at the south */
  if ( game_get_space( game, sp_south_id ) ) {
    parse_space( game, ge, game_get_space( game, sp_south_id ), GAME_MAP, 0, 8 );
  }
  /* !!! IMPROVE END */

  x=42;
  y=1;
  ui_box_seek( ui, GAME_MAP, x, y++ );
  ui_box_put( ui, GAME_MAP, "+---+");
  ui_box_seek( ui, GAME_MAP, x, y++ );
  ui_box_put( ui, GAME_MAP, "| %1d |", die_get_lastn( game_get_die( game ) ) );
  ui_box_seek( ui, GAME_MAP, x, y++ );
  ui_box_put( ui, GAME_MAP, "+---+");

  /* overview box */
  ui_clear_box( ui, GAME_OVERVIEW );
  ui_box_bg( ui, GAME_OVERVIEW, BG_WHITE );
  ui_frm( ui, 3, BG_RED, FG_WHITE, S_BOLD );
  ui_box_put( ui, GAME_OVERVIEW, "          OVERVIEW\n");
  ui_rs( ui );


  objs = game_get_objects( game );

  if ( objs ) {

    /* object data */
    for ( i=0; i < MAX_OBJECTS; i++ ) {

      obj = objs[ i ];

      if ( !obj ) continue;

      sp_id = space_get_id( game_get_object_space( game, obj_get_id( obj ) ) );

      ui_frm( ui, 3, S_BOLD, BG_WHITE, FG_BLACK );
      ui_box_put( ui, GAME_OVERVIEW, " %s", obj_get_name( obj ) );
      ui_rs( ui );

      ui_box_put( ui, GAME_OVERVIEW, "{id: %d, ",  obj_get_id( obj ) );
      ui_box_put( ui, GAME_OVERVIEW, "loc: ");

      if ( sp_id == -1 ) {
        ui_frm( ui, 4, S_BLINK, BG_WHITE, FG_RED, S_BOLD );
        ui_box_put( ui, GAME_OVERVIEW, "?" );
      } else {
        ui_box_put( ui, GAME_OVERVIEW, "%ld", sp_id );
      }
      ui_rs( ui );
      ui_box_put( ui, GAME_OVERVIEW, "}\n" );

    }

  }

  /* player data */
  ui_box_put( ui, GAME_OVERVIEW, "\n" );

  /* player name */
  ui_frm( ui, 3, BG_WHITE, FG_BLACK, S_BOLD );
  ui_box_put( ui, GAME_OVERVIEW, " %s", player_get_name( player ) );
  ui_rs( ui );

  ui_box_put( ui, GAME_OVERVIEW, "{id: %ld, loc: %ld}\n", player_get_id( player ), player_get_location( player ) );

  /* help box */
  ui_clear_box( ui, GAME_HELP );
  ui_box_bg( ui, GAME_HELP, BG_WHITE );
  ui_frm( ui, 3, FG_WHITE, BG_PURPLE, S_BOLD );
  ui_box_put( ui, GAME_HELP, " HELP\n" );
  ui_rs( ui );

  ui_box_put( ui, GAME_HELP, " next: n  back: b  take: t\n" );
  ui_box_put( ui, GAME_HELP, " drop: d  exit: e  roll: rl\n" );
  ui_box_put( ui, GAME_HELP, " left: l  rigth: r move: m\n" );
  ui_box_put( ui, GAME_HELP, " help: h\n" );
  ui_rs( ui );

  /* feedback box */
  if ( cmd ) {

    ui_frm( ui, 3, S_BOLD, BG_BLACK, FG_WHITE );
    ui_box_put( ui, GAME_FEED, " $ " );
    ui_rs( ui );

    ui_frm( ui, 3, FG_YELLOW, S_BOLD, BG_BLACK  );

    if ( cmd_get_cid( cmd ) == UNKNOWN ) {
      ui_box_put( ui, GAME_FEED, "%s", cmd_get_argv( cmd, 0 ) );
    } else {
      ui_box_put( ui, GAME_FEED, "%s", cmd_get_bname( cmd ) );
      ui_frm( ui, 2, FG_WHITE, BG_BLACK  );
    }

    ui_frm( ui, 2, FG_WHITE, BG_BLACK  );

    /* draw command answer */
    answer = (char*)cmd_get_ans( cmd );

    if ( strlen( answer ) ) {
      ui_box_put( ui, GAME_FEED, " - %s", answer );
    }

    ui_box_put( ui, GAME_FEED, "\n" );
  }


  /* prints all the data into stdout */
  ui_draw( stdout, ui );

}
