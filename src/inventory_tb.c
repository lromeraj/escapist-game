/**
 * @brief Main for test the inventory
 *
 * @file inventory_tb.c
 * @author Gonzalo Serrano
 * @version 1.0
 * @date 18/03/2019
 */

 #ifndef _TEST_H
#define _TEST_H

#pragma GCC diagnostic ignored "-Wpedantic"

#ifndef NOCOLOR
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KCYN  "\x1B[36m"
#define RESET "\033[0m"
#else
#define KRED
#define KGRN
#define KYEL
#define KCYN
#define RESET
#endif

#define PRINT_TEST_RESULT(x) do{\
    __test_counter++; \
    __pass = (x); \
    __test_passed = (__pass)? __test_passed + 1 : __test_passed;\
    printf(KYEL "%s" RESET " line "  "%d " KCYN "%s" RESET ": %s\n", \
	   __FILE__, __LINE__ , __FUNCTION__, \
	   ((!__pass) ? KRED "NOT PASS" RESET : KGRN "PASS" RESET));	\
  } while (0)

#define PRINT_PASSED_PERCENTAGE printf("Tests passed %d%%\n", ((__test_passed * 100) / __test_counter))

static int __test_counter = 0;
static int __test_passed  = 0;
static int __pass = 0;

#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inventory.h"
#include "types.h"

#define MAX_TESTS 17

/**
* @brief creates a inventory on an integer
* @author Gonzalo Serrano
* @param {void}
* @retval {void}
*/
void test1_inventory_create();
/**
* @brief creates a inventory on an inventory
* @author Gonzalo Serrano
* @param {void}
* @retval {void}
*/
void test2_inventory_create();
/**
* @brief add an invalid id
* @author Gonzalo Serrano
* @param {void}
* @retval {void}
*/
void test1_inventory_add_id();
/**
* @brief add a valid id
* @author Gonzalo Serrano
* @param {void}
* @retval {void}
*/
void test2_inventory_add_id();
/**
* @brief deletes an invalid id
* @author Gonzalo Serrano
* @param {void}
* @retval {void}
*/
void test1_inventory_del_id();
/**
* @brief deletes a valid id
* @author Gonzalo Serrano
* @param {void}
* @retval {void}
*/
void test2_inventory_del_id();
/**
* @brief searches an invalid id
* @author Gonzalo Serrano
* @param {void}
* @retval {void}
*/
void test1_inventory_has_id();
/**
* @brief deletes a valid id
* @author Gonzalo Serrano
* @param {void}
* @retval {void}
*/
void test2_inventory_has_id();
/**
* @brief get a invalid number of objects
* @author Gonzalo Serrano
* @param {void}
* @retval {void}
*/
void test1_inventory_get_max();
/**
* @brief get the maximun number of objects
* @author Gonzalo Serrano
* @param {void}
* @retval {void}
*/
void test2_inventory_get_max();
/**
* @brief get an invalid total
* @author Gonzalo Serrano
* @param {void}
* @retval {void}
*/
void test1_inventory_get_total();
/**
* @brief get the total number of objects
* @author Gonzalo Serrano
* @param {void}
* @retval {void}
*/
void test2_inventory_get_total();
/**
* @brief compares if the inventory is full or not (in this case is not empty)
* @author Gonzalo Serrano
* @param {void}
* @retval {void}
*/
void test1_inventory_is_full();
/**
* @brief compares if the inventory is full or not (Empty)
* @author Gonzalo Serrano
* @param {void}
* @retval {void}
*/
void test2_inventory_is_full();
/**
* @brief compares if the inventory is empty or not (not empty)
* @author Gonzalo Serrano
* @param {void}
* @retval {void}
*/
void test1_inventory_is_empty();
/**
* @brief compares if the inventory is empty or not (empty)
* @author Gonzalo Serrano
* @param {void}
* @retval {void}
*/
void test2_inventory_is_empty();

