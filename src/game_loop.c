/**
 * @brief Main game loop
 *
 * @file game_loop.c
 * @author Álvaro Rodríguez & Javier Romera
 * @version 1.0
 * @date 07/02/2019
 * @copyright GNU Public License
 */

#include "g_engine.h"
#include "types.h"
#include "log.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <locale.h>
#include <unistd.h>
#include <math.h>
#include <sys/ioctl.h>

/******* PRIVATE_FUNCTIONS ******/

/**
* @brief This function will be executed when a signal is dispatched
* @param {int} sign - Signal id
*/
void ctrl_c();

/**
* @brief This function will free all the memory
* @param {int} errc - Error code
*/
void _kill( int errc );

/********************************/


enum { BOX1, BOX2, BOX3 };
int WIN_ROWS, WIN_COLS, old_r, old_c; /* termial/window size */
Ui *mui; /* main user interface */
Game *game; /* main game */
G_engine *gengine; /* main graphic engine */
struct winsize win; /* terminal window */


void _kill( int errc ) {

  log_w( "*************************\n" );
  log_w( "main loop ended\n" );
  log_w( "freeing memory ...\n" );

  ui_destroy( mui );
  game_destroy( game );
  g_engine_destroy( gengine );

  log_w( "----------- LOG END -----------\n" );

  log_end();

  exit( errc );

}

void ctrl_c() {
  _kill( 1 );
}

void upd_win() {
  struct winsize win;
  ioctl( STDOUT_FILENO, TIOCGWINSZ, &win );
  WIN_COLS = win.ws_col;
  WIN_ROWS = win.ws_row;
}

int main( int argc, char *argv[] ) {

  int i, errc, diff;
  Cmd *_cmd;
  long loop = 0;

  setlocale( LC_ALL, "" );
  signal( SIGINT, ctrl_c );
  srand( time( NULL ) );

  if ( argc < 2 ) {
    fprintf(stderr, "game needs 'data.dat'\n" );
    return 1;
  }

  if ( argc == 4 ) {
    if ( !strcmp("-l", argv[2] ) ) {
      log_begin( argv[3] );
      log_w( "----------- LOG BEGIN -----------\n" );
    }
  }

  log_w( "loading game ... " );

  game = game_create();

  if ( game == NULL ) {
    log_w( "ERR\n" );
    fprintf(stderr, "error while creating game\n");
    _kill( 1 );
  }

  if ( game_load_from_file( game, argv[1] ) == ERROR ) {
    log_w( "ERR\n" );
    fprintf(stderr, "error while initializing game\n");
    _kill( 1 );
  }

  log_w( "OK\n" );

  log_w( "loading graphic engine ... ");
  gengine = g_engine_create();

  if ( gengine == NULL ) {
    log_w( "ERR\n" );
    fprintf(stderr, "error while initializing graphic engine.\n");
    _kill( 1 );
  }


  upd_win();

  mui = ui_init( WIN_COLS, WIN_ROWS-1 );
  ui_new_box( mui, BOX1, 0, 0, WIN_COLS, WIN_ROWS-1 );
  ui_box_frm( mui, BOX1, 2, FG_BLACK, BG_WHITE );

  log_w( "OK\n" );

  while ( !game_is_over( game ) ) {

    log_w( "\n********** L%d **********\n", loop );

    log_w( "drawing frame ...\n" );

    _cmd = game_get_cmd( game );

    upd_win();

    /* check if there is enough space */
    while ( WIN_COLS < MIN_WIN_COLS || WIN_ROWS < MIN_WIN_ROWS ) {

      if ( old_c != WIN_COLS || old_r != WIN_ROWS ) {

        printf("\033c"); /* clear temrinal screen */
        ui_resize( mui, WIN_COLS, WIN_ROWS-1 );
        ui_box_resize( mui, BOX1, WIN_COLS, WIN_ROWS-1 );

        ui_clear_box( mui, BOX1 );
        ui_frm( mui, 3, S_BOLD, BG_RED, FG_WHITE );
        ui_box_put( mui, BOX1, " TERMINAL SIZE IS VERY SMALL\n", WIN_COLS, WIN_ROWS );
        ui_frm( mui, 2, BG_WHITE, FG_BLACK );
        ui_box_put( mui, BOX1, " Minimum size: @{1}%dx%d@{0}\n", 80, 25 );
        ui_box_put( mui, BOX1, " Current: @{1}%dx%d@{0}\n", WIN_COLS, WIN_ROWS );

        diff = MIN_WIN_COLS - WIN_COLS;
        if ( WIN_COLS < MIN_WIN_COLS ) {
          ui_box_put( mui, BOX1, " At least @{1}%d@{0} columns more (width)\n", diff );
        }

        diff = MIN_WIN_ROWS - WIN_ROWS;
        if ( diff > 0 ) {
          ui_box_put( mui, BOX1, " At least @{1}%d@{0} rows more (height)\n", diff );
        }

        ui_box_put( mui, BOX1, "\nTo fix this, just resize the terminal to make it bigger\n", WIN_COLS, WIN_ROWS );

        ui_dump_box( mui, BOX1 );
        ui_draw( stdout, mui );

        old_c = WIN_COLS;
        old_r = WIN_ROWS;
      }

      upd_win();

    }

    /* print different screens depending on the command */
    if ( cmd_get_cid( _cmd ) == HELP ) {
      g_engine_paint_help( gengine, game );
    } else {
      g_engine_paint_game( gengine, game );
    }

    log_w( "requesting cmd ...\n" );

    /* request command */
    _cmd = cmd_req();

    log_w( "updating game data ...\n" );
    game_update( game, _cmd );

    if ( _cmd ) {
      log_w( "$ %s\n", cmd_get_bname( _cmd ) );
      log_w( "   msg: \"%s\"\n", cmd_get_ans( _cmd ) );
      log_w( "   argc: %d\n", cmd_get_argc( _cmd ) );

      if ( cmd_get_argc( _cmd ) > 1 ) {

        log_w( "   argv: " );
        log_w( "{" );

        for ( i=1; i < cmd_get_argc( _cmd ); i++ ) {

          if ( i == cmd_get_argc( _cmd )-1 ) {
            log_w( "'%s'", cmd_get_argv( _cmd, i ) );
          } else {
            log_w( "'%s',", cmd_get_argv( _cmd, i ) );
          }

        }
        log_w( "}\n" );
      }

      errc = cmd_get_errc( _cmd );
      if ( errc == 0 ) {
        log_w( "   exit: OK(%d)\n", errc );
      } else {
        log_w( "   exit: ERR(%d)\n", errc );
      }

      if ( cmd_get_cid( _cmd ) == EXIT )
        break;

    }

    loop++;
  }

  _kill( 0 );

  return EXIT_SUCCESS;
}
