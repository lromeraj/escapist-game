#ifndef STACK_PF_H
#define STACK_PF_H

#include <stdio.h>
#include <stdbool.h>

typedef struct _Stack Stack;


typedef int (*stack_print_it)( FILE*, const void* );
typedef void* (*stack_cpy_it)( const void* );
typedef void (*stack_destroy_it)( void* );
typedef int (*stack_cmp_it)( const void*, const void* );

Stack* stack_ini( stack_destroy_it, stack_cpy_it, stack_cmp_it, stack_print_it );
void stack_destroy( Stack* );
void stack_push( Stack *, const void* );
void* stack_pop( Stack* );
bool stack_isEmpty( const Stack* );
bool stack_isFull( const Stack* );
bool stack_has( const Stack*, const void* );
int stack_print( FILE*, const Stack* );

#endif
