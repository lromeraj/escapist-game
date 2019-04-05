#ifndef BM_H
#define BM_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

typedef struct _Clk Clk;

void bm_build();
void bm_clk_begin( Clk *clk );
void bm_clk_end( Clk *clk );
void bm_clk_print( Clk *clk );
double bm_clk_avg( Clk *clk );
Clk* bm_clk( const char *name );
void bm_destroy();


#endif
