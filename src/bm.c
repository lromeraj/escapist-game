#include "bm.h"

#define MAX_CLKS 10
#define MAX_CLK_NAME 50


struct _Clk {
  double avg[ 2 ];
  char name[ MAX_CLK_NAME ];
  struct timespec t_start, t_end;
};


Clk *CLKS[ MAX_CLKS ];

void bm_build() {
  int i;

  for (i=0; i<MAX_CLKS; i++) {
    CLKS[ i ] = NULL;
  }

}

void bm_clk_begin( Clk *clk ) {
  if ( !clk )
    return;
  clock_gettime( CLOCK_MONOTONIC, &clk->t_start );
}

void bm_clk_end( Clk *clk ) {

  long sec, n_sec;
  double diff;

  if ( !clk )
    return;

  clock_gettime( CLOCK_MONOTONIC, &clk->t_end );

  sec = clk->t_end.tv_sec - clk->t_start.tv_sec;
  n_sec = clk->t_end.tv_nsec - clk->t_start.tv_nsec;

  diff = (double)sec + (double)n_sec/(double)1000000000;

  clk->avg[ 0 ]+=diff;
  clk->avg[ 1 ]++;

}

void bm_clk_print( Clk *clk ) {

  if ( !clk )
    return;

  printf("%s ~ %e\n", clk->name, bm_clk_avg( clk ) );

}

double bm_clk_avg( Clk *clk ) {

  if ( !clk )
    return 0;

  return !clk->avg[1] ? 0 : clk->avg[0]/clk->avg[1];
}

Clk* bm_clk( const char *name ) {

  Clk *clk;
  static int idx = 0;

  if ( idx >= MAX_CLKS )
    return NULL;

  clk = (Clk*) calloc( 1, sizeof(Clk) );

  if ( !clk )
    return NULL;

  clk->avg[0] = 0;
  clk->avg[1] = 0;

  strcpy( clk->name, name );

  CLKS[ idx ] = clk;

  idx++;

  return clk;
}


void bm_destroy() {

  int i;
  Clk *clk;

  for ( i=0; i<MAX_CLKS; i++ ) {
    clk = CLKS[ i ];
      if ( clk ) {
        free( CLKS[ i ] );
        CLKS[ i ] = NULL;
      }
  }
}
