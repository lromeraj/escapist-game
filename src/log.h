/**
 * @brief Logger
 *
 * @file log.h
 * @author Javier Romera
 * @version 0.3.3
 * @date 16/02/2019
 * @copyright GNU Public License
 */

#ifndef LOG_H
#define LOG_H
#include <stdbool.h>

/**
* @name log_begin
* @brief initializes the file
*
* @author Javier Romera
* @param {const char*} log_n - Log name
* @return {void} - Do not returns nothing
*/
void log_begin( const char *log_n );

/**
* @name log_w
* @brief writes in the file
*
* @author Javier Romera
* @param {const char*} frm - String format
* @param {...} - String format arguments
* @return {void} - Do not returns nothing
*/
void log_w( const char *frm, ... );

/**
* @name log_end
* @brief it closes the file opened before
*
* @author Javier Romera
* @return {void} - Do not returns nothing
*/
void log_end();

/**
* @name log_begin
* @brief it checks if the log file is open
*
* @author Javier Romera
* @return {bool} - Returns false or true
*/
bool log_isOpen();

#endif
