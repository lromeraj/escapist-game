#ifndef DICE_H
#define DICE_H

#include "types.h"

typedef struct _Die {
  Id id;
  int last_n;
} Die;

Die *die_init();
void die_destroy( Die *die );
int die_roll( Die *die );

#endif
