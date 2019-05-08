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
#include "game_rules.h"
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

#define GAME_PICTURE_FG MAIN_FG
#define GAME_PICTURE_BG MAIN_BG

#define GAME_FEED_BG MAIN_BG
#define GAME_FEED_FG MAIN_FG

#define GAME_FULLSCREEN_BG "brgb(0,0,0)"
#define GAME_FULLSCREEN_FG "frgb(255,255,255)"

#define PLAYER_BAG_OBJ_FG "frgb(250,255,0)"

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
  GAME_PICTURE, /*!< Game picture */
  GAME_FULLSCREEN, /*!< Box to show full screen results */
  HELP_TITLE, /*!< Help title */
  HELP_BODY /*!< Help body */
};

/****** PRIVATE FUNCTIONS ******/

/**
* @brief Parses a given space
* @param game - Game pointer
* @param ge - Graphic engine pointer
* @param sp - Space to be drawn
* @param id - Box id
*/
void parse_map( G_engine *ge, Game *game, int box );
void parse_info( G_engine *ge, Game *game, int box );
void dump_file_to_box( Ui *ui, int box, char *f_name );

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

      ui_new_box( _ui, GAME_MAP, 0, 0, 80, 16 );
      ui_new_box( _ui, GAME_FEED, 0, 16, 80, 7 );
      ui_new_box( _ui, GAME_PICTURE, 1, 1, 35, 15 );
      ui_new_box( _ui, GAME_INFO, 37, 2, 43, 11 );
      ui_new_box( _ui, GAME_FULLSCREEN, 0, 0, MIN_WIN_COLS, MIN_WIN_ROWS-1 );

      /* game feed */
      ui_box_bg( _ui, GAME_FEED, "%s", GAME_FEED_BG ); /* fill game feed background */

      ui_box_frms( _ui, GAME_FEED, "%s;%s", GAME_FEED_FG, GAME_FEED_BG );
      ui_frms( _ui, "0;%s;%s", "frgb(0,0,0)", "brgb(0, 163, 255)" );
      ui_box_put( _ui, GAME_FEED, "@{1} FEEDBACK\n" );
      ui_box_put( _ui, GAME_FEED, "@{0;3;frgb(150,150,150)}NOTE@{0}: use@{1;%s;%d} help @{0}", GAME_FEED_BG, FG_YELLOW );
      ui_box_put( _ui, GAME_FEED, "to see information about the game\n" );

      /* game info */
      ui_box_frms( _ui, GAME_INFO, "%s;%s", GAME_INFO_BG, GAME_INFO_FG );

      /* game picture */
      ui_box_frms( _ui, GAME_PICTURE, "%s;%s", GAME_PICTURE_BG, GAME_PICTURE_FG );

      /* game map */
      ui_box_frms( _ui, GAME_MAP, "%s;%s", GAME_MAP_BG, GAME_MAP_FG );
      ui_box_bg( _ui, GAME_MAP, "%s", GAME_MAP_BG );


      ui_box_frms( _ui, GAME_FULLSCREEN, "%s;%s", GAME_FULLSCREEN_BG, GAME_FULLSCREEN_FG );


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

      ui_frms( ui, "0;1;%s;brgb(76, 87, 127)", MAIN_FG );
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

      } else if ( !strcmp( b_name, "inspect" ) ) {

        ui_box_put( ui, HELP_BODY, "<type> [search_key]\n" );

        ui_box_put( ui, HELP_BODY, "@{0}This command allows you to inspect objects and spaces.\n" );
        ui_box_put( ui, HELP_BODY, " (*) <type> \n");
        ui_box_put( ui, HELP_BODY, "\t\t@ Use -s to inspect current space\n" );
        ui_box_put( ui, HELP_BODY, "\t\t\t[search_key] is not necessary\n");
        ui_box_put( ui, HELP_BODY, "\t\t@ Use -o to inspect an object by it's name\n");
        ui_box_put( ui, HELP_BODY, "\t\t\t[search_key] is necessary\n");
      } else if ( !strcmp( b_name, "turn" ) ) {

        ui_box_put( ui, HELP_BODY, "<flag> <obj_name>\n" );

        ui_box_put( ui, HELP_BODY, "@{0}This command allows you to turn on/off objects.\n" );
        ui_box_put( ui, HELP_BODY, " (*) <flag> \n");
        ui_box_put( ui, HELP_BODY, "\t\t@ Use @{1}on@{0} to turn on the object\n" );
        ui_box_put( ui, HELP_BODY, "\t\t@ Use @{1}off@{0} to turn off the object\n");
        ui_box_put( ui, HELP_BODY, " (*) <obj_name> name of the object\n");

      } else if ( !strcmp( b_name, "open" ) ) {
        ui_box_put( ui, HELP_BODY, "<link_id> with <obj_name>\n" );

        ui_box_put( ui, HELP_BODY, "@{0}This command allows you to open links.\n" );
        ui_box_put( ui, HELP_BODY, " (*) <link_id> id of the link\n");
        ui_box_put( ui, HELP_BODY, " (*) <obj_name> name of the object\n");
        ui_box_put( ui, HELP_BODY, "\n@{0;frgb(150,150,150)}Example@{0}: @{3}open 5 with tnt@{0}\n");

      } else if ( !strcmp( b_name, "save" ) ) {

        ui_box_put( ui, HELP_BODY, "<file_name>\n" );

        ui_box_put( ui, HELP_BODY, "@{0}This command allows you to save the progress of a game.\n" );
        ui_box_put( ui, HELP_BODY, "  <file_name> name of the file\n\n");
        ui_box_put( ui, HELP_BODY, "NOTE: if no file name is given a name based on current date will be generated\n");

      } else if ( !strcmp( b_name, "load" ) ) {

        ui_box_put( ui, HELP_BODY, "<file_name>\n" );

        ui_box_put( ui, HELP_BODY, "@{0}This command allows you to load the progress of a game.\n" );
        ui_box_put( ui, HELP_BODY, "  <file_name> name of the file\n\n");

      }

    } else { /* other cases */
      ui_frms( ui, "0;1;%s;brgb(76, 87, 127)", MAIN_FG );
      ui_box_put( ui, HELP_BODY, "There are no estries for '%s'\n", arg );
      ui_box_put( ui, HELP_BODY, "@{0}Sorry, that didn't work :(\n" );
      ui_box_put( ui, HELP_BODY, "Try using other key words\n" );

    }

  } else {
    ui_box_put( ui, HELP_TITLE, " - Overall\n" );

    ui_frms( ui, "0;%s;%s", HELP_BODY_BG, HELP_BODY_FG );

    ui_box_put( ui, HELP_BODY, "@{1;brgb(76, 87, 127)} Command      Description\n@{0}" );
    ui_box_put( ui, HELP_BODY, " @{33}help@{0}, h      show this help desk\n" );
    ui_box_put( ui, HELP_BODY, " @{33}move@{0}, m      go to a given direction\n" );
    ui_box_put( ui, HELP_BODY, " @{33}turn@{0}, trn    turns on/off a given object\n" );
    ui_box_put( ui, HELP_BODY, " @{33}open@{0}, o      opens a link with a given object\n" );
    ui_box_put( ui, HELP_BODY, " @{33}take@{0}, t      take an object\n" );
    ui_box_put( ui, HELP_BODY, " @{33}drop@{0}, d      drop an object\n" );
    ui_box_put( ui, HELP_BODY, " @{33}inspect@{0}, i   inspect an element of the game\n" );
    ui_box_put( ui, HELP_BODY, " @{33}save@{0}, s      saves current game\n" );
    ui_box_put( ui, HELP_BODY, " @{33}load@{0}, ld     loads a game from a given file\n" );
    ui_box_put( ui, HELP_BODY, " @{33}exit@{0}, e      game exit\n" );

    ui_box_put( ui, HELP_BODY, "\n To see more information about " );
    ui_box_put( ui, HELP_BODY, "a particular command use: " );
    ui_box_put( ui, HELP_BODY, "@{1;frgb(255,172,0);%s}help@{0} @{3}<command>@{0}\n", HELP_BODY_BG );

  }

  ui_box_put( ui, HELP_BODY, "\n Press @{!0;1;6;brgb(240, 65, 65)} ENTER @{0} key to exit help\n" );

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
  _x=x+cell_w-12;
  _y=y+cell_h-7;
  pp = space_get_picture( cu_sp );

  if ( pp ) {

    len = strlen( pp );

    if ( len > 0 ) {

      /* change default box formats */
      if ( light ) {
        ui_box_frms( ui, box, "1;frgb(0,0,0);brgb(255,255,255)" );
      } else {
        ui_box_frms( ui, box, "frgb(255,255,255);brgb(0,0,0)" );
      }

      len = strlen( pp );

      ui_box_put( ui, box, "@{0}" );
      ui_box_set_cx_off( ui, box, _x );
      ui_box_set_cx_top( ui, box, x + cell_w );

      ui_box_seek( ui, box, _x, _y );
      ui_box_put( ui, box, "%s", pp );

    }

    /* restore default box format */
    ui_box_frms( ui, box, "%s;%s", GAME_MAP_BG, GAME_MAP_FG );
    ui_box_set_cx_off( ui, box, 0 );
    ui_box_set_cx_top( ui, box, ui_box_get_w( ui, box ) );
    ui_box_put( ui, box, "@{0}" );
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

  if ( set_get_total( bag ) == 0 ) {
    ui_box_put( ui, box, "@{!0;1;%s;%s}----@{0}", PLAYER_BAG_OBJ_FG, GAME_INFO_BG );
  } else {
    for ( i=0, j=0; i < t_objs; i++ ) {
      obj = objs[ i ];
      if ( player_has_object( player, obj_get_id( obj ) ) ) {
        ui_box_put( ui, box, "@{!0;1;%s;%s}%s@{0}", PLAYER_BAG_OBJ_FG, GAME_INFO_BG, obj_get_name( obj ) );
        if ( j < set_get_total( bag ) - 1 ) {
          ui_box_put( ui, box, ", " );
        }
        j++;
      }
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

  for ( i=0; i < t_objs; i++ ) {

    obj = objs[ i ];


    if ( !space_has_object( cu_sp, obj_get_id( obj ) ) ) continue;

    len = strlen( obj_get_name( obj ) );

    if ( ui_box_get_cx( ui, box )+len >= x+cell_w-13 ) {
      ui_box_seek( ui, box, _x, _y++ );
    }

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


  }

  ui_rs( ui );

}


void parse_info( G_engine *ge, Game *game, int box ) {

  Ui *ui;
  int len;
  Cmd *cmd;
  char *tstr;
  Space *cu_sp;
  Player *player;
  RuleAns ans;
  char *t_name;

  long max_uses;
  Object *obj;

  if ( !ge || !game )
    return;

  ui = ge->game_ui;
  cmd = game_get_cmd( game );

  player = game_get_player( game );
  cu_sp = game_get_space( game, player_get_location( player ) );

  ui_clear_box( ui, GAME_PICTURE );
  ui_clear_box( ui, GAME_INFO );
  tstr = (char*)cmd_get_argv( cmd, 1 );

  if ( !strcmp( tstr, "-s" ) ) {

    ui_box_bg( ui, GAME_INFO, "%s", GAME_INFO_BG );
    ui_frms( ui, "0;1;brgb(124, 182, 0);frgb(0,0,0)" );
    ui_box_put( ui, GAME_INFO, " SPACE INSPECTION\n@{0}" );

    ui_box_put( ui, GAME_INFO, "@{!0;%s;frgb(150,150,150)}name@{0}: %s, ", GAME_INFO_BG, space_get_name( cu_sp ) );
    ui_box_put( ui, GAME_INFO, "@{!0;%s;frgb(150,150,150)}light@{0}: %s\n", GAME_INFO_BG, space_get_light( cu_sp ) ? "on" : "off" );
    ui_box_put( ui, GAME_INFO, "@{!0;%s;frgb(150,150,150)}description@{0}: ", GAME_INFO_BG );

    ans = can_show_space_descrp( game );


    if ( ans == _OBJ_NOT_IN_BAG ) {
      ui_box_put( ui, GAME_INFO, "you need a @{1}map@{0} to see detailed description\n" );
    } else if ( ans == _RULE_YES ) {
      ui_box_put( ui, GAME_INFO, "%s\n", space_get_ldescrp( cu_sp ) );
    }

    t_name = (char*)space_get_picture_file( cu_sp );
    len = t_name ? strlen( t_name ) : 0;

    if ( len ) {
      ui_box_bg( ui, GAME_PICTURE, "%s", GAME_PICTURE_BG );
      dump_file_to_box( ui, GAME_PICTURE, t_name );
      ui_dump_box( ui, GAME_PICTURE );
    }

  } else if ( !strcmp( tstr, "-o" ) ) {

    ui_box_bg( ui, GAME_INFO, "%s", GAME_INFO_BG );
    ui_frms( ui, "0;1;brgb(124, 182, 0);frgb(0,0,0)" );
    ui_box_put( ui, GAME_INFO, " OBJECT INSPECTION\n@{0}" );

    tstr = (char*) cmd_get_argv( cmd, 2 );
    obj = game_get_object_by_name( game, tstr );

    if ( !obj ) {
      ui_box_put( ui, GAME_INFO, "object '%s' does not exists", tstr );
    } else {

      ui_box_put( ui, GAME_INFO, "@{!0;%s;frgb(150,150,150)}name@{0}: %s, ", GAME_INFO_BG, obj_get_name( obj ) );

      max_uses = obj_get_attr( obj, OBJ_MAX_USES );

      if ( max_uses > 0 ) {
        ui_box_put( ui, GAME_INFO, "@{!0;%s;frgb(150,150,150)}used@{0}: %ld of @{1}%ld@{0}, ", GAME_INFO_BG, obj_get_attr( obj, OBJ_USED ), max_uses );
      }

      ui_box_put( ui, GAME_INFO, "@{!0;%s;frgb(150,150,150)}movable@{0}: %s\n", GAME_INFO_BG, obj_get_attr( obj, OBJ_IS_MOVABLE ) == OBJ_YES ? "yes" : "no" );
      ui_box_put( ui, GAME_INFO, "@{!0;%s;frgb(150,150,150)}description@{0}: ", GAME_INFO_BG );

      ans = can_show_object_descrp( game, obj );

      if ( ans == _OBJ_NOT_IN_BAG ) {
        ui_box_put( ui, GAME_INFO, "you need a @{1}book@{0} to see detailed description\n" );
      } else if ( ans == _OBJ_IS_OUTWORN ) {
        ui_box_put( ui, GAME_INFO, "you can't inspect objects anymore!\n" );
      } else if ( ans == _RULE_YES || ans == _OBJ_SELF ) {
        if ( obj_get_attr( obj, OBJ_IS_MOVED ) == OBJ_YES ) {
          ui_box_put( ui, GAME_INFO, "%s\n", obj_get_ldescrp( obj ) );
        } else {
          ui_box_put( ui, GAME_INFO, "%s\n", obj_get_descrp( obj ) );
        }
      } else {
        ui_box_put( ui, GAME_INFO, "\n" );
      }

      t_name = (char*)obj_get_picture_file( obj );
      len = t_name ? strlen( t_name ) : 0;

      if ( len ) {
        ui_box_bg( ui, GAME_PICTURE, "%s", GAME_PICTURE_BG );
        dump_file_to_box( ui, GAME_PICTURE, t_name );
        ui_dump_box( ui, GAME_PICTURE );

      }

    }

  }

}

void dump_file_to_box( Ui *ui, int box, char *f_name ) {

  FILE *f;
  char _buff[ 124 ];

  if ( !ui || !f_name )
    return;

  f = fopen( f_name, "r" );

  if ( !f )
    return;

  while ( fgets( _buff, sizeof( _buff ), f ) ) {
    ui_box_put( ui, box, "%s", _buff );
  }

  fclose( f );

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


  if ( game_finished( game ) == _PLAYER_IS_ALIVE ) {
    dump_file_to_box( ui, GAME_FULLSCREEN, "ascii/ascii_success" );
    ui_dump_box( ui, GAME_FULLSCREEN );
  } else if ( game_finished( game ) == _PLAYER_IS_DEATH ) {
    dump_file_to_box( ui, GAME_FULLSCREEN, "ascii/ascii_death" );
    ui_dump_box( ui, GAME_FULLSCREEN );
  }


  /* prints all the data into stdout */
  ui_draw( stdout, ui );

}
