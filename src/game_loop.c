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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <signal.h>


/** Main function of the game, works on a loop while no exit or quit option
* is being introduced.
* Returns 1 if it fails openning data file or graphic engine module,
* returns 0 if the player decides quiting game.
*
* @param {int} argc - number of arguments with which was called the process
* @param {char*} argv - arguments with which was called the process
* @return {int} - returns an error code
*/


/******* PRIVATE_FUNCTIONS ******/

/** This function will be executed when a signal is dispatched
* @param {int} sign - Signal id
*/
void ctrl_c();

/** This function will free all the memory
* @param {void}
*/
void _kill();

/********************************/


Game game;
G_engine *gengine;

void _kill() {

  log_w( "*************************\n" );
  log_w( "main loop ended\n" );
  log_w( "freeing memory ...\n" );

  game_destroy( &game );
  g_engine_destroy( gengine );

  log_w( "----------- LOG END -----------\n" );

  log_end();

}

/* signal handler */
void ctrl_c( int sign ) {
  _kill();
  exit(1);
}

int main( int argc, char *argv[] ) {

  int i, errc;
  Cmd *_cmd;
  long loop = 0;

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

  if ( game_create_from_file( &game, argv[1] ) == ERROR ) {
    log_w( "ERR\n" );
    fprintf(stderr, "error while initializing game\n");
    return 1;
  }
  log_w( "OK\n" );

  log_w( "loading graphic engine ... ");
  if ( ( gengine = g_engine_create() ) == NULL ) {
    log_w( "ERR\n" );
    fprintf(stderr, "error while initializing graphic engine.\n");
    game_destroy( &game );
    return 1;
  }
  log_w( "OK\n" );


  while ( !game_is_over( &game ) ) {

    log_w( "\n********** L%d **********\n", loop );

    g_engine_paint_game( gengine, &game );
    log_w( "drawing frame ...\n" );
    log_w( "requesting cmd ...\n" );
    _cmd = cmd_req();

    log_w( "updating game data ...\n" );
    game_update( &game, _cmd );

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

  _kill();

  return 0;
}
