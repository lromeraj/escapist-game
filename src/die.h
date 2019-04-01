/**
 * @brief Die's module header
 *
 * @file die.h
 * @version 0.0.3
 * @date 10/03/2019
 * @author Javier Romera
 * @copyright GNU Public License
 */

#ifndef DICE_H
#define DICE_H

#include "types.h"

typedef struct _Die Die;

/**
* @brief Initializates a die
* @author Javier Romera
* @param {Id} id - Die identification
* @retval Returns a pointer towards die
*/
Die* die_init( Id id );


/**
* @brief destroys a die
* @author Javier Romera
* @param {Die*} die - Die pointer
*/
void die_destroy( Die *die );


/**
* @brief rolls a die getting a random number
* @author Javier Romera
* @param {Die*} die - Die pointer
* @retval {int} - Returns the random number;
*/
int die_roll( Die *die );


/**
* @brief gets the last random number of the die
* @author Javier Romera
* @param {Die*} die - Die pointer
* @retval {int} - Returns the last random number;
*/
const int die_get_lastn( Die *die );

#endif
