/**
 * @brief It defines types of data.
 *
 * @file types.h
 * @author Miguel Rodríguez
 * @version 0.8.4
 * @date 18/03/2019
 */

#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdint.h>

#define WORD_SIZE 1000  /*!< @brief Default strings buffer length */
#define NO_ID -1        /*!< @brief Value of NO_ID */

/**
 * @brief Defines an id as long
 */
typedef long Id;

/*!
* @brief Status variants
*/
typedef enum {
  ERROR, /*!< @brief Error means a failure */
  OK     /*!< @brief Ok means success */
} STATUS;

/*!
* @brief Direction's structure
*
*/
typedef enum {
  N, /*!< @brief North */
  S, /*!< @brief South */
  E, /*!< @brief East */
  W /*!< @brief West */
} CardinalPoint;

#endif
