/**
 * @brief Player testbench, valuates each player function for each case
 *
 * @file object_tb.c
 * @version 1.0.0
 * @date 5/04/2019
 * @author Álvaro Rodríguez
 * @copyright GNU Public License
 */

#include "player.h"
#include "set.h"
#include "types.h"
#include "ui.h"
#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define MAX_PLAYERS 2 /*!< @brief Default maxumum players */
#define MAX_PLAYER_OBJ 2 /*!< @brief Default maximum player objects */
#define MAX_POS 20 /*!< @brief Default maximum positions */
#define MAX_OBJ 10 /*!< @brief Default maximum objects */
#define NAMES 30 /*!< @brief Default total name */
#define MAX_SIZE 50 /*!< @brief Default name length */
#define ERR_TB 2 /*!< @brief Default error testbench loop */

int i = 0, r = 0, t = 0;
Id pos = NO_ID;
Id id = NO_ID;
Id obj = NO_ID;
Id name = NO_ID;

char names[NAMES][MAX_SIZE] = {"Akali", "Alistar", "Brand", "Caitlyn", "Fizz", "Galio", "Katarina", "Lux", "Morgana", "Ryze", "Jynx", "Ekko", "Illaoi", "Hecarim", "Heimerdinger", "Kha'Zix", "Kindred", "Leona", "LeBlanc", "Nautilus", "Olaf", "Neeko", "Nidalee", "Rek'Sai", "Rengar", "Sejuani", "Tristana", "Twisted Fate", "Yasuo", "Faker"}; /*!< @brief Default names */

/*!
* @brief Enumeration for case select.
*/

typedef enum{
  NORMAL = 1,
  UNINITIALIZED,
  ALL,
  EXIT
} OPTION;

/**
* @brief Cleans array passed as argument
* @author Álvaro Rodríguez
* @param {Player**} players - players identificator
* @retval Returns a state
*/

STATUS main_clean( Player **players );

/**
* @brief Prints player information
* @author Álvaro Rodríguez
* @param {Player*} player - player identificator
* @retval Returns a state
*/

STATUS main_print( Player *player );

/**
* @brief Test player module with valid values
* @author Álvaro Rodríguez
* @param {Player**} players - players identificator
* @retval Returns a state
*/

STATUS main_valid( Player **players );

/**
* @brief Test player module with non-valid values
* @author Álvaro Rodríguez
* @param {Player**} players - players identificator
* @retval Returns a state
*/

STATUS main_err( Player **player );

/**
* @brief Test main function, contains a case select
* @author Álvaro Rodríguez
* @param {int} argc - number of arguments
* @param {int} argv[] - arguments
* @retval Returns a integer
*/

int main( int argc, char *argv[] ) {

  Player *players[MAX_PLAYERS];

  int opcode;

  srand( time(NULL) );

  opcode = 0;

  for ( i = 0; i < MAX_PLAYERS; i++) {
    players[i] = NULL;
  }

  do {
    fprintf(stdout, "\033[43m\n\n\t\t\t\tPLAYER DEBUG\n\033[0m\n\n" );
    fprintf( stdout, "\033[6mSelect test (1, 2, 3, 4):\033[0m\n\t\033[4m1. Normal values\033[0m\n\t\033[4m2. Null values\033[0m\n\t\033[4m3. All\n\t\033[0m\033[4m4. Exit\033[0m\n\n" );
    fprintf( stdout, "Operation: " );
    scanf("%d", &opcode);

     switch ( opcode ) {
       case NORMAL:
         fprintf(stdout, "\n\033[34mRunning with normal initialitation...\033[0m\n" );
         if ( main_valid( players ) == ERROR) {
           return 1;
         }
         if ( main_clean( players ) == ERROR ) {
           return 1;
         }
       break;
       case UNINITIALIZED:
         fprintf(stdout, "\n\033[34mRunning with invalid initialitation ( uninitialized players and invalid information to object function )...\033[0m\n" );
         if ( main_err( players ) == ERROR ) {
           fprintf(stdout, "\033[31mError in main_err funtion\033[0m\n" );
           return 1;
         }
         if ( main_clean( players ) == ERROR ) {
           return 1;
         }
       break;
       case ALL:
        fprintf(stdout, "\n\033[34mRunnning all...\033[0m\n");
        fprintf(stdout, "\n\033[34mRunning with normal initialitation...\033[0m\n" );
        if ( main_valid( players ) == ERROR) {
          return 1;
        }
        if ( main_clean( players ) == ERROR ) {
          return 1;
        }
        fprintf(stdout, "\n\033[34mRunning with invalid initialitation ( uninitialized players and invalid information to players )...\033[0m\n" );
        if ( main_err( players ) == ERROR ) {
          fprintf(stdout, "\033[31mError in main_err funtion\033[0m\n" );
          return 1;
        }
        if ( main_clean( players ) == ERROR ) {
          return 1;
        }
       break;
       case EXIT:
        fprintf(stdout, "\033[2mExiting...\033[0m\n");
       break;
       default:
        fprintf(stdout, "\n\033[31mUnknown operation. Exiting...\033[0m\n" );
        return 1;
     }

  }while ( opcode != EXIT );

	return 0;
}

