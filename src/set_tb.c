#include "ui.h"
#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_IDS 7
#define MAX_ID 10

enum { BOX1, BOX2, BOX3 };

void _sts( int errc, const char *str );
void _sleep( float secs );
void _print_set( FILE *stream, Set *set );
int usleep( __useconds_t );


void _sts( int errc, const char *str ) {

	switch ( errc ) {
		case 0:
			printf("\033[1;%dmOK\033[0m\n", FG_GREEN );
			break;
		default:
			printf("\033[1;%dmERR\033[0m:%s\n", FG_RED, str );
	}

}

void _sleep( float secs ) {
	usleep( (int)(secs*1000000) );
}

void _print_set( FILE *stream, Set *set ) {

}

int main() {

	Id id;
	Set *set;
	int i, max;

	srand( time(NULL) );

	printf("\n\033c");

	fprintf( stdout, "\033[1mcreating set\033[0m ... " );

	set = set_create();
	if ( !set ) {
		_sts( 2, "build failed" );
		return -1;
	}
	_sts( 0, "" );
	set_print( stdout, set );

	for (i=0; i<MAX_IDS; i++) {

		id = rand() % MAX_ID;

		fprintf( stdout, " <= %ld - ", id );
		if ( set_add_id( set, id ) == OK ) {
			_sts( 0, "" );
		} else {
			if ( set_is_full( set ) ) {
				_sts( 1, "full" );
			} else {
				_sts( 1, "conflict" );
			}
		}
		set_print( stdout, set );
		_sleep( 0.75 );
	}

	max = rand() % MAX_IDS + 3 ;
	for ( i=0; i < max; i++ ) {
		id = rand() % MAX_ID;

		fprintf( stdout, " => %ld - ", id );
		if ( set_del_id( set, id ) == OK ) {
			_sts( 0, "" );
		} else {
			_sts( 1, "not found" );
		}
		set_print( stdout, set );
		_sleep( 0.75 );
	}

	printf("\n");

	fprintf( stderr, "\033[1mdestroying set\033[0m ...\n" );

	set_destroy( set );

	return 0;
}
