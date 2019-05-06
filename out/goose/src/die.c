#include "die.h"
#include <stdio.h>
#include <stdlib.h>


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
