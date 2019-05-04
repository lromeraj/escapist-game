/**
* @brief Graphic engine source code
*
* @file g_engine.c
* @version 0.7.2
* @date 17/03/2019
* @copyright GNU Public License
*/

#include "str.h"
#include "game.h"
#include "player.h"
#include "inventory.h"
#include "g_engine.h"
#include "ui.h"
#include "link.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define MAIN_BG "brgb(29,38,47)" /*!< @brief Main background color */
#define MAIN_FG "frgb(255,255,255)" /*!< @brief Main foreground color */

/* game ui */
#define GAME_MAP_BG MAIN_BG
#define GAME_MAP_FG MAIN_FG

#define GAME_INFO_BG MAIN_BG
#define GAME_INFO_FG MAIN_FG

#define GAME_FEED_BG MAIN_BG
#define GAME_FEED_FG MAIN_FG

#define GAME_TITLE_BG "brgb(255,172,0)"
#define GAME_TITLE_FG "frgb(29,38,47)"

#define LINK_CLOSED_FG "frgb(255,64,64)"
#define LINK_OPENED_FG "frgb(55,255,62)"

/* help ui */
#define HELP_TITLE_BG "brgb(255,172,0)"
#define HELP_TITLE_FG "frgb(29,38,47)"
#define HELP_BODY_BG MAIN_BG
#define HELP_BODY_FG MAIN_FG


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
  GAME_FEED, /*!< Feedback box */
  GAME_INFO, /*!< Info box */
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
void parse_map( G_engine *ge, Game *game, int box );
void parse_info( G_engine *ge, Game *game, int box );

/*******************************/