/**
 * @brief Funcion principal de pruebas para el modulo Inventory.
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
         printf("Running all test for module Inventory:\n");
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


     if (all || test == 1) test1_inventory_create();
     if (all || test == 2) test2_inventory_create();
     if (all || test == 3) test1_inventory_add_id();
     if (all || test == 4) test2_inventory_add_id();
     if (all || test == 5) test1_inventory_del_id();
     if (all || test == 6) test2_inventory_del_id();
     if (all || test == 7) test1_inventory_has_id();
     if (all || test == 8) test2_inventory_has_id();
     if (all || test == 9) test1_inventory_get_max();
     if (all || test == 10) test2_inventory_get_max();
     if (all || test == 11) test1_inventory_get_total();
     if (all || test == 12) test2_inventory_get_total();
     if (all || test == 13) test1_inventory_is_full();
     if (all || test == 14) test2_inventory_is_full();
     if (all || test == 15) test1_inventory_is_empty();
     if (all || test == 16) test2_inventory_is_empty();

     PRINT_PASSED_PERCENTAGE;

     return 1;
 }

 void test1_inventory_create(){
   int result = inventory_create()!=NULL ;
   result = NULL;
   PRINT_TEST_RESULT(result);
 }

 void test2_inventory_create(){
   Inventory *i;
   int result = OK;
   i = inventory_create();
   if (i!=NULL){
   PRINT_TEST_RESULT(result);
   inventory_destroy(i);
   }
 }

 void test1_inventory_add_id(){
   Inventory *i;
   i = inventory_create();
   PRINT_TEST_RESULT(inventory_add_id(i, "hola") == ERROR);
   inventory_destroy(i);
 }

 void test2_inventory_add_id(){
   Inventory *i;
   i = inventory_create();
   PRINT_TEST_RESULT(inventory_add_id(i, 1) == OK);
   inventory_destroy(i);
 }

 void test1_inventory_del_id(){
   Inventory *i;
   i = inventory_create();
   inventory_add_id(i, 1);
   PRINT_TEST_RESULT(inventory_del_id(i, 2));
   inventory_destroy(i);
 }

 void test2_inventory_del_id(){
   Inventory *i;
   i = inventory_create();
   inventory_add_id(i, 1);
   PRINT_TEST_RESULT(inventory_del_id(i, 1));
   inventory_destroy(i);
 }

 void test1_inventory_has_id(){
   Inventory *i;
   i = inventory_create();
   inventory_add_id(i, 1);
   PRINT_TEST_RESULT(inventory_has_id(i, 2));
   inventory_destroy(i);
 }

 void test2_inventory_has_id(){
   Inventory *i;
   i = inventory_create();
   inventory_add_id(i, 1);
   PRINT_TEST_RESULT(inventory_has_id(i, 1));
   inventory_destroy(i);
 }

 void test1_inventory_get_max(){
   Inventory *i;
   i = inventory_create();
   PRINT_TEST_RESULT(inventory_get_max(i) == -1);
   inventory_destroy(i);
 }

 void test2_inventory_get_max(){
   Inventory *i;
   i = inventory_create();
   PRINT_TEST_RESULT(inventory_get_max(i) == 5);
   inventory_destroy(i);
 }

 void test1_inventory_get_total(){
   Inventory *i;
   i = inventory_create();
   inventory_add_id(i, 1);
   inventory_add_id(i, 2);
   PRINT_TEST_RESULT(inventory_get_total(i) == 1);
   inventory_destroy(i);
 }

 void test2_inventory_get_total(){
   Inventory *i;
   i = inventory_create();
   inventory_add_id(i, 1);
   PRINT_TEST_RESULT(inventory_get_total(i) == 1);
   inventory_destroy(i);
 }

 void test1_inventory_is_full(){
   Inventory *i;
   i = inventory_create();
   inventory_add_id(i, 1);
   PRINT_TEST_RESULT(inventory_is_full(i));
   inventory_destroy(i);
 }

 void test2_inventory_is_full(){
   Inventory *i;
   i = inventory_create();
   inventory_add_id(i, 1);
   inventory_add_id(i, 2);
   inventory_add_id(i, 3);
   inventory_add_id(i, 4);
   inventory_add_id(i, 5);
   PRINT_TEST_RESULT(inventory_is_full(i));
   inventory_destroy(i);
 }

 void test1_inventory_is_empty(){
   Inventory *i;
   i = inventory_create();
   inventory_add_id(i, 1);
   PRINT_TEST_RESULT(inventory_is_empty(i));
   inventory_destroy(i);
 }

 void test2_inventory_is_empty(){
   Inventory *i;
   bool result;
   i = inventory_create();
   result = inventory_is_empty(i);
   PRINT_TEST_RESULT( result );
   inventory_destroy(i);
 }
