/**
 * @brief Main for test the space
 *
 * @file space_tb.c
 * @author Miguel Rodríguez
 * @version 1.0
 * @date 05/05/2019
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "space.h"
 #include "space_tb.h"
 #include "test.h"

 #define MAX_TESTS 42

 int main(int argc, char** argv) {

     int test = 0;
     int all = 1;

     if (argc < 2) {
         printf("Running all test for module space:\n");
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


     if (all || test == 1) test1_space_create();
     if (all || test == 2) test2_space_create();
     if (all || test == 3) test1_space_destroy();
     if (all || test == 4) test2_space_destroy();
     if (all || test == 5) test1_space_get_id();
     if (all || test == 6) test2_space_get_id();
     if (all || test == 7) test1_space_set_name();
     if (all || test == 8) test2_space_set_name();
     if (all || test == 9) test1_space_get_descrp();
     if (all || test == 10) test2__space_get_descrp();
     if (all || test == 11) test1_space_get_ldescrp();
     if (all || test == 12) test2_space_get_ldescrp();
     if (all || test == 13) test1_space_get_objects();
     if (all || test == 14) test2_space_get_objects();
     if (all || test == 15) test1_space_set_descrp();
     if (all || test == 16) test2_space_set_descrp();
     if (all || test == 17) test1_space_set_ldescrp();
     if (all || test == 18) test2_space_set_ldescrp();
     if (all || test == 19) test1_space_get_name();
     if (all || test == 20) test2_space_get_name();
     if (all || test == 21) test1_space_get_link();
     if (all || test == 22) test2_space_get_link();
     if (all || test == 23) test1_space_set_link();
     if (all || test == 24) test2_space_set_link();
     if (all || test == 25) test1_space_del_object();
     if (all || test == 26) test2_space_del_object();
     if (all || test == 27) test1_space_add_object();
     if (all || test == 28) test2_space_add_object();
     if (all || test == 29) test1_space_get_object();
     if (all || test == 30) test2_space_get_object();
     if (all || test == 31) test1_space_has_object();
     if (all || test == 32) test2_space_has_object();
     if (all || test == 33) test1_space_set_picture();
     if (all || test == 34) test2_space_set_picture();
     if (all || test == 35) test1_space_get_picture();
     if (all || test == 36) test2_space_get_picture();
     if (all || test == 37) test1_space_set_light();
     if (all || test == 38) test2_space_set_light();
     if (all || test == 39) test1_space_toggle_light();
     if (all || test == 40) test2_space_toggle_light();
     if (all || test == 41) test1_space_get_light();
     if (all || test == 42) test2_space_get_light();



     PRINT_PASSED_PERCENTAGE;

     return 1;
 }


 void test1_space_create(){
   Space *sp;
   int result=1; /*1=OK*/

   sp=space_create(-1);
   if(!sp){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }

 void test2_space_create(){
   Space *sp;
   int result=1;

   sp=space_create(1);
   if(!sp){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }

 void test1_space_destroy(){
   Space *sp=NULL;
   int result=1;

   if(!sp){
     result=0;
   }
   PRINT_TEST_RESULT(result);
 }

 void test2_space_destroy(){
   Space *sp;
   int result=1;

   sp=space_create(1);
   if(!sp){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }

 void test1_space_get_id(){
  Space *sp;
   int result=1;

   sp=space_create(1);

   if(space_get_id(sp)==1){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }

 void test2_space_get_id(){
   Space *sp;
   int result=1;

   sp=space_create(1);

   if(space_get_id(sp)!=1){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }


 void test1_space_set_name(){
   Space *sp;
   int result=1;
   char *pt=NULL;

   sp=space_create(1);

   if(!space_set_name(sp, pt)){
     result=0;
   }
 space_destroy(sp);
 PRINT_TEST_RESULT(result);
 }


 void test2_space_set_name(){
   Space *sp;
   int result=1;
   char *palabra ="hola";

   sp=space_create(1);

   if(!space_set_name(sp, palabra)){
     result=0;
   }
 space_destroy(sp);
 PRINT_TEST_RESULT(result);
 }

 void test1_space_get_descrp(){
   Space *sp=NULL;
   int result=1;
   char *palabra = NULL;

   space_set_descrp(sp, palabra);
   if(!space_get_descrp(sp)){
     result=0;
   }

   PRINT_TEST_RESULT(result);
 }

 void test2__space_get_descrp(){
   Space *sp;
   int result=0;
   char *palabra = "hola";

   sp=space_create(1);
   space_set_descrp(sp, palabra);
   if(space_get_descrp(sp)){
     result=1;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }

 void test1_space_get_ldescrp(){
   Space *sp=NULL;
   int result=1;
   char *palabra = NULL;

   space_set_ldescrp(sp, palabra);
   if(!space_get_ldescrp(sp)){
     result=0;
   }
   PRINT_TEST_RESULT(result);
 }

 void test2_space_get_ldescrp(){
   Space *sp;
   int result=0;
   char *palabra = "hola";

   sp=space_create(1);
   space_set_ldescrp(sp, palabra);
   if(space_get_ldescrp(sp)){
     result=1;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }

 void test1_space_get_objects(){
   Space *sp=NULL;
   int result=1;

   if(!space_get_objects(sp)){
     result=0;
   }
   PRINT_TEST_RESULT(result);
 }

 void test2_space_get_objects(){
   Space *sp;
   int result=1;

   sp=space_create(1);

   if(!space_get_objects(sp)){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }

 void test1_space_set_descrp(){
   Space *sp=NULL;
   int result=1;
   char *palabra = NULL;

   if(!space_set_descrp(sp, palabra)){
     result=0;
   }
   PRINT_TEST_RESULT(result);
 }

 void test2_space_set_descrp(){
   Space *sp=NULL;
   int result=1;
   char *palabra = "hola";

   sp=space_create(1);
   if(!space_set_descrp(sp, palabra)){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }

 void test1_space_set_ldescrp(){
   Space *sp=NULL;
   int result=1;
   char *palabra = NULL;

   if(!space_set_ldescrp(sp, palabra)){
     result=0;
   }
   PRINT_TEST_RESULT(result);
 }

 void test2_space_set_ldescrp(){
   Space *sp=NULL;
   int result=1;
   char *palabra = "hola";

   sp=space_create(1);
   if(!space_set_ldescrp(sp, palabra)){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }

 void test1_space_get_name(){
   Space *sp=NULL;
   int result=1;
   char *name = "hola";

   space_set_name(sp, name);
   if(!space_get_name(sp)){
     result=0;
   }
   PRINT_TEST_RESULT(result);
 }

 void test2_space_get_name(){
   Space *sp=NULL;
   int result=1;
   char *name = "hola";

   sp=space_create(1);
   space_set_name(sp, name);
   if(!space_get_name(sp)){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }

 void test1_space_get_link(){
   Space *sp;
    int result=0;

    sp=space_create(1);
    space_set_link(sp, N, 1);
    if(space_get_link(sp, N)!=1){
      result=1;
    }
    space_destroy(sp);
    PRINT_TEST_RESULT(result);
  }

 void test2_space_get_link(){
   Space *sp;
    int result=1;

    sp=space_create(1);
    space_set_link(sp, N, 1);
    if(space_get_link(sp, S)==1){
      result=0;
    }
    space_destroy(sp);
    PRINT_TEST_RESULT(result);
 }

 void test1_space_set_link(){
   Space *sp;
    int result=1;

    sp=space_create(1);

    if(space_set_link(sp, S, -1)){
      result=0;
    }
    space_destroy(sp);
    PRINT_TEST_RESULT(result);
 }

 void test2_space_set_link(){
   Space *sp;
   int result=1;

   sp=space_create(1);

   if(!space_set_link(sp, N, 1)){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }

 void test1_space_del_object(){
   Space *sp;
   int result=1;

   sp=space_create(1);
   space_add_object(sp, 1);
   if(space_del_object(sp, -1)){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }

 void test2_space_del_object(){
   Space *sp;
   int result=1;

   sp=space_create(1);
   space_add_object(sp, 1);
   if(!space_del_object(sp, 1)){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }

 void test1_space_add_object(){
   Space *sp;
   int result=1;

   sp=space_create(1);

   if( !space_add_object(sp, -1) ){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }

 void test2_space_add_object(){
   Space *sp;
   int result=1;

   sp=space_create(1);

   if( !space_add_object(sp, 1) ){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }

 void test1_space_get_object(){
   Space *sp=NULL;
   int result=1;

   if( space_get_object(sp, 1) ){
     result=0;
   }
   PRINT_TEST_RESULT(result);
 }
 void test2_space_get_object(){
   Space *sp;
   int result=1;

   sp=space_create(1);
   space_add_object(sp, 1);
   if( !space_get_object(sp, 1) ){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }

 void test1_space_has_object(){
   Space *sp=NULL;
   int result=1;

   sp=space_create(1);
   if( !space_has_object(sp,1) ){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }
 void test2_space_has_object(){
   Space *sp=NULL;
   int result=1;

   sp=space_create(1);
   space_add_object(sp, 1);
   if( !space_has_object(sp,1) ){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }
 void test1_space_set_picture(){
   Space *sp=NULL;
   int result=1;
   char *palabra="hola";


   if( !space_set_picture(sp, palabra) ){
     result=0;
   }
   PRINT_TEST_RESULT(result);
 }

 void test2_space_set_picture(){
   Space *sp=NULL;
   int result=1;
   char *palabra="hola";

   sp=space_create(1);
   if( !space_set_picture(sp, palabra) ){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }

 void test1_space_get_picture(){
   Space *sp=NULL;
   int result=1;

   if( !space_get_descrp(sp)){
     result=0;
   }
   PRINT_TEST_RESULT(result);
 }

 void test2_space_get_picture(){
   Space *sp=NULL;
   int result=1;
   char *palabra="hola";

   sp=space_create(1);
   space_set_picture(sp, palabra);
   if( !space_get_picture(sp) ){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }

 void test1_space_set_light(){
   Space *sp=NULL;
   int result=1;

   if( !space_set_light(sp, true)){
     result=0;
   }
   PRINT_TEST_RESULT(result);
 }

 void test2_space_set_light(){
   Space *sp=NULL;
   int result=1;

   sp=space_create(1);
   if( !space_set_light(sp, true)){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }

 void test1_space_toggle_light(){
   Space *sp=NULL;
   int result=1;

   if( !space_toggle_light(sp)){
     result=0;
   }
   PRINT_TEST_RESULT(result);
 }

 void test2_space_toggle_light(){
   Space *sp=NULL;
   int result=1;

   sp=space_create(1);
   if( !space_toggle_light(sp)){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }

 void test1_space_get_light(){
   Space *sp=NULL;
   int result=1;

   if( !space_get_light(sp)){
     result=0;
   }
   PRINT_TEST_RESULT(result);
 }

 void test2_space_get_light(){
   Space *sp=NULL;
   int result=1;

   sp=space_create(1);
   space_set_light(sp, true);
   if( !space_get_light(sp)){
     result=0;
   }
   space_destroy(sp);
   PRINT_TEST_RESULT(result);
 }
