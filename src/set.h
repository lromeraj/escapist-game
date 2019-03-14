#ifndef SET_H
#define SET_H

#include <stdio.h>
#include "types.h"

#define MAX_SET 5

typedef struct _Set Set;

Set* set_create();
void set_destroy( Set *set);

STATUS set_add_id( Set *set, Id id);
STATUS set_del_id( Set *set, Id id);

bool set_has_id( Set *set, Id id );
int set_get_total( Set *set);

bool set_is_full( Set *set);
bool set_is_empty( Set *set);

// only for testing
Id set_get_first( Set *set );

int set_print( FILE *stream, Set *set);

#endif
