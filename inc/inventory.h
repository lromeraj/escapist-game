/**
 * @brief Inventory manager
 *
 * @file inventory.h
* @author Miguel Rodríguez
 * @version 0.9.1
 * @date 07/04/2019
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "set.h"
#include <stdio.h>
#include "types.h"

#define MAX_INVENTORY 5 /*!< @brief Maximum capacity of inventory */


/*!
 * @brief Defines the type of inventory structure
 */
typedef struct _Inventory Inventory;


/**
* @brief This fuction initializes an inventory
* @author Miguel Rodríguez
*
* @retval {Inventory*} - Returns an inventory's pointer
*/
Inventory* inventory_create();


/**
* @brief This fuction destroys an Inventory
* @author Miguel Rodríguez
* @param {Inventory*} inv - Inventory pointer
*/
void inventory_destroy( Inventory *inv );


/**
* @brief Adds a new id to an inventory
* @author Miguel Rodríguez
* @param {Inventory*} - Inventory pointer
* @retval {STATUS} - Returns ok or error
*/
STATUS inventory_add_id( Inventory *inv, Id id );


/**
* @brief Deletes an id from an inventory
* @author Miguel Rodríguez
* @param {Inventory*} inv - inventory pointer
* @param {Id} id - variable of type Id
* @retval {STATUS} - Returns ok or error
*/
STATUS inventory_del_id( Inventory *inv, Id id );


/**
* @brief Tells if an id is in a Inventory or not
* @author Miguel Rodríguez
* @param {Inventory*} - Inventory pointer
* @param {Id} id - variable of type Id
* @retval {bool} - Returns a boolean value
*/
bool inventory_has_id( Inventory *inv, Id id );


/**
* @brief Tells the maximun capacity of the Inventory
* @author Miguel Rodríguez
* @param {Inventory*} - Inventory pointer
* @retval {int} - Returns an integer
*/
int inventory_get_max( Inventory *inv );


/**
* @brief Tells the number of id's in an inventory
* @author Miguel Rodríguez
* @param {Inventory*} - Inventory pointer
* @retval {int} - Returns an integer
*/
int inventory_get_total( Inventory *inv );


/**
* @brief Gets the bag of the player
* @author Javier Romera
* @param {Inventory*} - inventory pointer
* @retval {Set*} - returns player's bag as a set of ids
*/
Set* inventory_get_bag( Inventory *inv );


/**
* @brief Tells if an inventory is full or not
* @author Miguel Rodríguez
* @param {Inventory*} - Inventory pointer
* @retval {bool} - Returns a boolean value
*/
bool inventory_is_full( Inventory *inv );


/**
* @brief Tells if an inventory is empty or not
* @author Miguel Rodríguez
* @param {Inventory*} - Iventory pointer
* @retval {bool} - Returns a boolean value
*/
bool inventory_is_empty( Inventory *inv );

#endif
