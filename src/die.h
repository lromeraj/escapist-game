#ifndef DICE_H
#define DICE_H

#include "types.h"

typedef struct _Die Die;

/**
* @brief initializes a new die for the game
*
* @author Javier Romera
* @return {Die*} - returns a pointer
* to the new die
*/
Die *die_init();

/**
* @brief destroys a die
*
* @author Javier Romera
* @param {Die*} die - Die pointer
* @return {void} - Do not returns nothing;
*/
void die_destroy( Die *die );

/**
* @brief rolls a die getting a random number
*
* @author Javier Romera
* @param {Die*} die - Die pointer
* @return {int} - Returns the random number;
*/
int die_roll( Die *die );

/**
* @brief gets the last random number of the die
*
* @author Javier Romera
* @param {Die*} die - Die pointer
* @return {int} - Returns the last random number;
*/
const int die_get_lastn( Die *die );

#endif