STATUS main_clean( Player **players ){

  int n = 1;

  fprintf(stdout, "\n\033[1mRemoving players...\033[0m \n");

  for ( i = 0; i < MAX_PLAYERS; i++) {
    if ( players[i] != NULL ) {
      n = 0;
      break;
    }
  }

  if ( n == 1 ) {
    fprintf( stdout, "\033[1mNo players to be removed.\n" );
    return OK;
  }

  for(i = 0; i < MAX_PLAYERS; i++){
    if ( players[i] != NULL ) {
      if ( player_destroy( players[i] ) == ERROR ) {
        fprintf(stdout, "\033[31mClean failure.\033[0m \n\n");
        return ERROR;
      }
      players[i] = NULL;
    }
  }

  fprintf(stdout, "\033[1mClean done!\033[0m \n\n");

  return OK;
}

STATUS main_valid( Player **players ){

  for (i = 0; i < MAX_PLAYERS; i++) {

    pos = rand() % MAX_POS +1;
    name = rand() % NAMES;
    id = i + 1;

    fprintf(stdout,"\n\n\033[1mTesting now with player[%d]\033[0m\n", i + 1 );

    players[i] = player_create( id );

    if ( !players[i] ) {
      fprintf(stdout, "Error while player[%d] initialitation \n", i+1 );
      return ERROR;
    }

    fprintf(stdout, "\nCorrect player[%d] initialitation.\n", i+1 );

    if ( player_get_id( players[i] ) != id ) {
      fprintf(stdout, "Error while getting player's[%d] id {player_create function failure} \n", i+1 );
      return ERROR;
    }

    player_set_id( players[i] , id );

    if ( player_get_id( players[i] ) != id ) {
      fprintf(stdout, "Error while getting player's[%d] id {player_set_id function failure} \n", i+1 );
      return ERROR;
    }

    fprintf(stdout, "Correct player's[%d] id initialitation.\n", i+1 );

    if ( player_set_name( players[i], names[name] ) == ERROR ) {
      fprintf(stdout, "Error while setting player's[%d] name \n", i+1 );
      return ERROR;
    }

    if ( player_get_name( players[i] ) == NULL || strcmp( player_get_name( players[i] ), names[name] ) ) {
      fprintf(stdout, "Error while getting player's[%d] name \n", i+1 );
      return ERROR;
    }

    fprintf(stdout, "Correct player's[%d] name initialitation.\n", i+1 );

    if ( player_set_location( players[i], pos ) == ERROR ) {
      fprintf(stdout, "Error while setting player's[%d] location \n", i+1 );
      return ERROR;
    }

    if ( player_get_location( players[i] ) != pos ) {
      fprintf(stdout, "Error while getting player's[%d] location \n", i+1 );
      return ERROR;
    }

    fprintf(stdout, "Correct player's[%d] location initialitation.\n", i+1 );

    for ( t = 0; t < MAX_PLAYER_OBJ ; t++ ) {
      obj = rand() % MAX_OBJ + 1;
      if ( player_has_object( players[i], obj) == false ) {
        if ( player_add_object( players[i], obj ) == ERROR ) {
          fprintf( stdout, "Error while adding object %d to player[%d]  \n", (int)obj, i+1 );
          return ERROR;
        }
        if ( player_has_object( players[i], obj ) == false ) {
          fprintf(stdout, "Error while adding object %d to player[%d].\n", (int)obj, i+1 );
          return ERROR;
        }
        fprintf(stdout, "Correct player's[%d] object %d initialitation.\n", i + 1, (int)obj );
      }
    }

    fprintf( stdout, "\n" );
    fprintf( stdout, "\033[0;33mSupposed values for player[%d]\033[0m:\n\n Name: %s\n ID: %d\n ", i + 1, names[name], (int)id );
    fprintf(stdout, "Objects: ");
    for ( t = 1; t <= MAX_OBJ; t++) {
      if ( player_has_object( players[i], t ) == true ) {
        fprintf(stdout, "%d ", t);
      }
    }
    fprintf(stdout, "\n" );
    fprintf(stdout, " Location: %d\n", (int)pos );
  }

  for( i = 0; i < MAX_PLAYERS; i++){
    fprintf(stdout, "\n\033[1mNow printing player[%d]'s information\033[0m (initialised)\n", i + 1 );
    if ( main_print( players[i] ) == ERROR ) {
      return ERROR;
    }
  }

  return OK;
}

