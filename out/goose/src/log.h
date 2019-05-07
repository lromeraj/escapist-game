/**
 * @brief Logger
 *
 * @file log.h
 * @author @lromeraj
 * @version 0.3.3
 * @date 16/02/2019
 * @copyright GNU Public License
 */

#ifndef LOG_H
#define LOG_H
#include <stdbool.h>

void log_begin( const char *log_n );
void log_w( const char *frm, ... );
void log_end();
bool log_isOpen();

#endif
