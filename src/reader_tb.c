/**
 * @brief Reader testbench evaluates each object function for each case
 *
 * @file object_tb.c
 * @version 1.0.0
 * @date 7/04/2019
 * @author Álvaro Rodríguez
 * @copyright GNU Public License
 */

#include "reader.h"
#include "types.h"
#include "game.h"
#include "space.h"
#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define MAX_NAME 50 /*!< Id of the link */

int i;

/**
* @brief Runs the test
* @author Álvaro Rodríguez
* @param {Game*} game - game pointer
* @param {char*} f_name - file name
* @retval Returns a state
*/

STATUS main_test( Game *game, char *f_name );

/**
* @brief Cleans data passed as argument
* @author Álvaro Rodríguez
* @param {Game*} game - game pointer
* @retval Returns a state
*/

STATUS main_clean( Game *game );

int main(int argc, char *argv[]) {

  Game *game;
  char f_name[MAX_NAME];

  game = NULL;

  strcpy(f_name, ".rtb_data.dat");

  srand( time(NULL) );

  fprintf(stdout, "\033[43m\n\n\t\t\t\tREADER DEBUG\n\033[0m\n\n" );

  game = game_create();

  if ( !game ) {
    fprintf(stdout, "\033[31m\nError while creating game\n\033[0m\n\n" );
    return 1;
  }

  if ( main_test( game, f_name ) == ERROR ) {
    fprintf(stdout, "\033[31m\nError while testing reader\n\033[0m\n\n" );
    return 1;
  }

  return 0;
}

STATUS main_clean( Game *game ){
  if ( !game ) {
    return ERROR;
  }

  fprintf(stdout, "\n\033[1mCleaning...\033[0m \n");

  if ( game_destroy( game ) == ERROR ) {
    fprintf(stdout, "\033[31m\nError while cleaning. Exiting...\n\033[0m\n\n" );
    return ERROR;
  }

  fprintf(stdout, "\033[1mClean done!\033[0m \n");

  return OK;
}

