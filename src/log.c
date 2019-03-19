/**
 * @brief Logger
 *
 * @file log.c
 * @version 0.3.3
 * @date 16/02/2019
 * @author Javier Romera
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

FILE *LOG_FILE = NULL;

bool log_isOpen() {
  return (LOG_FILE == NULL) ? false : true;
}

void log_begin( const char *log_n ) {

  LOG_FILE = fopen( log_n, "w" );

  if ( !log_isOpen() ) {
    fprintf( stderr, "error opening log\n" );
  }

}

void log_end() {
  if ( !LOG_FILE )
    return;
  fclose( LOG_FILE );
  LOG_FILE = NULL;
}

void log_w( const char *frm, ... ) {

  va_list args;
  char buff[ 500 ];

  if ( !log_isOpen() ) return;

  va_start( args,frm );
  vsprintf( buff, frm, args );
  va_end( args );

  fprintf( LOG_FILE, "%s", buff );

}
