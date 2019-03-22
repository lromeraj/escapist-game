/**
 * @brief Die's module dynamic
 *
 * Defines functions responsible of constrolling a die
 * @file die.c
 * @version 0.0.3
 * @date 10/03/2019
 * @author Javier Romera
 * @copyright GNU Public License
 */

 #include "die.h"
 #include <stdio.h>
 #include <stdlib.h>

 /*!
 * @brief Die structure which contains information about Die
 */

 struct _Die {
   Id id; /*!< @brief Die's id */
   int last_n; /*!< @brief Die's last number rolled */
 };

 Die *die_init() {

   Die *d = (Die*) malloc( sizeof( Die ) );

   if ( d ) {
     d->id = NO_ID;
     d->last_n = 0;
   }

   return d;

 }

 void die_destroy( Die *d ) {
   if ( !d ) return;
   free( d );
 }

 int die_roll( Die *d ) {

   int n;
   if ( !d )
     return -1;

   n = rand() % 6 + 1;

   d->last_n = n;

   return n;

 }

 const int die_get_lastn( Die *die ) {

   if (!die)
     return -1;

   return die->last_n;
 }
