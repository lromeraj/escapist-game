#include "die.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_RLS 15

int main() {
	int i;
	Die *die;

	srand( time(NULL) );

  fprintf( stderr, "creating die ... " );
  die = die_init( 1 );

	if ( !die ) {
		fprintf( stderr, "ERR\n" );
		return -1;
	}

  fprintf( stderr, "OK\n" );


	for (i=0; i<MAX_RLS; i++) {
		fprintf( stdout, "roll: %d\n", die_roll( die ) );
	}

  fprintf( stderr, "destroying die ...\n" );
	die_destroy( die );

	return 0;
}
