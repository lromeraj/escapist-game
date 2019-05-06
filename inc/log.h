/**
 * @brief Logger
 *
 * @file log.h
 * @version 0.3.3
 * @date 16/02/2019
 * @author Javier Romera
 * @copyright GNU Public License
 */

#ifndef LOG_H
#define LOG_H
#include <stdbool.h>

/**
 * @brief initializes the file
 *
 * @date 16/02/2019
 * @author Javier Romera
 *
 * @param {const char*} log_n - Log name
 */
void log_begin( const char *log_n );

/**
 * @brief writes in the file
 *
 * @date 16/02/2019
 * @author Javier Romera
 *
 * @param {const char*} frm - String format
 * @param {...} - String format arguments
 */
void log_w( const char *frm, ... );

/**
 * @brief it closes the file opened before
 *
 * @date 16/02/2019
 * @author Javier Romera
 * @param {char*} frm - String format
 * @param {...} - String format arguments
 */
void log_end();

/**
 * @brief it checks if the log file is open
 *
 * @date 16/02/2019
 * @author Javier Romera
 *
 * @param empty
 * @retval {bool} - Returns False or True
 */
bool log_isOpen();

#endif