STATUS main_err( Player **players ){

  Player *p[ERR_TB];
  Player *_pobj;

  _pobj = NULL;

  for ( i = 0; i < ERR_TB; i++) {
    p[i] = NULL;
  }

  for ( i = 0; i < ERR_TB; i++) {
    p[i] = player_create( i + 1 );
    if ( !p[i] ) {
      fprintf(stdout, "\n\033[031mError while setting up main_err function\033[0m\n" );
      return ERROR;
    }
  }

  for (i = 0; i < ERR_TB; i++) {
    pos = rand() % MAX_POS +1;
    name = rand() % NAMES;
    id = i + 1;

    fprintf(stdout,"\n\033[1mTesting now with player[%d]\033[0m\n\n", i + 1 );

    player_set_id( players[i] , id );

    fprintf(stdout, "\n\033[032mPassing uninitialized player or player with invalid id to player_get_id\033[0m\n" );

    fprintf(stdout, "\t\033[33mExpected player[%d]'s id:\033[0m: %d\n", (int)id, (int)id );

    if ( player_get_id ( players[i] ) != NO_ID || player_get_id ( p[i] ) == NO_ID ) {
      fprintf(stdout, "\t\033[31mReturn value from player_get_id was not as expected to be.\033[0m\n\n" );
      return ERROR;
    }

    fprintf(stdout, "\t\033[35mReturn value of player[%d]'s id:\033[0m: NO_ID\n\n", i + 1 );

    fprintf(stdout, "\033[032mPassing uninitialized player or invalid name to player_set_name\033[0m\n" );

    fprintf(stdout, "\t\033[33mExpected return value of player_set_name:\033[0m: ERROR\n" );

    if ( player_set_name( players[i], names[name] ) == OK || player_set_name( p[i], NULL ) ) {
      fprintf(stdout, "\t\033[31mReturn value from player_set_name was not as expected to be.\033[0m\n" );
      return ERROR;
    }

    fprintf(stdout, "\t\033[35mReturn value of player_set_name:\033[0m: ERROR\n\n" );

    fprintf(stdout, "\033[032mPassing uninitialized player or player with no name to player_get_name\033[0m\n" );

    fprintf(stdout, "\t\033[33mExpected player[%d]'s name:\033[0m: NULL\n", i + 1 );

    if ( player_get_name( players[i] ) != NULL || strlen( player_get_name( p[i] ) ) != 0 ) {
      fprintf(stdout, "\t\033[31mReturn value from player_get_name was not as expected to be.\033[0m\n" );
      return ERROR;
    }

    fprintf(stdout, "\t\033[35mReturn value of player[%d]'s name:\033[0m: NULL\n\n", i + 1 );

    fprintf(stdout, "\033[032mPassing uninitialized player or non valid id to player_set_location\033[0m\n" );

    fprintf(stdout, "\t\033[33mExpected return value of player_set_location:\033[0m: ERROR\n" );

    if ( player_set_location( players[i], pos ) == OK || player_set_location( p[i], NO_ID ) == OK ) {
      fprintf(stdout, "\t\033[31mReturn value from player_set_location was not as expected to be.\033[0m\n" );
      return ERROR;
    }

    fprintf(stdout, "\t\033[35mReturn value of player_set_location:\033[0m: ERROR\n\n" );

    fprintf(stdout, "\033[032mPassing uninitialized player or player with invalid location to player_get_location\033[0m\n" );

    fprintf(stdout, "\t\033[33mExpected player[%d]'s location:\033[0m: NO_ID\n", i + 1 );

    if ( player_get_location( players[i] ) !=NO_ID ) {
      fprintf(stdout, "\t\033[31mReturn value from player_get_location was not as expected to be.\033[0m\n" );
      return ERROR;
    }

    fprintf(stdout, "\t\033[35mReturn value of player[%d]'s location:\033[0m: NO_ID\n\n", i + 1 );


    for (t = 0; t < MAX_PLAYER_OBJ; t++) {
      obj = rand() % MAX_OBJ +1;

      fprintf(stdout, "\033[032mPassing uninitialized player or player with invalid object to player_add_object\033[0m\n" );

      fprintf(stdout, "\t\033[33mExpected value of player[%d]'s object[%d]  by player_add_object:\033[0m: ERROR \n", i + 1, t );

      if ( player_add_object( players[i], obj ) == OK || player_add_object( p[i], NO_ID ) == OK ) {
        fprintf(stdout, "\t\033[31mReturn value from player_add_object was not as expected to be.\033[0m\n" );
        return ERROR;
      }

      fprintf(stdout, "\t\033[35mReturn value of player[%d]'s object[%d] by player_add_object:\033[0m: ERROR\n\n", i + 1, t );

      fprintf(stdout, "\033[032mPassing uninitialized player or player with object to player_has_object\033[0m\n" );

      fprintf(stdout, "\t\033[33mExpected value of player[%d]'s object[%d] by player_has_object:\033[0m: false\n", i + 1, t );

      if ( player_has_object( players[i], t) == true || player_has_object( p[i], t ) == true ) {
        fprintf(stdout, "\t\033[31mReturn value from player_has_object was not as expected to be.\033[0m\n" );
        return ERROR;
      }

      fprintf(stdout, "\t\033[35mReturn value of player[%d]'s object[%d] by player_has_object:\033[0m: false\n\n", i + 1, t );
    }
  }

  for( i = 0; i < ERR_TB; i++){
    fprintf(stdout, "\n\033[1mNow printing player[%d]'s information\033[0m \033[9m(initialised)\033[0m\n\n", i + 1 );

    fprintf(stdout, "\033[032mPassing uninitialized player  to player_print\033[0m\n" );

    fprintf(stdout, "\t\033[33mExpected value of player[%d]'s information print:\033[0m: ERROR {no information}\n", i + 1 );

    if ( main_print( players[i] ) == OK ) {
      fprintf(stdout, "\t\033[31mReturn value from player_print was not as expected to be.\033[0m\n" );
      return ERROR;
    }

    fprintf(stdout, "\n\033[032mPassing player with just id to player_print\033[0m\n\n" );

    if ( main_print( p[i] ) == ERROR ) {
      fprintf(stdout, "\t\033[31mReturn value from player_print was not as expected to be.\033[0m\n" );
      return ERROR;
    }

    fprintf(stdout, "\t\033[33mExpected value of player[%d]'s information print:\033[0m: OK {id only}\n", i + 1 );

    fprintf(stdout, "\n\t\033[35mReturn value of player[%d]'s information print:\033[0m: OK {id only}\n", i + 1 );
  }

  if ( main_clean( p ) == ERROR ) {
    fprintf(stdout, "\t\033[31mError while removing players. Exiting...\033[0m\n" );
    return ERROR;
  }

  _pobj = player_create( 1 );

  if ( !_pobj ) {
    fprintf(stdout, "\t\033[31mError while preparing object test. Exiting...\033[0m\n" );
    return ERROR;
  }

  player_set_location( _pobj, 1 );

  player_set_name( _pobj, "PlayerObjTest" );

  fprintf(stdout, "\n\033[1mPreparing inventory test for player:\033[0m\n\n" );

  for( i = 0; i < MAX_OBJ; i++ ){

    fprintf(stdout, "\033[5mSTATUS: %d out of %d total objects loading:\033[0m\n", i + 1, MAX_OBJ );

    obj = rand() % MAX_OBJ + 1;

    if ( i < MAX_PLAYER_OBJ ) {
      fprintf(stdout, "\033[035mInserting object %d to player [%d out of %d objects]...\033[0m\n\n", (int)obj, i + 1, MAX_PLAYER_OBJ );

      if ( player_has_object( _pobj, obj ) == true ) {
        fprintf(stdout, "\033[033m\tPlayer has this object already!\033[0m\n\n" );
        continue;
      }

      if ( player_add_object( _pobj, obj ) == ERROR ) {
        fprintf(stdout, "\t\033[31mError while inserting object. Exiting...\033[0m\n\n" );
        return ERROR;
      }
      fprintf(stdout, "\033[032m\tObject %d inserted to player [%d out of %d objects]...\033[0m\n\n", (int)obj, i + 1, MAX_PLAYER_OBJ );
    }
    else if ( i >= MAX_PLAYER_OBJ ) {
      fprintf(stdout, "\033[035mInserting object %d to player [OBJECT SHOULDN'T BE INSERTED]...\033[0m\n\n", (int)obj );

      if ( player_has_object( _pobj, obj ) == true ) {
        fprintf(stdout, "\033[033m\tPlayer has this object already!\033[0m\n\n" );
        continue;
      }

      if ( player_add_object( _pobj, obj ) == ERROR ) {
        fprintf(stdout, "\t\033[34mObject couldn't be inserted. Max reached!...\033[0m\n\n" );
        continue;
      }
      else if( player_add_object( _pobj, obj ) == OK ) {
        fprintf(stdout, "\t\033[31mObject inserted when max reached! Exiting...\033[0m\n" );
        return ERROR;
      }
    }
  }

  if ( main_print( _pobj ) == ERROR ) {
    fprintf(stdout, "\t\033[31mError while printing player information. Exiting...\033[0m\n" );
    return ERROR;
  }

  fprintf(stdout, "\n\033[1mObject test status: OK.\033[0m\n\n" );

  player_destroy( _pobj );

  return OK;

}

STATUS main_print( Player *player ){

  if (!player) {
    return ERROR;
  }

  if ( player_get_id( player ) == NO_ID ) {
    fprintf(stdout, "\t\033[31mNo information to print\033[0m\n" );
    return ERROR;
  }

  fprintf( stdout, "\033[1;36mPlayer[%d]'s\033[0m \033[1;31mname:\033[0m %s\n", (int)player_get_id( player ), player_get_name( player ) );

  fprintf( stdout, "\033[1;36mPlayer[%d]'s\033[0m \033[1;32mid:\033[0m %d\n", (int)player_get_id( player ), (int)player_get_id( player ) );

  fprintf(stdout, "\033[1;36mPlayer[%d]'s\033[0m \033[1;32mobjects: \033[0m ", (int)player_get_id( player ) );

  for ( t = 1; t <= MAX_OBJ; t++) {
    if ( player_has_object( player, t ) == true ) {
      fprintf(stdout, "%d ", t);
    }
  }

  fprintf(stdout, "\n" );

  fprintf( stdout, "\033[1;36mPlayer[%d]'s\033[0m \033[1;34mlocation:\033[0m %d\n", (int)player_get_id( player ), (int)player_get_location( player ) );

  fprintf(stdout, "\n");

  return OK;
}
