/**
 * @brief Code implementation of the inventory manager
 *
 * @file inventory.c
 * @date 07/04/2019
 */

#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>

/*!
* Main inventory structure
*/
struct _Inventory {
	Set *bag;  /*!< @brief bag */
	int max; /*!< @brief Maximum capacity of the bag */
};

Inventory* inventory_create() {

	Inventory *inv;

	inv = (Inventory*) malloc( sizeof( Inventory ) );

	if( !inv )
    return NULL;

	inv->bag = set_create();
  inv->max = MAX_INVENTORY;

  return inv;

}
void inventory_destroy( Inventory *inv ) {
  if ( !inv )
    return;

  set_destroy( inv->bag );

  free( inv );

}

STATUS inventory_add_id( Inventory *inv, Id id ) {

  if ( !inv )
    return ERROR;

  if ( inventory_is_full( inv ) || inventory_get_total( inv ) >= MAX_INVENTORY )
    return ERROR;

  return set_add_id( inv->bag, id );
}

STATUS inventory_del_id( Inventory *inv, Id id ){

  if ( !inv )
    return ERROR;

  return set_del_id( inv->bag, id);
}


bool inventory_has_id( Inventory *inv, Id id ){

  if ( !inv || id == NO_ID )
    return false;

  return set_has_id( inv->bag, id );

}


int inventory_get_total( Inventory *inv ) {

  if ( !inv )
    return -1;

  return set_get_total( inv->bag );
}


int inventory_get_max( Inventory *inv ) {
  if ( !inv ) {
    return -1;
  }
  return inv->max;
}

Set* inventory_get_bag( Inventory *inv ) {

	if ( !inv )
		return NULL;

	return inv->bag;
}

bool inventory_is_full( Inventory *inv ) {

  if ( !inv )
    return true;

  return (bool)(inv->max == set_get_total( inv->bag ));
}

bool inventory_is_empty( Inventory *inv){

  if ( !inv )
    return false;

  return (bool)set_is_empty( inv->bag );
}
