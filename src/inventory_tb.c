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
 * @test Creates an inventory on an integer
 * @pre inventory set on an integer
 * @post A null pointer to the created inventory
 */
void test1_inventory_create();

/**
 * @test Creates an inventory on an inventory
 * @pre The integer set on an inventory
 * @post A pointer to the created inventory
 */
void test2_inventory_create();

/**
 * @test Add an id to the inventory
 * @pre The integer NO_ID as parameter
 * @post An ERROR to the introduced id
 */
void test1_inventory_add_id();

/**
* @test Add an id to the inventory
 * @pre The integer 1 as parameter
 * @post An OK to the introduced id
 */
void test2_inventory_add_id();

/**
* @test Deletes an id to the inventory
 * @pre The integer 2 as parameter
 * @post An ERROR to the introduced id
 */
void test1_inventory_del_id();

/**
* @test Deletes an id to the inventory
 * @pre The integer 1 as parameter
 * @post An OK to the introduced id
 */
void test2_inventory_del_id();

/**
 * @test Find if the inventory has that id
 * @pre The integer 2 as parameter
 * @post An ERROR to the introduced id
 */
void test1_inventory_has_id();

/**
 * @test Creates a space on an integer
 * @pre The integer 1 as parameter
 * @post An OK to the introduced id
 */
void test2_inventory_has_id();

/**
 * @test Get the maximun cunatity of objects in the inventory
 * @pre The inventory is initialised and and integer id 1 is added
 * @post An OK to the introduced id
 */
void test1_inventory_get_max();

/**
 * @test Get the maximun cunatity of objects in the inventory
 * @pre The inventory is uninitialised
 * @post An ERROR
 */
void test2_inventory_get_max();

/**
 * @test Get the total of objects stored on the inventory
 * @pre The inventory initialised
 * @post An OK to the introduced inventory
 */
void test1_inventory_get_total();

/**
 * @test Get a invalid total of objects stored on the inventory
 * @pre The inventory uninitialised
 * @post An ERROR to the introduced inventory
 */
void test2_inventory_get_total();

/**
 * @test Shows if the inventory is full
 * @pre The integer 1 as parameter
 * @post An ERROR to the introduced inventory
 */
void test1_inventory_is_full();

/**
 * @test Shows if the inventory is full
 * @pre The integer 1 to 6 as parameter
 * @post A OK to the introduced inventory
 */
void test2_inventory_is_full();

/**
 * @test Shows if the inventory is empty without one obj in it
 * @pre inventory as parameter
 * @post An ERROR to the introduced inventory
 */
void test1_inventory_is_empty();

/**
 * @test Shows if the inventory is empty without any obj in it
 * @pre inventory as parameter
 * @post A OK to the introduced inventory
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
   result = 0;
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
   int result=1;

   i = inventory_create();

   if(inventory_add_id(i, NO_ID) == ERROR){
     result=0;
   }

   inventory_destroy(i);
   PRINT_TEST_RESULT(result);
 }

 void test2_inventory_add_id(){
   Inventory *i;
   int result=1;

   i = inventory_create();

   if(inventory_add_id(i, 1) == ERROR){
     result=0;
   }

   inventory_destroy(i);
   PRINT_TEST_RESULT(result);
 }

 void test1_inventory_del_id(){
   Inventory *i;
   int result=1;

   i = inventory_create();
   inventory_add_id(i, 1);

   if(inventory_del_id(i, 2) == ERROR){
     result=0;
   }
   inventory_destroy(i);
   PRINT_TEST_RESULT(result);
 }

 void test2_inventory_del_id(){
   Inventory *i;
   int result=1;

   i = inventory_create();
   inventory_add_id(i, 1);

   if(inventory_del_id(i, 1) == ERROR){
     result=0;
   }

   inventory_destroy(i);
   PRINT_TEST_RESULT(result);
 }

 void test1_inventory_has_id(){
   Inventory *i;
   int result=1;

   i = inventory_create();
   inventory_add_id(i, 1);

   if(inventory_has_id(i, 2) == ERROR){
      result=0;
   }

   inventory_destroy(i);
   PRINT_TEST_RESULT(result);
 }

 void test2_inventory_has_id(){
   Inventory *i;
   int result=1;

   i = inventory_create();
   inventory_add_id(i, 1);

   if(inventory_has_id(i, 1) == ERROR){
     result=0;
   }

   inventory_destroy(i);
   PRINT_TEST_RESULT(result);
 }

 void test1_inventory_get_max(){
   Inventory *i;
   int result=1;
   int max = 6;

   i = inventory_create();

   if(inventory_get_max(i) != max){
     result=0;
   }

   inventory_destroy(i);
   PRINT_TEST_RESULT(result);
 }

 void test2_inventory_get_max(){
   Inventory *i=NULL;
   int result=1;
   int max = 6;

   if(inventory_get_max(i) != max){
     result=0;
   }

   inventory_destroy(i);
   PRINT_TEST_RESULT(result);
 }

 void test1_inventory_get_total(){
   Inventory *i;
   int result=1, nelements=2;

   i = inventory_create();

   inventory_add_id(i, 1);
   inventory_add_id(i, 2);

   if(inventory_get_total(i) != nelements){
     result=0;
   }

   inventory_destroy(i);
   PRINT_TEST_RESULT(result);
 }

 void test2_inventory_get_total(){
   Inventory *i;
   int result=1;

   i = inventory_create();

   if(inventory_get_total(i) == ERROR){
     result=0;
   }

   inventory_destroy(i);
   PRINT_TEST_RESULT(result);
 }

 void test1_inventory_is_full(){
   Inventory *i;
   int result=1;

   i = inventory_create();
   inventory_add_id(i, 1);

   if(inventory_is_full(i) == ERROR){
     result=0;
   }

   inventory_destroy(i);
   PRINT_TEST_RESULT(result);
 }

 void test2_inventory_is_full(){
   Inventory *i;
   int result=1;
   i = inventory_create();
   inventory_add_id(i, 1);
   inventory_add_id(i, 2);
   inventory_add_id(i, 3);
   inventory_add_id(i, 4);
   inventory_add_id(i, 5);
   inventory_add_id(i, 6);

   if(inventory_is_full(i) == ERROR){
     result=0;
   }

   inventory_destroy(i);
   PRINT_TEST_RESULT(result);
 }

 void test1_inventory_is_empty(){
   Inventory *i;
   int result=1;
   i = inventory_create();
   inventory_add_id(i, 1);

   if(inventory_is_empty(i) == ERROR){
     result=0;
   }

   inventory_destroy(i);
   PRINT_TEST_RESULT(result);
 }

 void test2_inventory_is_empty(){
   Inventory *i;
   int result=1;
   i = inventory_create();
   result = inventory_is_empty(i);

   inventory_destroy(i);
   PRINT_TEST_RESULT(result);
 }