G_engine *g_engine_create() {

  static G_engine *ge = NULL;

  Ui *_ui;

  if ( ge )
    return ge;

  ge = (G_engine*) malloc( sizeof( G_engine ) );

  if ( ge ) {

    _ui = ui_init( MIN_WIN_COLS, MIN_WIN_ROWS-1 );

    if ( _ui ) {

      ui_bg( _ui, "%s", MAIN_BG );

      ui_new_box( _ui, GAME_TITLE, 0, 0, 80, 1 );
      ui_new_box( _ui, GAME_MAP, 0, 1, 80, 15 );
      ui_new_box( _ui, GAME_FEED, 0, 16, 80, 7 );
      ui_new_box( _ui, GAME_INFO, 0, 15, 80, 8 );

      /* game feed */
      ui_box_bg( _ui, GAME_FEED, "%s", GAME_FEED_BG ); /* fill game feed background */

      ui_box_frms( _ui, GAME_FEED, "%s;%s", GAME_FEED_FG, GAME_FEED_BG );
      ui_frms( _ui, "0;%s;%s", "frgb(0,0,0)", "brgb(0, 163, 255)" );
      ui_box_put( _ui, GAME_FEED, "@{1} FEEDBACK\n" );
      ui_box_put( _ui, GAME_FEED, "@{0;3;frgb(150,150,150)}NOTE@{0}: use@{1;%s;%d} help @{0}", GAME_FEED_BG, FG_YELLOW );
      ui_box_put( _ui, GAME_FEED, "to see information about the game\n" );

      /* game info */
      ui_box_frms( _ui, GAME_INFO, "%s;%s", GAME_INFO_BG, GAME_INFO_FG );

      /* game map */
      ui_box_frms( _ui, GAME_MAP, "%s;%s", GAME_MAP_BG, GAME_MAP_FG );
      ui_box_bg( _ui, GAME_MAP, "%s", GAME_MAP_BG );

      /* game title */
      ui_box_frm( _ui, GAME_TITLE, 2, BG_YELLOW, FG_BLACK );

      /* title box */
      ui_box_bg( _ui, GAME_TITLE, "%s", GAME_TITLE_BG );
      ui_frms( _ui, "0;%d;%s;%s", S_REVERSE, GAME_TITLE_BG, GAME_TITLE_FG );
      ui_box_put( _ui, GAME_TITLE, " Goose game ");
      ui_frms( _ui, "0;1;%s;%s", GAME_TITLE_BG, GAME_TITLE_FG );
      ui_box_put( _ui, GAME_TITLE, " by lromeraj, Mikel04, alvarorp00 and Gosma00");
      ui_frms( _ui, "0" );
      ui_dump_box( _ui, GAME_TITLE );

      ge->game_ui = _ui;

    }

    _ui = ui_init( MIN_WIN_COLS, MIN_WIN_ROWS-1 );

    if ( _ui ) {

      ui_new_box( _ui, HELP_TITLE, 0, 0, 80, 1 );
      ui_new_box( _ui, HELP_BODY, 0, 1, 80, 22);

      ui_box_frms( _ui, HELP_TITLE, "%s;%s", HELP_TITLE_BG, HELP_TITLE_FG );
      ui_box_frms( _ui, HELP_BODY, "%s;%s", HELP_BODY_BG, HELP_BODY_FG );

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

  ui_frms( ui, "0;1;%s;%s", HELP_TITLE_BG, HELP_TITLE_FG );
  ui_box_put( ui, HELP_TITLE, " HELP DESK" );

  ui_box_bg( ui, HELP_BODY, "%s", HELP_BODY_BG );

  if ( cmd_get_argc( cmd ) > 1 ) {

    arg = (char*)cmd_get_argv( cmd, 1 );
    _cmd = cmd_get_by_name( arg );

    ui_box_put( ui, HELP_TITLE, "\n" );

    if ( _cmd ) {

      b_name = (char*)cmd_get_bname( _cmd );

      ui_frms( ui, "0;1;%s;brgb(22,128,221)", MAIN_FG );
      ui_box_put( ui, HELP_BODY, " %s, %s - ", b_name, cmd_get_sname( _cmd ) );

      if ( !strcmp( b_name, "move" ) ) {

        ui_box_put( ui, HELP_BODY, "<direction> \n" );

        ui_box_put( ui, HELP_BODY, "@{0}This command allows you to move over the map.\n" );
        ui_box_put( ui, HELP_BODY, " (*) <direction> [north n] [east e] [south s] [west w]\n");
        ui_box_put( ui, HELP_BODY, "\t\t@ [north n] goes to the north if possible\n");
        ui_box_put( ui, HELP_BODY, "\t\t@ [east e] goes to the east if possible\n");
        ui_box_put( ui, HELP_BODY, "\t\t@ [south s] goes to the south if possible\n");
        ui_box_put( ui, HELP_BODY, "\t\t@ [west w] goes to the west if possible\n");
        ui_box_put( ui, HELP_BODY, "\nNOTE: this command consideres the links of the spaces.\n");

      } else if ( !strcmp( b_name, "take" ) ) {

        ui_box_put( ui, HELP_BODY, "<name> \n" );

        ui_box_put( ui, HELP_BODY, "@{0}This command allows you to take objects located inside spaces.\n" );
        ui_box_put( ui, HELP_BODY, " (*) <name> Object name \n");
        ui_box_put( ui, HELP_BODY, "You can take as much @{1;%d;%d} %d @{0} object/s\n",
                                    FG_BLACK, BG_YELLOW, MAX_INVENTORY );
        ui_box_put( ui, HELP_BODY, "\nIf there is only one argument, the default search type used is the name.\n");

      } else if ( !strcmp( b_name, "drop" ) ) {

        ui_box_put( ui, HELP_BODY, "<search_type> <key> \n" );

        ui_box_put( ui, HELP_BODY, "@{0}This command allows you to drop objects inside spaces.\n" );
        ui_box_put( ui, HELP_BODY, " (*) <search_type> [-i] [-n]\n");
        ui_box_put( ui, HELP_BODY, "\t\t@ [-i] search by id\n");
        ui_box_put( ui, HELP_BODY, "\t\t@ [-n] search by name\n");
        ui_box_put( ui, HELP_BODY, " (*) <key> search key\n");
        ui_box_put( ui, HELP_BODY, "\nIf there is only one argument, the default search type used is the name.\n");

      } else if ( !strcmp( b_name, "help" ) ) {

        ui_box_put( ui, HELP_BODY, "<command>\n" );

        ui_box_put( ui, HELP_BODY, "@{0}This command allows you to see more information about a command.\n" );
        ui_box_put( ui, HELP_BODY, " (*) <command> command to check\n");
        ui_box_put( ui, HELP_BODY, "\nIf no argument is passed, it will show an overall about all available commands.\n");

      } else if ( !strcmp( b_name, "exit" ) ) {

        ui_box_put( ui, HELP_BODY, "...\n" );

        ui_box_put( ui, HELP_BODY, "@{0}This command allows you to exit from the game.\n" );
        ui_box_put( ui, HELP_BODY, "The game will be closed securely and all reserved memory will be freed.\n" );

      } else if ( !strcmp( b_name, "next" ) ) {

        ui_box_put( ui, HELP_BODY, "<n>\n" );

        ui_box_put( ui, HELP_BODY, "@{0}This command allows you to move to the south direction.\n" );
        ui_box_put( ui, HELP_BODY, " (*) <n> number of south jumps\n");
        ui_box_put( ui, HELP_BODY, "\nIf there is no argument, the default number of jumps is 1.\n");
        ui_box_put( ui, HELP_BODY, "NOTE: this command ignores the space links.\n");

      } else if ( !strcmp( b_name, "back" ) ) {

        ui_box_put( ui, HELP_BODY, "<n>\n" );

        ui_box_put( ui, HELP_BODY, "@{0}This command allows you to move to the north direction.\n" );
        ui_box_put( ui, HELP_BODY, " (*) <n> number of north jumps\n");
        ui_box_put( ui, HELP_BODY, "\nIf there is no argument, the default number of jumps is 1.\n");
        ui_box_put( ui, HELP_BODY, "NOTE: this command ignores the space links.\n");

      } else if ( !strcmp( b_name, "right" ) ) {

        ui_box_put( ui, HELP_BODY, "...\n" );
        ui_box_put( ui, HELP_BODY, "@{0}This command allows you to move to the east direction.\n" );

      } else if ( !strcmp( b_name, "left" ) ) {

        ui_box_put( ui, HELP_BODY, "...\n" );

        ui_box_put( ui, HELP_BODY, "@{0}This command allows you to move to the west direction.\n" );

      } else if ( !strcmp( b_name, "inspect" ) ) {

        ui_box_put( ui, HELP_BODY, "<type> [search_key]\n" );

        ui_box_put( ui, HELP_BODY, "@{0}This command allows you to inspect objects and spaces.\n" );
        ui_box_put( ui, HELP_BODY, " (*) <type> \n");
        ui_box_put( ui, HELP_BODY, "\t\t@ Use -s to inspect current space\n" );
        ui_box_put( ui, HELP_BODY, "\t\t\t[search_key] is not necessary\n");
        ui_box_put( ui, HELP_BODY, "\t\t@ Use -o to inspect an object by it's name\n");
        ui_box_put( ui, HELP_BODY, "\t\t\t[search_key] is necessary\n");
      }

    } else { /* other cases */
      ui_frm( ui, 3, S_BOLD, BG_RED, FG_WHITE );
      ui_box_put( ui, HELP_BODY, "There are no estries for '%s'\n", arg );
      ui_frm( ui, 2, BG_BLACK, FG_WHITE );
      ui_box_put( ui, HELP_BODY, "Sorry, that didn't work :(\n" );
      ui_box_put( ui, HELP_BODY, "Try using other key words\n" );

    }

  } else {
    ui_box_put( ui, HELP_TITLE, " - Overall\n" );

    ui_frms( ui, "0;%s;%s", HELP_BODY_BG, HELP_BODY_FG );

    ui_box_put( ui, HELP_BODY, "\n");
    ui_box_put( ui, HELP_BODY, "help, h -> show this help desk\n" );
    ui_box_put( ui, HELP_BODY, "next, n -> go to the south\n" );
    ui_box_put( ui, HELP_BODY, "back, b -> go to the north\n" );
    ui_box_put( ui, HELP_BODY, "rigth, r -> go to the east\n" );
    ui_box_put( ui, HELP_BODY, "left, l -> go to the west\n" );
    ui_box_put( ui, HELP_BODY, "move, m -> go to a given direction\n" );
    ui_box_put( ui, HELP_BODY, "take, t -> take an object\n" );
    ui_box_put( ui, HELP_BODY, "drop, d -> drop an object\n" );
    ui_box_put( ui, HELP_BODY, "inspect, i -> inspect an element of the game\n" );
    ui_box_put( ui, HELP_BODY, "exit, e -> game exit\n" );

    ui_box_put( ui, HELP_BODY, "\nTo see more information about " );
    ui_box_put( ui, HELP_BODY, "a particular command use: " );
    ui_box_put( ui, HELP_BODY, "@{1;frgb(255,172,0);%s}help@{0} <command>\n", HELP_BODY_BG );

  }

  ui_box_put( ui, HELP_BODY, "\nPress @{1;%d} ENTER @{0} key to exit help\n", BG_RED );

  ui_dump_box( ui, HELP_TITLE );
  ui_dump_box( ui, HELP_BODY );

  ui_draw( stdout, ui );
}

void g_engine_destroy( G_engine *ge ) {

  if ( ge ) {
    ui_destroy( ge->game_ui );
    ui_destroy( ge->help_ui );
    free( ge );
  }

}

void parse_map( G_engine *ge, Game *game, int box ) {

  int w, x, y, i, j, len;
  Ui *ui;
  char *pp; /* picture pointer */
  char *tstr; /* temporary string pointer */
  int _x, _y; /* temporary cursors */
  Link *ln;
  Object *obj;
  Object *objs[ MAX_OBJECTS ]; /* objects array */
  int t_objs; /* total amount of objects */
  Player *player;
  Space *cu_sp;
  int cell_h = 11; /* number of rows of the space */
  int cell_w = 35; /* number of cols of the space */
  bool light;
  Set *bag;
  CardinalPoint cps[6] = { N, E, S, W, U, D }; /* cardinal points */
  char cpstr[6][2] = { "N", "E", "S", "W", "U", "D" }; /* cardinal points strings */

  if ( !game || !ge )
    return;

  ui = ge->game_ui;

  player = game_get_player( game );
  cu_sp = game_get_space( game, player_get_location( player ) );
  light = space_get_light( cu_sp );

  game_get_objects( game, MAX_OBJECTS, objs, &t_objs );

  x=1;
  y=2;

  _x = x;
  _y = y;

  if ( light ) {
    ui_frms( ui, "0;brgb(255,255,255);frgb(0,0,0)" );
  } else {
    ui_frms( ui, "0;brgb(0,0,0);frgb(255,255,255)" );
  }

  for ( i=0; i < cell_h; i++ ) {

    ui_box_seek( ui, box, _x, _y++ );
    for ( j=0; j < cell_w; j++ ) {
      ui_box_put( ui, box, " " );
    }

  }

  /* print space id */
  ui_box_seek( ui, box, x+2, y+1 );
  if ( light ) {
    ui_frms( ui, "0;1;frgb(0,0,0);brgb(255,255,255)" );
  } else {
    ui_frms( ui, "0;frgb(255,255,255);brgb(0,0,0)" );
  }
  ui_box_put( ui, box, "%ld@{0}", space_get_id( cu_sp ) );

  /* draw space picture */
  _x=x+cell_w-11;
  _y=y+cell_h-5;
  pp = space_get_picture( cu_sp );

  if ( pp ) {

    len = strlen( pp );

    if ( len > 0 ) {

      if ( light ) {
        ui_frms( ui, "0;1;frgb(0,0,0);brgb(255,255,255)" );
      } else {
        ui_frms( ui, "0;frgb(255,255,255);brgb(0,0,0)" );
      }

      ui_box_seek( ui, box, _x, _y );

      len = strlen( pp );

      for (i=0; i < len; i++ ) {

        if ( pp[ i ] == '\\' && pp[ i + 1 ] == 'n' ) {
          i++; _y++;
          ui_box_seek( ui, box, _x, _y );
        } else if ( pp[ i ] != '\n' ) {
          ui_box_put( ui, box, "%c", pp[ i ] );
        }

      }

    }

  }

  _x = x+cell_w+1;
  _y = y;

  /* draw links */
  for ( i=0; i < 6; i++ ) {

    ln = game_get_link_by_id( game, space_get_link( cu_sp, cps[ i ] ) );

    if ( ln ) {
      ui_box_seek( ui, box, _x, _y++ );
      if ( link_get_state( ln ) == LINK_CLOSED ) {
        ui_box_put( ui, box, "@{0;1;%s}!%s@{0}(@{1}%ld@{0})@{0}: ", LINK_CLOSED_FG, cpstr[ i ], link_get_id( ln ) );
      } else {
        ui_box_put( ui, box, "@{0;1;%s}%s@{0}(@{1}%ld@{0})@{0}: ", LINK_OPENED_FG, cpstr[ i ], link_get_id( ln ) );
      }

      ui_box_put( ui, box, "%s", link_get_name( ln ) );
    }

  }

  /* draw overview */
  _x=x+cell_w+1;

  tstr = (char*)space_get_descrp( cu_sp );
  w = ui_box_get_w( ui, box );

  ui_box_seek( ui, box, _x, _y++ );

  for ( i=_x; i < w-1; i++ ) {
    ui_box_put( ui, box, "_" );
  }

  ui_box_seek( ui, box, _x, _y );
  ui_box_set_cx_off( ui, box, _x );

  /* draw player bag */
  ui_box_put( ui, box, "@{0;frgb(150,150,150)}Bag@{0}: " );

  bag = player_get_bag( player );

  for ( i=0, j=0; i < t_objs; i++ ) {
    obj = objs[ i ];
    if ( player_has_object( player, obj_get_id( obj ) ) ) {
      ui_box_put( ui, box, "@{!0;1;frgb(250, 255, 0);%s}%s@{0}", GAME_INFO_BG, obj_get_name( obj ) );
      if ( j < set_get_total( bag ) - 1 ) {
        ui_box_put( ui, box, ", " );
      }
      j++;
    }
  }
  ui_box_put( ui, box, "\n" );

  ui_box_put( ui, box, "@{0;frgb(150,150,150)}%s@{0}: ", space_get_name( cu_sp ) );

  if ( tstr ) {
    ui_box_put( ui, box, "%s\n", tstr );
  }

  ui_box_set_cx_off( ui, box, 0 );

  /* draw space objects */
  _x = x+2;
  _y = y+4;

  ui_box_seek( ui, box, _x, _y++ );

  for ( i=0; i < t_objs; i++ ) {

    obj = objs[ i ];

    if ( !space_has_object( cu_sp, obj_get_id( obj ) ) ) continue;

    if ( space_get_light( cu_sp ) ) {

      if ( obj_get_attr( obj, OBJ_IS_HIDDEN ) == OBJ_NO ) {
        ui_box_put( ui, box, "@{!0;brgb(0,0,0);frgb(255,255,255)} %s ", obj_get_name( obj ) );
        ui_box_put( ui, box, "@{!0;brgb(255,255,255)} " );
      }

    } else {

      if ( !strcmptok( obj_get_name( obj ), "torch", "," ) ) {
        ui_box_put( ui, box, "@{!0;brgb(255,255,255);frgb(0,0,0)} %s ", obj_get_name( obj ) );
        ui_box_put( ui, box, "@{!0;brgb(0,0,0)} " );
      }

    }

    if ( ui_box_get_cx( ui, box ) > x+cell_w/2 ) {
      ui_box_seek( ui, box, _x, _y++ );
    }

  }

  ui_rs( ui );

}


void parse_info( G_engine *ge, Game *game, int box ) {

  Ui *ui;
  Cmd *cmd;
  char *tstr;
  Space *cu_sp;
  Player *player;

  long max_uses;
  Object *obj, *book, *map;

  if ( !ge || !game )
    return;

  ui = ge->game_ui;
  cmd = game_get_cmd( game );

  player = game_get_player( game );
  cu_sp = game_get_space( game, player_get_location( player ) );

  ui_box_bg( ui, GAME_INFO, "%s", GAME_INFO_BG );
  ui_frms( ui, "0;1;brgb(124, 182, 0);frgb(0,0,0)" );
  ui_box_put( ui, GAME_INFO, " INSPECT\n@{0}" );

  tstr = (char*)cmd_get_argv( cmd, 1 );

  if ( !strcmp( tstr, "-s" ) ) {

    map = game_get_object_by_name( game, "map" );

    ui_box_put( ui, GAME_INFO, "@{!0;%s;frgb(150,150,150)}Name@{0}: %s\n", GAME_INFO_BG, space_get_name( cu_sp ) );
    ui_box_put( ui, GAME_INFO, "@{!0;%s;frgb(150,150,150)}Description@{0}: ", GAME_INFO_BG );

    if ( player_has_object( player, obj_get_id( map ) ) ) {
      ui_box_put( ui, GAME_INFO, "%s", space_get_ldescrp( cu_sp ) );
    } else {
      ui_box_put( ui, GAME_INFO, "you need a map to see detailed description" );
    }

  } else if ( !strcmp( tstr, "-o" ) ) {

    book = game_get_object_by_name( game, "book" );

    tstr = (char*) cmd_get_argv( cmd, 2 );
    obj = game_get_object_by_name( game, tstr );

    if ( !obj ) {
      ui_box_put( ui, GAME_INFO, "object '%s' does not exists", tstr );
    } else {

      ui_box_put( ui, GAME_INFO, "@{!0;%s;frgb(150,150,150)}Name@{0}: %s\n", GAME_INFO_BG, obj_get_name( obj ) );

      max_uses = obj_get_attr( obj, OBJ_MAX_USES );

      if ( max_uses > 0 ) {
        ui_box_put( ui, GAME_INFO, "@{!0;%s;frgb(150,150,150)}Used@{0}: %ld of %ld\n", GAME_INFO_BG, obj_get_attr( obj, OBJ_USED ), max_uses );
      }

      ui_box_put( ui, GAME_INFO, "@{!0;%s;frgb(150,150,150)}Description@{0}: ", GAME_INFO_BG );
      if ( player_has_object( player, obj_get_id( book ) ) ) {

        if ( obj_get_attr( obj, OBJ_IS_MOVED ) == OBJ_YES ) {
          ui_box_put( ui, GAME_INFO, "%s", obj_get_ldescrp( obj ) );
        } else {
          ui_box_put( ui, GAME_INFO, "%s", obj_get_descrp( obj ) );
        }

      } else {
        ui_box_put( ui, GAME_INFO, "you need a book to see detailed description" );
      }

    }

  }

}

void g_engine_paint_game( G_engine *ge, Game *game ) {

  int i, w;
  Ui *ui;
  Cmd *cmd; /* last command */
  char *answer;

  if ( !ge || !game )
    return;

  cmd = game_get_cmd( game );
  ui = ge->game_ui;

  /* map box */
  ui_clear_box( ui, GAME_MAP );
  ui_frms( ui, "0;1;brgb(255, 0, 107)" );

  w = ui_box_get_w( ui, GAME_MAP );
  for ( i=0; i < w; i++ ) {
    ui_box_put( ui, GAME_MAP, " " );
  }
  ui_box_seek( ui, GAME_MAP, w/2-2, 0 );
  ui_box_put( ui, GAME_MAP, "@{frgb(0,0,0)}MAP@{0}" );

  parse_map( ge, game, GAME_MAP );

  ui_dump_box( ui, GAME_MAP );

  /* feedback box */
  if ( cmd ) {

    ui_frms( ui, "0;1;%s;%s", GAME_FEED_BG, GAME_FEED_FG );
    ui_box_put( ui, GAME_FEED, "$ " );
    ui_rs( ui );

    ui_frms( ui, "0;1;%s;%s", "frgb(255, 122, 0)", GAME_FEED_BG  );

    if ( cmd_get_cid( cmd ) == UNKNOWN ) {
      ui_box_put( ui, GAME_FEED, "%s", cmd_get_argv( cmd, 0 ) );
    } else {
      ui_box_put( ui, GAME_FEED, "%s", cmd_get_bname( cmd ) );
    }

    ui_frms( ui, "0;%s;%s", GAME_FEED_BG, GAME_FEED_FG );

    /* draw command answer */
    answer = (char*)cmd_get_ans( cmd );

    if ( strlen( answer ) ) {
      ui_box_put( ui, GAME_FEED, " - %s", answer );
    }

    ui_box_put( ui, GAME_FEED, "\n" );

  }

  ui_dump_box( ui, GAME_FEED );

  /* inspect box */
  ui_clear_box( ui, GAME_INFO );

  if ( cmd_get_cid( cmd ) == INSPECT && !cmd_get_errc( cmd ) ) {
    parse_info( ge, game, GAME_INFO );
    ui_dump_box( ui, GAME_INFO );
  }

  /* prints all the data into stdout */

  ui_draw( stdout, ui );

}
