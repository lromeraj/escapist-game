#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STACK 100

struct _Stack {
  void *its[ MAX_STACK ];
  int top;
  stack_destroy_it fn_destroy;
  stack_cpy_it fn_cpy;
  stack_print_it fn_print;
  stack_cmp_it fn_cmp;
};

Stack* stack_ini( stack_destroy_it f1, stack_cpy_it f2, stack_cmp_it f3, stack_print_it f4 ) {

  int i;
  Stack *st;

  st = (Stack*) malloc( sizeof( Stack ) );

  if ( !st )
    return NULL;

  st->top = 0;
  st->fn_destroy = f1;
  st->fn_cpy = f2;
  st->fn_cmp = f3;
  st->fn_print = f4;

  for ( i=0; i < MAX_STACK; i++ ) {
    st->its[ i ] = NULL;
  }

  return st;
}

void stack_destroy( Stack *st ) {

  if ( !st )
    return;

  while ( st->top > 0 ) {

    if ( st->fn_destroy ) {
      st->fn_destroy( st->its[ st->top-1 ] );
      st->top--;
    }

  }

  free( st );

}


bool stack_isFull( const Stack *st ) {

  if ( !st )
    return true;

  if ( st->top >= MAX_STACK )
    return true;

  return false;
}

bool stack_isEmpty( const Stack *st ) {

  if ( !st )
    return false;

  if ( st->top <= 0 )
    return true;

  return false;
}


void stack_push( Stack *st, const void *vp ) {

  void *cpy;

  if ( stack_isFull( st ) || !(st->fn_cpy) )
    return;

  cpy = st->fn_cpy( vp );

  if ( !cpy )
    return;

  st->its[ st->top ] = cpy;
  st->top++;

}

void *stack_pop( Stack *st ) {

  void *it;

  if ( !st )
    return NULL;

  if ( stack_isEmpty( st ) )
    return NULL;

  st->top--;

  it = st->its[ st->top ];
  st->its[ st->top ] = NULL;

  return it;

}

int stack_print( FILE *stream, const Stack *st ) {

  int i;
  int bytes = 0;

  if ( !st )
    return 0;

  if ( !stream || stack_isEmpty( st ) || !(st->fn_print) )
    return 0;

  for ( i=st->top-1; i > -1; i-- ) {
    bytes+=st->fn_print(stream, st->its[ i ] );
    bytes+=printf(" ");
  }


  bytes+=printf("\n");

  return bytes;
}


bool stack_has( const Stack *st, const void *vp ) {
  int i;

  if ( !st || !vp || !st->fn_cmp || stack_isEmpty( st ) )
    return false;

  for ( i=0; i < st->top; i++ ) {
    if ( !st->fn_cmp( st->its[ i ], vp ) )
      return true;

  }

  return false;

}
