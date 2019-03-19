/**
 * @brief Die functions
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

/**
 * @brief The die structure with its elements
 *
 */

typedef struct _Die Die;

/**
 * @brief initializes a new die for the game
 *
 * @date 10/03/2019
 * @author Javier Romera
 *
 * @param empty
 * @retval {Die*} - returns a pointer to the new die
 */
Die *die_init();

/**
 * @brief destroys a die
 *
 * @date 10/03/2019
 * @author Javier Romera
 *
 * @param {Die*} die - Die pointer
 * @retval {void} - Do not returns nothing
 */
void die_destroy( Die *die );

/**
 * @brief rolls a die getting a random number
 *
 * @date 10/03/2019
 * @author Javier Romera
 *
 * @param {Die*} die - Die pointer
 * @retval {int} - Returns the random number
 */
int die_roll( Die *die );

/**
 * @brief gets the last random number of the die
 *
 * @date 10/03/2019
 * @author Javier Romera
 *
 * @param {Die*} die - Die pointer
 * @retval {int} - Returns the last random number
 */
const int die_get_lastn( Die *die );

#endif
