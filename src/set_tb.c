#include "ui.h"
#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_IDS 5
#define MAX_ID 10

int main() {
	int i, max;
	Id id;
	Set *set;

	srand( time(NULL) );

	fprintf( stderr, "creating set ... " );
	set = set_create();

	if ( !set ) {
		fprintf( stderr, "ERR\n" );
		return -1;
	}
	fprintf( stderr, "OK\n" );

	for (i=0; i<MAX_IDS; i++) {
		id = rand() % MAX_ID;

		fprintf( stdout, "adding: %ld - ", id );

		switch ( set_add_id( set, id ) ) {
			case OK:
				fprintf( stdout, "OK\n" );
				break;
			case ERROR:
				fprintf( stdout, "ERR\n" );
				break;
		}
	}

	set_print( stdout, set );

	max = rand() % MAX_IDS + 1 ;

	for ( i=0; i < max; i++ ) {
		id = rand() % MAX_ID;
		fprintf( stdout, "deleting: %ld - ", id );

		switch ( set_del_id( set, id ) ) {
			case OK:
				fprintf( stdout, "OK\n" );
				break;
			case ERROR:
				fprintf( stdout, "ERR\n" );
				break;
		}

	}

	set_print( stdout, set );

	fprintf( stderr, "destroying set ...\n" );
	set_destroy( set );

	return 0;
}