STATUS main_test( Game *game, char *f_name ){

  Link *ln ; /* link pointers */
  Id  ln_id = NO_ID, /* link id */
      ln_from = NO_ID, /* link origin */
      ln_to = NO_ID; /* link destination */
  LinkState ln_state; /* link state */
  Space *space; /* space pointer */
  Object *_oid, *_oname, *object; /* object pointers */
  char space_name[MAX_NAME]; /* space name */
  char object_name[MAX_NAME]; /* object name */
  char space_desc[MAX_NAME]; /* space desc */
  char object_desc[MAX_NAME]; /* object desc */
  char ln_name[MAX_NAME]; /* link name */
  Id obj_id = NO_ID; /* object id */
  Id sp_id = NO_ID; /* space id */
  Id sp_n = NO_ID; /* space north id */
  Id sp_s = NO_ID; /* space south id */
  Id sp_e = NO_ID; /* space east id */
  Id sp_w = NO_ID; /* space west id */
  int len;
  char *pic = NULL;

  space = NULL;
  _oid = NULL;
  _oname = NULL;
  object = NULL;
  ln = NULL;

  strcpy( space_name, "Space 05" );
  strcpy( object_name, "ball" );
  strcpy( ln_name, "Link 01" );
  strcpy( space_desc, "goose area" );
  strcpy( object_desc, "And in the end it's only round 'n round" );
  ln_state = LINK_CLOSED;
  obj_id = 01;
  sp_id = 05;
  sp_n = 8;
  sp_e = 9;
  sp_s = 10;
  ln_id = 01;
  ln_from = 01;
  ln_to = 02;

  if ( !game || !f_name ) {
    fprintf(stdout, "\033[31m\nInvalid arguments to main_test function\n\033[0m\n\n" );
    return ERROR;
  }

  if ( game_create_from_file( game, f_name ) == ERROR ) {
    fprintf(stdout, "\033[31m\nGame create from file failure\n\033[0m\n\n" );
    return ERROR;
  }

  space = game_get_space ( game, 05 );

  if ( !space ) {
    fprintf(stdout, "\033[31m\nError getting space from game\n\033[0m\n\n" );
    return ERROR;
  }

  _oid = game_get_object_by_id ( game, obj_id );

  if ( !_oid ) {
    fprintf(stdout, "\033[31m\nError getting object by id from game\n\033[0m\n\n" );
    return ERROR;
  }

  _oname = game_get_object_by_name ( game, object_name );

  if ( !_oname ) {
    fprintf(stdout, "\033[31m\nError getting object by name from game\n\033[0m\n\n" );
    return ERROR;
  }

  if ( obj_get_id( _oid ) != obj_get_id( _oname ) ) {
    fprintf(stdout, "\033[31m\nError while loading objects by id and name, they're not the same!\n\033[0m\n\n" );
    return ERROR;
  }

  object = _oid;

  ln = game_get_link_by_id( game, i + 1);
  if ( !ln ) {
    fprintf(stdout, "\033[31m\nError getting link %d from game\n\033[0m\n\n", i + 1 );
  }

  /* TESTING SPACE */

  fprintf( stdout, "\n\033[1mTesting space values...\033[0m\n" );

  fprintf(stdout, "\n\033[33mExpected space id:\033[0m: %d\n", (int)sp_id );

  fprintf( stdout, "\033[1;36mSpace\033[0m \033[1;31mid:\033[0m %d\n", (int)space_get_id( space ) );

  if ( space_get_id( space ) != sp_id ) {
    fprintf(stdout, "\033[31m\nSpace id differs from supossed value\n\033[0m\n\n" );
    return ERROR;
  }

  fprintf(stdout, "\n\033[33mExpected space name:\033[0m: %s\n", space_name );

  fprintf( stdout, "\033[1;36mSpace\033[0m \033[1;31mname:\033[0m %s\n", space_get_name( space ) );

  if ( strcmp( space_get_name( space ), space_name ) ) {
    fprintf(stdout, "\033[31m\nSpace name differs from supossed value\n\033[0m\n\n" );
    return ERROR;
  }

  fprintf(stdout, "\n\033[33mExpected space description:\033[0m: %s\n", space_desc );

  fprintf( stdout, "\033[1;36mSpace\033[0m \033[1;31mdescription:\033[0m %s\n", space_get_descrp( space ) );

  if ( strcmp( space_get_descrp( space ), space_desc ) ) {
    fprintf(stdout, "\033[31m\nSpace description differs from supossed\n\033[0m\n\n" );
    return ERROR;
  }

  fprintf(stdout, "\n\033[33mExpected space picture:\033[0m: %s\n", "\n<O)__/ \n \\_-/" );

  fprintf( stdout, "\033[1;36mSpace\033[0m \033[1;31mpicture:\033[0m " );

  pic = space_get_picture( space );

  len = strlen( pic );

  for (i=0; i < len; i++ ) {

    if ( pic[ i ] == '\\' && pic[ i + 1 ] == 'n' ) {
      i++;
      fprintf(stdout, "\n" );
    } else if ( pic[ i ] != '\n' ) {
      fprintf(stdout, "%c", pic[i] );
    }
  }
  fprintf(stdout, "\n" );

  fprintf(stdout, "\n\033[33mExpected space north id:\033[0m: %d\n", (int)sp_n );

  fprintf( stdout, "\033[1;36mSpace\033[0m \033[1;31m north id:\033[0m %d\n", (int)space_get_link( space, N ) );

  if ( space_get_link( space, N ) != sp_n ) {
    fprintf(stdout, "\033[31m\nSpace north id differs from supossed value\n\033[0m\n\n" );
    return ERROR;
  }

  fprintf(stdout, "\n\033[33mExpected space south id:\033[0m: %d\n", (int)sp_s );

  fprintf( stdout, "\033[1;36mSpace\033[0m \033[1;31m south id:\033[0m %d\n", (int)space_get_link( space, S ) );

  if ( space_get_link( space, S ) != sp_s ) {
    fprintf(stdout, "\033[31m\nSpace south id differs from supossed value\n\033[0m\n\n" );
    return ERROR;
  }

  fprintf(stdout, "\n\033[33mExpected space east id:\033[0m: %d\n", (int)sp_e );

  fprintf( stdout, "\033[1;36mSpace\033[0m \033[1;31m east id:\033[0m %d\n", (int)space_get_link( space, E ) );

  if ( space_get_link( space, E ) != sp_e ) {
    fprintf(stdout, "\033[31m\nSpace east id differs from supossed value\n\033[0m\n\n" );
    return ERROR;
  }

  fprintf(stdout, "\n\033[33mExpected space west id:\033[0m: %d\n", (int)sp_w );

  fprintf( stdout, "\033[1;36mSpace\033[0m \033[1;31m west id:\033[0m %d\n", (int)space_get_link( space, W ) );

  if ( space_get_link( space, W ) != sp_w ) {
    fprintf(stdout, "\033[31m\nSpace west id differs from supossed value\n\033[0m\n\n" );
    return ERROR;
  }

  /* TESTING OBJECT */

  fprintf( stdout, "\n\n\033[1mTesting object values...\033[0m\n" );

  fprintf(stdout, "\n\033[33mExpected object id:\033[0m: %d\n", (int)obj_id );

  fprintf( stdout, "\033[1;36mObject\033[0m \033[1;31mid:\033[0m %d\n", (int)obj_get_id( object ) );

  if ( obj_get_id( object ) != obj_id ) {
    fprintf(stdout, "\033[31m\nObject id differs from supossed value\n\033[0m\n\n" );
    return ERROR;
  }

  fprintf(stdout, "\n\033[33mExpected object name:\033[0m: %s\n", object_name );

  fprintf( stdout, "\033[1;36mObject\033[0m \033[1;31mname:\033[0m %s\n", obj_get_name( object ) );

  if ( strcmp( obj_get_name( object ), object_name ) ) {
    fprintf(stdout, "\033[31m\nObject name differs from supossed value\n\033[0m\n\n" );
    return ERROR;
  }

  fprintf(stdout, "\n\033[33mExpected object description:\033[0m: %s\n", object_desc );

  fprintf( stdout, "\033[1;36mObject\033[0m \033[1;31mdescription:\033[0m %s\n", obj_get_descrp( object ) );

  if ( strcmp( obj_get_descrp( object ), object_desc ) ) {
    fprintf(stdout, "\033[31m\nObject description differs from supossed\n\033[0m\n\n" );
    return ERROR;
  }

  /* LINK TEST */

  fprintf( stdout, "\n\n\033[1mTesting link values...\033[0m\n" );

  fprintf(stdout, "\n\033[33mExpected link id:\033[0m: %d\n", (int)ln_id );

  fprintf( stdout, "\033[1;36mLink\033[0m \033[1;31mid:\033[0m %d\n", (int)link_get_id( ln ) );

  if ( link_get_id( ln ) != ln_id ) {
    fprintf(stdout, "\033[31m\nLink id differs from supossed value\n\033[0m\n\n" );
    return ERROR;
  }

  fprintf(stdout, "\n\033[33mExpected link name:\033[0m: %s\n", ln_name );

  fprintf( stdout, "\033[1;36mLink\033[0m \033[1;31mname:\033[0m %s\n", link_get_name( ln ) );

  if ( strcmp( link_get_name( ln ), ln_name ) ) {
    fprintf(stdout, "\033[31m\nLink name differs from supossed value\n\033[0m\n\n" );
    return ERROR;
  }

  fprintf(stdout, "\n\033[33mExpected link id from:\033[0m: %d\n", (int)ln_from );

  fprintf( stdout, "\033[1;36mLink\033[0m \033[1;31mid from:\033[0m %d\n", (int)link_get_from( ln ) );

  if ( link_get_from( ln ) != ln_from ) {
    fprintf(stdout, "\033[31m\nLink id from differs from supossed value\n\033[0m\n\n" );
    return ERROR;
  }

  fprintf(stdout, "\n\033[33mExpected link id to:\033[0m: %d\n", (int)ln_to );

  fprintf( stdout, "\033[1;36mLink\033[0m \033[1;31mid to:\033[0m %d\n", (int)link_get_to( ln ) );

  if ( link_get_to( ln ) != ln_to ) {
    fprintf(stdout, "\033[31m\nLink id to differs from supossed value\n\033[0m\n\n" );
    return ERROR;
  }

  fprintf(stdout, "\n\033[33mExpected link state:\033[0m: %s\n", ln_state == LINK_OPENED ? "OPENED" : "CLOSED" );

  fprintf( stdout, "\033[1;36mLink\033[0m \033[1;31mstate:\033[0m %s\n", link_get_state( ln ) == LINK_OPENED ? "OPENED" : "CLOSED" );

  if ( link_get_state( ln ) != ln_state ) {
    fprintf(stdout, "\033[31m\nLink state differs from supossed value\n\033[0m\n\n" );
    return ERROR;
  }

  /* END OF THE TEST */

  if ( main_clean( game ) == ERROR ) {
    return ERROR;
  }

  fprintf( stdout, "\n\n\033[1mTest gone through no errors.\033[0m\n\n" );

  return OK;
}
