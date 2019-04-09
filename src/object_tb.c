/**
 * @brief Object testbench evaluates each object function for each case
 *
 * @file object_tb.c
 * @version 1.0.0
 * @date 7/04/2019
 * @author Álvaro Rodríguez
 * @copyright GNU Public License
 */

#include "object.h"
#include "types.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define MAX_OBJ 2 /*!< @brief Default maxumum objects */
#define ERR_TB 2 /*!< @brief Default error testbench loop */
#define NAMES 30 /*!< @brief Default total name */
#define DESCRIPTIONS 30 /*!< @brief Default total descriptions */

int i = 0, r = 0, t = 0;
Id id = NO_ID;
Id name_id = NO_ID;
Id desc_id = NO_ID;
char name[MAX_OBJ_NAME];
char desc[MAX_OBJ_DESCRP];

char names[NAMES][MAX_OBJ_NAME] = {"Botas", "Armadura", "Anillo", "Baston", "Amuleto", "Ancla", "Brazalete", "Capa", "Pergamino", "Eter", "Cetro", "Chaleco", "Coraza", "Cimitarra", "Brazal", "Cristal", "Cinturon", "Caliz", "Cefiro", "Codice", "Cronometro", "Daga", "Sello", "Elixir", "Escudo", "Estandarte", "Galleta", "Guantelete", "Grebas", "Reloj"}; /*!< @brief Default names */
char descriptions[DESCRIPTIONS][MAX_OBJ_DESCRP] = {"Para los pies", "Para el cuerpo", "Para el dedo", "Para sujeccion", "Para suerte", "Para barco", "Para brazo", "Para espalda", "Para guiarte", "Para disolver", "Para ataque", "Para tiempo", "Para proteccion", "Para ataque", "Para brazo", "Para videncia", "Para sujeccion", "Para beber", "Para viento", "Para biblioteca", "Para tiempo", "Para ataque", "Para carta", "Para pocima", "Para proteccion", "Para comer", "Para mano", "Para piernas", "Para tiempo"}; /*!< @brief Default descriptions */

/**
* @brief Cleans array passed as argument
* @author Álvaro Rodríguez
* @param {Object**} objects - objects identificator
* @retval Returns a state
*/

STATUS main_clean( Object **objects );

/**
* @brief Prints object information
* @author Álvaro Rodríguez
* @param {Object*} objects - object identificator
* @retval Returns a state
*/

STATUS main_print( Object *object );

/**
* @brief Test object module with valid values
* @author Álvaro Rodríguez
* @param {Object**} objects - objects identificator
* @retval Returns a state
*/

STATUS main_valid( Object **objects );

/**
* @brief Test object module with non-valid values
* @author Álvaro Rodríguez
* @param {Object**} objects - objects identificator
* @retval Returns a state
*/

STATUS main_err( Object **objects );

/**
* @brief Test main function, contains a case select
* @author Álvaro Rodríguez
* @param {int} argc - number of arguments
* @param {int} argv[] - arguments
* @retval Returns a integer
*/

int main( int argc, char *argv[] ) {

  Object *objects[MAX_OBJ];

  srand( time(NULL) );

  for ( i = 0; i < MAX_OBJ; i++) {
    objects[i] = NULL;
  }

  fprintf(stdout, "\033[43m\n\n\t\t\t\tOBJECT DEBUG\n\033[0m\n\n" );

  if ( main_valid( objects ) == ERROR ) {
    fprintf(stdout, "\033[31m\nError in main_valid function\n\033[0m\n\n" );
    return 1;
  }

  if ( main_clean( objects ) == ERROR ) {
    fprintf(stdout, "\033[31m\nError in main_clean function\n\033[0m\n\n" );
    return 1;
  }

  if ( main_err( objects ) == ERROR ) {
    fprintf(stdout, "\033[31m\nError in main_err function\n\033[0m\n\n" );
    return 1;
  }

  fprintf(stdout, "\n\033[1mObject test status: OK.\033[0m\n" );

  fprintf(stdout, "\033[1m\nTest gone through no errors\n\033[0m\n" );

	return 0;
}

