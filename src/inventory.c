#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "inventory.h"

/*!
* Main inventory structure
*/
struct _Inventory {
	Set *ids;  /*!< @brief Ids of the item */
	int max; /*!< @brief Maximum number of items */
};

Inventory* inventory_create() {

	Inventory *inv;

	inv = (Inventory*) malloc( sizeof( Inventory ) );

	if( !inv )
    return NULL;

	inv->ids = set_create();
  inv->max = MAX_INVENTORY;

  return inv;

}
void inventory_destroy( Inventory *inv ) {
  if ( !inv )
    return;

  set_destroy( inv->ids );

  free( inv );

}

STATUS inventory_add_id( Inventory *inv, Id id ) {

  if ( !inv )
    return ERROR;

  if ( inventory_is_full( inv ) || inventory_get_total( inv ) >= MAX_INVENTORY )
    return ERROR;

  if( set_add_id( inv->ids, id ) == ERROR )
		return ERROR;

  return OK;
}

STATUS inventory_del_id( Inventory *inv, Id id ){

  if ( !inv )
    return ERROR;

  return set_del_id( inv->ids, id);
}


bool inventory_has_id( Inventory *inv, Id id ){

  if ( !inv || id == NO_ID )
    return false;

  return set_has_id( inv->ids, id );

}


int inventory_get_total( Inventory *inv ) {

  if ( !inv )
    return -1;

  return set_get_total( inv->ids );
}


int inventory_get_max( Inventory *inv ) {
  if ( !inv ) {
    return -1;
  }
  return inv->max;
}

bool inventory_is_full( Inventory *inv ) {

  if ( !inv )
    return true;

  return (bool)(inv->max == set_get_total( inv->ids ));
}

bool inventory_is_empty( Inventory *inv){

  if ( !inv )
    return false;

  return (bool)set_is_empty( inv->ids );
}
