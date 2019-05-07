/**
 * @brief Main for test the link
 *
 * @file link_tb.c
 * @author Miguel Rodríguez
 * @version 1.0
 * @date 18/03/2019
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "test.h"
#include "link.h"
#include "types.h"

#define MAX_TESTS 15
#define ID 1

struct _Link {
  Id id; /*!< Id of the link */
  char name[ MAX_LINK_NAME ]; /*!< Name of the link */
  Id from; /*!< Id sucessor of the link */
  Id to; /*!< Id destination of the link */
  LinkState state; /*!< State of the link OPEN or CLOSE */
};

/**
 * @test creates a Link on an Link
 * @pre The integer -1 as parameter
 * @post A null pointer to the created link
 */
void test1_Link_create();

/**
 * @test creates a Link on an Link
 * @pre The integer 1 as parameter
 * @post A pointer to the created link
 */
void test2_Link_create();

/**
 * @test set an id to a link
 * @pre A link pointer and an the integer -1 as parameters
 * @post An ERROR
 */
void test1_Link_set_id();

/**
 * @test set an id to a link
 * @pre A link pointer and an the integer 1 as parameters
 * @post An OK
 */
void test2_Link_set_id();

/**
 * @test set a name
 * @pre A null link pointer and a name as parameters
 * @post An ERROR
 */
void test1_Link_set_name();

/**
 * @test set a name
 * @pre A link pointer and a name as parameters
 * @post A OK
 */
void test2_Link_set_name();

/**
 * @test set the link to
 * @pre A null link pointer and a integer as parameters
 * @post An ERROR
 */
void test1_Link_set_to();

/**
 * @test set the link to
 * @pre A link pointer and a integer as parameters
 * @post An OK
 */
void test2_Link_set_to();

/**
 * @test set the link from
 * @pre A null link pointer and a integer as parameters
 * @post An ERROR
 */
void test1_Link_set_from();

/**
 * @test set the link from
 * @pre A link pointer and a integer as parameters
 * @post A OK
 */
void test2_Link_set_from();

/**
 * @test set link state
 * @pre A null link pointer and a integer as parameters
 * @post An ERROR
 */
void test1_Link_set_state();

/**
 * @test set link state
 * @pre A link pointer and a integer as parameters
 * @post An OK
 */
void test2_Link_set_state();

/**
 * @test Print the link fields
 * @pre A null link pointer as parameter
 * @post An ERROR
 */
void test1_Link_print();

/**
 * @test Print the link fields
 * @pre A link pointer as parameter
 * @post An OK
 */
void test2_Link_print();

/**
 * @test Gets the link id
 * @pre A null link pointer as parameter
 * @post The integer -1
 */
void test1_Link_get_id();

/**
 * @test Gets the link id
 * @pre A link pointer as parameter
 * @post The id of the link
 */
void test2_Link_get_id();

/**
 * @test Gets the id of the field link to
 * @pre A null link pointer as parameter
 * @post The integer -1
 */
void test1_Link_get_to();

/**
 * @test Gets the id of the field link to
 * @pre A link pointer as parameter
 * @post The link_to id
 */
void test2_Link_get_to();

/**
 * @test Gets the id of the field link_from
 * @pre A null link pointer as parameter
 * @post The integer -1
 */
void test1_Link_get_from();

/**
 * @test Gets the id of the field link_from
 * @pre A link pointer as parameter
 * @post The link_from id
 */
void test2_Link_get_from();

/**
 * @test Gets the state of the link
 * @pre A null link pointer as parameter
 * @post Link close
 */
void test1_Link_get_state();

/**
 * @test Gets the state of the link
 * @pre A link pointer as parameter
 * @post Link sate
 */
void test2_Link_get_state();