STATUS main_clean( Object **objects ){

  int n = 1;

  fprintf(stdout, "\n\033[1mRemoving objects...\033[0m \n");

  for ( i = 0; i < MAX_OBJ; i++) {
    if ( objects[i] != NULL ) {
      n = 0;
      break;
    }
  }

  if ( n == 1 ) {
    fprintf( stdout, "\033[1mNo objects to be removed.\n" );
    return OK;
  }

  for(i = 0; i < MAX_OBJ; i++){
    if ( objects[i] != NULL ) {
      obj_destroy( objects[i] );
      objects[i] = NULL;
    }
  }

  fprintf(stdout, "\033[1mClean done!\033[0m \n\n");

  return OK;
}

STATUS main_valid( Object **objects ){

  fprintf(stdout, "\n\033[34mRunning with normal initialitation...\033[0m\n" );

  for (i = 0; i < MAX_OBJ; i++) {

    name_id = rand() % NAMES;

    id = i + 1;

    fprintf(stdout,"\n\n\033[1mTesting now with object[%d]\033[0m\n", i + 1 );

    objects[i] = obj_create( id );

    if ( !objects[i] ) {
      fprintf(stdout, "Error while object[%d] initialitation \n", i+1 );
      return ERROR;
    }

    fprintf(stdout, "\nCorrect object[%d] initialitation.\n", i+1 );

    if ( obj_get_id( objects[i] ) != id ) {
      fprintf(stdout, "Error while getting object's[%d] id {obj_create function failure} \n", i+1 );
      return ERROR;
    }

    obj_set_id( objects[i] , id );

    if ( obj_get_id( objects[i] ) != id ) {
      fprintf(stdout, "Error while getting object's[%d] id {obj_set_id function failure} \n", i+1 );
      return ERROR;
    }

    fprintf(stdout, "Correct object's[%d] id initialitation.\n", i+1 );

    obj_set_name( objects[i], names[name_id] );

    if ( obj_get_name( objects[i] ) == NULL || strcmp( obj_get_name( objects[i] ), names[name_id] ) ) {
      fprintf(stdout, "Error while getting object's[%d] name \n", i+1 );
      return ERROR;
    }

    fprintf(stdout, "Correct object's[%d] name initialitation.\n", i+1 );

    obj_set_descrp( objects[i], descriptions[name_id] );

    if ( obj_get_descrp( objects[i] ) == NULL || strcmp( obj_get_descrp( objects[i] ), descriptions[name_id] ) ) {
      fprintf(stdout, "Error while getting object's[%d] description. \n", i+1 );
      return ERROR;
    }

    fprintf(stdout, "Correct object's[%d] description initialitation.\n", i+1 );

    fprintf( stdout, "\n" );
    fprintf( stdout, "\033[0;33mSupposed values for object[%d]\033[0m:\n\n Name: %s\n ID: %d\n Description: %s\n", i + 1, names[name_id], (int)id, descriptions[name_id] );
  }

  for( i = 0; i < MAX_OBJ; i++){
    fprintf(stdout, "\n\033[1mNow printing object[%d]'s information\033[0m (initialised)\n", i + 1 );
    if ( main_print( objects[i] ) == ERROR ) {
      return ERROR;
    }
  }

  return OK;
}

