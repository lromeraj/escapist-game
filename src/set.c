#include <stdio.h>
#include <stdlib.h>
#include "set.h"


struct _Set {
  Id ids[ MAX_SET ];
  int total;
};

Set* set_create() {
  Set *set;
  int i;

  set = (Set*)malloc(sizeof(Set));

  if (!set) {
    fprintf(stderr, "ERROR WHILE ALLOC. MEM - SET\n");
    return NULL;
  }

  for ( i=0; i < MAX_SET; i++ ) {
    set->ids[ i ] = NO_ID;
  }

  set->total = 0;

  return set;
}

void set_destroy( Set *set ){
  if ( !set )
    return;
  free( set );
}

STATUS set_add_id( Set *set, Id id ){

  int i;

  if ( !set )
    return ERROR;

  if ( set_is_full( set ) || set_has_id( set, id ) )
    return ERROR;

  for ( i=0; i < MAX_SET; i++ ) {

    if ( set->ids[ i ] == NO_ID ) {
      set->ids[ i ] = id;
      set->total++;
      return OK;
    }

  }

  return ERROR;
}

Id set_get_first( Set *set ) {

  int i;
  if ( !set || set_is_empty( set ) )
    return NO_ID;

  for ( i=0; i < MAX_SET; i++ ) {
    if ( set->ids[ i ] != NO_ID )
      return set->ids[ i ];
  }

  return NO_ID;

}

bool set_has_id( Set *set, Id id ) {
  int i;

  if ( !set )
    return false;

  for ( i=0; i < MAX_SET; i++ ) {
    if ( set->ids[ i ] == id )
      return true;
  }

  return false;
}

STATUS set_del_id( Set *set, Id id ){

  int i;

  if ( !set )
    return ERROR;

  for (i=0; i < MAX_SET; i++ ) {

    if ( set->ids[ i ] == id ) {
      set->ids[ i ] = NO_ID;
      set->total--;
      return OK;
    }

  }

  return ERROR;
}

int set_get_total( Set *set ) {
  if ( !set ) {
    return -1;
  }
  return set->total;
}

bool set_is_full( Set *set ) {

  if ( !set ) {
    return false;
  }

  if ( set->total >= MAX_SET ) {
    return true;
  }

  return false;
}

bool set_is_empty( Set *set ){
  if ( !set ) {
    return false;
  }
  if ( !set->total ) {
    return true;
  }
  return false;
}

int set_print( FILE *stream, Set *set ) {
  int i, bytes=0;

  if ( !set )
    return ERROR;

  bytes+=fprintf( stream, "SET: " );
  bytes+=fprintf( stream, "[" );
  for ( i=0; i < MAX_SET; i++ ) {
    if ( i == MAX_SET-1 ) {
      bytes+=fprintf(stream, "%ld", set->ids[ i ] );
    } else {
      bytes+=fprintf(stream, "%ld, ", set->ids[ i ] );
    }
  }
  bytes+=fprintf( stream, "]\n" );
  bytes+=fprintf( stream, "TOTAL: %d\n", set_get_total( set ));

  return bytes;
}
