/**
 * @brief Defines player's inventory
 *
 * @file inventory.h
 * @version 0.0.3
 * @date 20/03/2019
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include "types.h"

#define MAX_INVENTORY 2

typedef struct _Inventory Inventory;

Inventory* inventory_create();
void inventory_destroy( Inventory *inv );

STATUS inventory_add_id( Inventory *inv, Id id );
STATUS inventory_del_id( Inventory *inv, Id id );

bool inventory_has_id( Inventory *inv, Id id );
int inventory_get_max( Inventory *inv );
int inventory_get_total( Inventory *inv );

bool inventory_is_full( Inventory *inv );
bool inventory_is_empty( Inventory *inv );

#endif