STATUS main_err( Object **objects ){

  Object *o[ERR_TB];

  fprintf(stdout, "\n\033[34mRunning with invalid initialitation ( uninitialized objects and invalid information to object functions )...\033[0m\n" );

  for ( i = 0; i < ERR_TB; i++) {
    o[i] = NULL;
  }

  for ( i = 0; i < ERR_TB; i++) {
    o[i] = obj_create( i + 1 );
    if ( !o[i] ) {
      fprintf(stdout, "\n\033[031mError while setting up main_err function\033[0m\n" );
      return ERROR;
    }
  }

  for (i = 0; i < ERR_TB; i++) {

    name_id = rand() % NAMES;
    id = i + 1;

    fprintf(stdout,"\n\033[1mTesting now with object[%d]\033[0m\n\n", i + 1 );

    obj_set_id( objects[i] , id );

    fprintf(stdout, "\n\033[032mPassing uninitialized object or object with id to obj_get_id\033[0m\n" );

    fprintf(stdout, "\t\033[33mExpected object[%d]'s id:\033[0m: NO_ID\n", i + 1 );

    if ( obj_get_id ( objects[i] ) != NO_ID || obj_get_id ( o[i] ) == NO_ID ) {
      fprintf(stdout, "\t\033[31mReturn value from object_get_id was not as expected to be.\033[0m\n\n" );
      return ERROR;
    }

    fprintf(stdout, "\t\033[35mReturn value of object[%d]'s id:\033[0m: NO_ID\n\n", i + 1 );

    fprintf(stdout, "\033[032mPassing uninitialized object or invalid name to obj_set_name\nand then getting it.\n\033[0m\n" );

    obj_set_name( objects[i], names[name_id] );

    obj_set_name( o[i], NULL );

    fprintf(stdout, "\033[032mPassing uninitialized object or object with no name to obj_get_name\033[0m\n" );

    fprintf(stdout, "\t\033[33mExpected object[%d]'s name:\033[0m: NULL\n", i + 1 );

    if ( obj_get_name( objects[i] ) != NULL || strlen( obj_get_name( o[i] ) ) != 0 ) {
      fprintf(stdout, "\t\033[31mReturn value from obj_get_name was not as expected to be.\033[0m\n" );
      return ERROR;
    }

    fprintf(stdout, "\t\033[35mReturn value of object[%d]'s name:\033[0m: NULL\n\n", i + 1 );

    fprintf(stdout, "\033[032mPassing uninitialized object or invalid description to obj_set_descrp\nand then getting it.\n\033[0m\n" );

    obj_set_descrp( objects[i], descriptions[name_id] );

    obj_set_descrp( o[i], NULL );

    fprintf(stdout, "\033[032mPassing uninitialized object or object with no name to obj_get_descrp\033[0m\n" );

    fprintf(stdout, "\t\033[33mExpected object[%d]'s description:\033[0m: NULL\n", i + 1 );

    if ( obj_get_descrp( objects[i] ) != NULL || strlen( obj_get_descrp( o[i] ) ) != 0 ) {
      fprintf(stdout, "\t\033[31mReturn value from obj_get_descrp was not as expected to be.\033[0m\n" );
      return ERROR;
    }

    fprintf(stdout, "\t\033[35mReturn value of object[%d]'s description:\033[0m: NULL\n\n", i + 1 );

  }

  for( i = 0; i < ERR_TB; i++){

    fprintf(stdout, "\n\033[1mNow printing object[%d]'s information\033[0m \033[9m(initialised)\033[0m\n\n", i + 1 );

    fprintf(stdout, "\033[032mPassing uninitialized object to object_print\033[0m\n" );

    fprintf(stdout, "\t\033[33mExpected value of object[%d]'s information print:\033[0m: ERROR {no information}\n", i + 1 );

    if ( main_print( objects[i] ) == OK ) {
      fprintf(stdout, "\t\033[31mReturn value from object_print was not as expected to be.\033[0m\n" );
      return ERROR;
    }

    fprintf(stdout, "\n\033[032mPassing object with just id to object_print\033[0m\n\n" );

    if ( main_print( o[i] ) == ERROR ) {
      fprintf(stdout, "\t\033[31mReturn value from object_print was not as expected to be.\033[0m\n" );
      return ERROR;
    }

    fprintf(stdout, "\t\033[33mExpected value of object[%d]'s information print:\033[0m: OK {id only}\n", i + 1 );

    fprintf(stdout, "\n\t\033[35mReturn value of object[%d]'s information print:\033[0m: OK {id only}\n", i + 1 );
  }

  for( i = 0; i < ERR_TB; i++){
    obj_destroy( o[i] );
  }

  return OK;

}

STATUS main_print( Object *object ){

  if (!object) {
    return ERROR;
  }

  if ( obj_get_id( object ) == NO_ID ) {
    fprintf(stdout, "\t\033[31mNo information to print\033[0m\n" );
    return ERROR;
  }

  fprintf( stdout, "\033[1mPrinting information...\033[0m\n\n" );

  fprintf( stdout, "\033[1;36mObject[%d]'s\033[0m \033[1;31mname:\033[0m %s\n", (int)obj_get_id( object ), obj_get_name( object ) );

  fprintf( stdout, "\033[1;36mObject[%d]'s\033[0m \033[1;32mid:\033[0m %d\n", (int)obj_get_id( object ), (int)obj_get_id( object ) );

  fprintf( stdout, "\033[1;36mObject[%d]'s\033[0m \033[1;34mdescription:\033[0m %s\n", (int)obj_get_id( object ), obj_get_descrp( object ) );

  fprintf(stdout, "\n");

  return OK;
}