/**
 * @brief Funcion principal de pruebas para el modulo Link.
 *
 * Dos modos de ejecucion:
 *   1.-Si se ejecuta sin parametros se ejecutan todas las pruebas
 *   2.-Si se ejecuta con un numero entre 1 y el numero de pruebas solo ejecuta
 *      la prueba indicada
 *
 */

 int main(int argc, char** argv) {

     int test = 0;
     int all = 1;

     if (argc < 2) {
         printf("Running all test for module Link:\n");
     }
     else {
         test = atoi(argv[1]);
         all = 0;
         printf("Running test %d:\t", test);
 	if (test < 1 && test > MAX_TESTS) {
 	  printf("Error: unknown test %d\t", test);
 	  exit(EXIT_SUCCESS);
         }
     }


     if (all || test == 1) test1_Link_create();
     if (all || test == 2) test2_Link_create();
     if (all || test == 3) test1_Link_set_id();
     if (all || test == 4) test2_Link_set_id();
     if (all || test == 5) test1_Link_set_name();
     if (all || test == 6) test2_Link_set_name();
     if (all || test == 7) test1_Link_set_to();
     if (all || test == 8) test2_Link_set_to();
     if (all || test == 9) test1_Link_set_from();
     if (all || test == 10) test2_Link_set_from();
     if (all || test == 11) test1_Link_set_state();
     if (all || test == 12) test2_Link_set_state();
     if (all || test == 13) test1_Link_print();
     if (all || test == 14) test2_Link_print();
     if (all || test == 15) test1_Link_get_id();
     if (all || test == 16) test2_Link_get_id();
     if (all || test == 17) test1_Link_get_to();
     if (all || test == 18) test2_Link_get_to();
     if (all || test == 19) test1_Link_get_from();
     if (all || test == 20) test2_Link_get_from();
     if (all || test == 21) test1_Link_get_state();
     if (all || test == 22) test2_Link_get_state();

     PRINT_PASSED_PERCENTAGE;

     return 1;
 }

 void test1_Link_create(){
   Link *l;
   int result = OK;
   l = link_create(-1);
   if (!l){
     result=0;
   }
   PRINT_TEST_RESULT(result);
   link_destroy(l);
 }

 void test2_Link_create(){
   Link *l;
   int result = OK;
   l = link_create(ID);
   if (!l){
     result=0;
   }
   PRINT_TEST_RESULT(result);
   link_destroy(l);
 }

 void test1_Link_set_id(){
   Link *l;
   l = link_create(ID);
   PRINT_TEST_RESULT(link_set_id(l, NO_ID));
   link_destroy(l);
 }

 void test2_Link_set_id(){
   Link *l;
   l = link_create(ID);
   PRINT_TEST_RESULT(link_set_id(l, 1) == OK);
   link_destroy(l);
 }

 void test1_Link_set_name(){
   Link *l;
   l = NULL;
   PRINT_TEST_RESULT(link_set_name(l, "East"));
   link_destroy(l);
 }

 void test2_Link_set_name(){
   Link *l;
   l = link_create(ID);
   PRINT_TEST_RESULT(link_set_name(l,"North"));
   link_destroy(l);
 }

 void test1_Link_set_to(){
   Link *l;
   l = link_create(ID);
   PRINT_TEST_RESULT(link_set_to(l, NO_ID));
   link_destroy(l);
 }

 void test2_Link_set_to(){
   Link *l;
   l = link_create(ID);
   PRINT_TEST_RESULT(link_set_to(l, 2));
   link_destroy(l);
 }

 void test1_Link_set_from(){
   Link *l=NULL;

   PRINT_TEST_RESULT(link_set_from(l, NO_ID));
   link_destroy(l);
 }

 void test2_Link_set_from(){
   Link *l;
   l = link_create(ID);
   PRINT_TEST_RESULT(link_set_from(l, 3));
   link_destroy(l);
 }

 void test1_Link_set_state(){
   Link *l=NULL;

   PRINT_TEST_RESULT(link_set_state(l, 0));
   link_destroy(l);
 }

 void test2_Link_set_state(){
   Link *l;
   l = link_create(ID);
   PRINT_TEST_RESULT(link_set_state(l, 20));
   link_destroy(l);
 }

 void test1_Link_print(){
   Link *l = NULL;
   PRINT_TEST_RESULT(link_print(stdout, l));

 }

 void test2_Link_print(){
   Link *l;
   l = link_create(ID);
   link_set_id(l, 1);
   link_set_name(l, "South");
   link_set_to(l, 3);
   link_set_from(l, 2);
   link_set_state(l, 1);
   PRINT_TEST_RESULT(link_print(stdout, l));
   link_destroy(l);
 }

 void test1_Link_get_id(){
   Link *l;
   l = link_create(ID);
   link_set_id(l, 2);
   PRINT_TEST_RESULT(link_get_id(l)==1);
   link_destroy(l);
 }

 void test2_Link_get_id(){
   Link *l;
   l = link_create(ID);
   link_set_id(l, 1);
   PRINT_TEST_RESULT(link_get_id(l)==1);
   link_destroy(l);
 }

 void  test1_Link_get_to(){
   Link *l;
   l = link_create(ID);
   link_set_to(l, 2);
   PRINT_TEST_RESULT(link_get_to(l)==1);
   link_destroy(l);
 }

 void test2_Link_get_to(){
   Link *l;
   l = link_create(ID);
   link_set_to(l, 1);
   PRINT_TEST_RESULT(link_get_to(l)==1);
   link_destroy(l);
 }

 void test1_Link_get_from(){
   Link *l;
   l = link_create(ID);
   link_set_from(l, 2);
   PRINT_TEST_RESULT(link_get_from(l)==1);
   link_destroy(l);
 }

 void test2_Link_get_from(){
   Link *l;
   l = link_create(ID);
   link_set_from(l, 1);
   PRINT_TEST_RESULT(link_get_from(l)==1);
   link_destroy(l);
 }

 void test1_Link_get_state(){
   Link *l;
   l = link_create(ID);
   link_set_state(l, 2);
   PRINT_TEST_RESULT(link_get_state(l)==1);
   link_destroy(l);
 }

 void test2_Link_get_state(){
   Link *l;
   l = link_create(ID);
   link_set_state(l, 1);
   PRINT_TEST_RESULT(link_get_state(l)==1);
   link_destroy(l);
 }
