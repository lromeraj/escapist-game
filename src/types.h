/**
 * @brief It defines common type.
 *
 * @file types.h
 * @author Álvaro Rodríguez & Javier Romera
 * @version 1.0
 * @date 07/02/2019
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdint.h>

/* Defines maximum size of a word as 1000 and no id for players, objects and spaces as -1 */

#define WORD_SIZE 1000
#define NO_ID -1

/* Id defined as long var */

typedef long Id;

/* BOOL defines FALSE and TRUE as return types. */

typedef enum {
  FALSE, TRUE
} BOOL;

/* STATUS defines ERROR and OK as return types. */

typedef enum {
  ERROR, OK
} STATUS;

/* DIRECTION defines: N, north; S, south, ;E, east; W, west; as return types. */

typedef enum {
  N, S, E, W
} DIRECTION;

#endif
