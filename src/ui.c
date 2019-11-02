/**
* @brief Ui source code
*
* @file ui.c
* @author Javier Romera
* @copyright GNU Public License
*/

#define _POSIX_C_SOURCE 200809L

#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define DEFAULT_TXT_BG_COLOR BG_WHITE
#define DEFAULT_TXT_FG_COLOR FG_BLACK
#define DEFAULT_TXT_FORMAT S_DEFAULT
#define DEFAULT_BOX_BG_COLOR BG_WHITE
#define DEFAULT_BG_COLOR BG_WHITE

#define UI_TAB_SIZE 3 /*!< @brief Tab key size */
#define UI_MAX_BOXES 15 /*!< @brief Maximum quantity of boxes per UI */
#define UI_MAX_BUFF_LEN 500 /*!< @brief Maximum buffer length */
#define UI_MAX_FRM 20 /*!< @brief Maximum number of parameters for formatting */
#define UI_MAX_SFRM_LEN 100 /*!< @brief Maximum string fromat length */

#define UI_MAX_FRM_LEN ( UI_MAX_FRM + 2 )  /*!< @brief Maximum length of the format array */

#define __frmidx( __frm ) ( __frm[ UI_MAX_FRM_LEN - 2 ] ) /*!< @brief get the destination index of the format */
#define __frmxor( __frm ) ( __frm[ UI_MAX_FRM_LEN - 1 ] ) /*!< @brief get the checksum of the format */

typedef struct _Ui_screen Ui_screen;
typedef struct _Ui_data Ui_data;
typedef struct _Ui_pix Ui_pix;
typedef struct _Ui_cpix Ui_cpix;
typedef struct _Ui_box Ui_box;

/*!
* @brief Basic pixel structure
*/
struct _Ui_pix {
  char c; /*!< @brief Pixel char */
  int frm[ UI_MAX_FRM_LEN ]; /*!< @brief Pixel format */
};

struct _Ui_cpix {
  int csum; /*!< @brief Format checksum */
  char sfrm[ UI_MAX_SFRM_LEN ]; /*!< @brief String cache format */
};

/*!
* @brief Main box structure
*/
struct _Ui_box {
  Ui_pix **__pixs; /*!< @brief Pixels array */
  int id; /*!< @brief Box identification */
  int x; /*!< @brief Coordenate 'x' */
  int y; /*!< @brief Coordenate 'y' */
  int w; /*!< @brief Width */
  int h; /*!< @brief Height */
  int cx; /*!< @brief Position of the 'x' cursor */
  int cy;  /*!< @brief Position of the 'y' cursor */
  int cx_off; /*!< @brief Offset for the 'x' cursor */
  int cx_top; /*!< @brief Limit for the 'x' cursor */
  int __len;  /*!< @brief Length of the pixels array */
  int pad[ 4 ];  /*!< @brief Box padding */
  Color bg;  /*!< @brief Background color */
  int frm[ UI_MAX_FRM_LEN ]; /*!< @brief Default format for the content of the box */
};

/*!
* @brief Main UI screen structure
*/
struct _Ui_screen {
  int w; /*!< @brief Width */
  int h; /*!< @brief Height */
};

/*!
* @brief Main UI data structure
*/
struct _Ui_data {
  long last_frame_ms; /*!< @brief Last frame clock time */
};

/*!
* @brief Main UI structure
*/
struct _Ui {
  Ui_data data; /*!< @brief Other Ui data storage */
  Ui_config config; /*!< @brief Ui configuration */
  Ui_screen scr; /*!< @brief Screen */
  Ui_box *boxes[ UI_MAX_BOXES ]; /*!< @brief Boxes */
  Ui_pix **__pixs; /*!< @brief Pixels buffer */
  Ui_cpix **__cache; /*!< @brief Cache of pixels buffer */
  int __len; /*!< @brief Number of pixels */
  int __frm[ UI_MAX_FRM_LEN ]; /*!< @brief Temporary format */
};



/****** PRIVATE FUNCTIONS ******/

/**
* @brief Reserves memory to alloc a certain quantity of pixels
* @param __len - The quantity of pixels to be allocted
* @retval - Returns a pointer which points to other pixels pointers
*/
Ui_pix **alloc_pixs( int __len );


/**
* @brief This function destroys an array of pixels to liberate memory
* @param __pixs - Pointer which points to the data
* @param __len - The length of the pixs matrix
*/
void kill_pixs( Ui_pix **__pixs, int __len );


/**
* @brief Reserves memory to alloc a certain quantity of cache pixels
* @param __len - The quantity of pixels to be allocted
* @retval - Returns a pointer which points to other pixels pointers
*/
Ui_cpix **alloc_cpixs( int __len );


/**
* @brief This function destroys an array of cache pixels to liberate memory
* @param __pixs - Pointer which points to the data
* @param __len - The length of the pixs matrix
*/
void kill_cpixs( Ui_cpix **__pixs, int __len );


/**
* @brief Checks if a given position ( usually for pixels ) is overflowing the max size
* @param x - Represents the x position ( column of the matrix )
* @param y - Represents the y position ( row of the matrix )
* @param w - Represents the space width
* @param h - Represents the space height
* @retval - Returns a boolean value, false if there is no overflow, else true
*/
bool ui_pix_ovf( int x, int y, int w, int h );


/**
* @brief Gets a pixel that is located in a given position
* @param __pixs - the array where the pixel should be located
* @param x - Represents the x position ( column of the matrix )
* @param y - Represents the y position ( row of the matrix )
* @param w - Represents the space width
* @param h - Represents the space height
* @retval - Returns a pointer to the found pixel, else returns NULL
*/
Ui_pix *ui_get_pix( Ui_pix **__pixs, int x, int y, int w, int h );


/**
* @brief Sets a given pixel in a given position
* @param __pixs - the array where the pixel should be located
* @param x - Represents the x position ( column of the matrix )
* @param y - Represents the y position ( row of the matrix )
* @param w - Represents the space width
* @param h - Represents the space height
* @param pix - Struct of the pixel to be setted
*/
void ui_set_pix( Ui_pix **__pixs, int x, int y, int w, int h, Ui_pix pix );

/**
* @brief Finds a box by it's id (slow)
* @param ui - UI where the box should be located
* @param id - The id of the requested box
* @retval - If the box was found returns a pointer
* to the requested box, else returns NULL
*/
Ui_box* ui_get_box_by_id( Ui* ui, int id );


/**
* @brief Gets a box by it's idx (fast)
* @param ui - UI where the box should be located
* @param id - The id of the requested box
* @retval - The box at the given index (can be NULL)
*/
Ui_box* ui_get_box_by_idx( Ui* ui, int idx );


/**
* @brief Destroys a given box
* @param ui - Ui where the box should be removed
* @param idx - Box index
*/
void ui_kill_box( Ui* ui, int idx );


/**
* @brief Resets the format
* @param frm - Format array to be reseted
*/
void _frm_rs( int *frm );


/**
* @brief Copies source format into destinationformat
* @param dest - Format array destination
* @param src - Format array source
*/
void _frm_cpy( int *dest, int *src );


/**
* @brief Adds a value to a given format
* @param frm - Format array to be modified
* @param v - Value to be added
*/
void _frm_add( int *frm, int v );


/**
* @brief Adds a list of values into a format array
* @param frm - format array destination
* @param n - Number of parameters to be added
* @param list - List of parameters to be inserted
*/
void _frm( int *frm, int n, va_list list );


/**
* @brief Parses a given format string into a number format array
* @param frm - Format destination
* @param defrm - Default format in case of reset
* @param sfrm - Format string
*/
void _frm_parse( int *frm, int *defrm, const char *sfrm );

int vsnprintf( char *buf, size_t size, const char *fmt, va_list list );
int snprintf( char *buf, size_t size, const char *fmt, ... );

/*******************************/


/** formatting functions *****************/

void _frm_rs( int *frm ) {

  if ( !frm )
    return;

  memset( frm, -1, UI_MAX_FRM_LEN*sizeof(int) );

  __frmxor( frm ) = 0;
  __frmidx( frm ) = 0;

  _frm_add( frm, 0 );

}

void _frm_cpy( int *dest, int *src ) {

  if ( !dest || !src )
    return;

  memcpy( dest, src, UI_MAX_FRM_LEN*sizeof(int) );

}

void _frm_add( int *frm, int v ) {

  int _i;

  if ( !frm )
    return;

  _i = __frmidx( frm );

  if ( _i < UI_MAX_FRM ) {
    frm[ _i ] = v;
    __frmxor( frm ) += v;
    __frmxor( frm ) = __frmxor( frm ) << 2 | __frmxor( frm );
    __frmidx( frm )++;
  }

}

void _frm_parse( int *frm, int *defrm, const char *sfrm ) {

  int i, j, _i, len;
  short r, g, b;
  char c;
  bool addChar, addSn;
  char strp[ UI_MAX_BUFF_LEN ] = ""; /* string parameter */

  if ( !frm || !sfrm )
    return;

  addSn = false;

  len = strlen( sfrm );
  for ( i=0, _i=0; i <= len; i++ ) {

    c = sfrm[ i ];
    addChar = true;

    if ( c == ';' || c == '\0' ) {
      addChar = false;
      addSn = true;
    }

    if ( addSn ) {

      if ( !strncmp( strp, "frgb", 4 ) ) { /* foreground rgb */
        sscanf( strp, "frgb(%hd,%hd,%hd)", &r, &g, &b );
        _frm_add( frm, 38 );
        _frm_add( frm, 2 );
        _frm_add( frm, r );
        _frm_add( frm, g );
        _frm_add( frm, b );
      } else if ( !strncmp( strp, "brgb", 4 ) ) { /* background rgb */
        sscanf( strp, "brgb(%hd,%hd,%hd)", &r, &g, &b );
        _frm_add( frm, 48 );
        _frm_add( frm, 2 );
        _frm_add( frm, r );
        _frm_add( frm, g );
        _frm_add( frm, b );
      } else if ( !strncmp( strp, "$", 1 ) ) { /* print format */

        for (j=0; j<UI_MAX_FRM_LEN; j++) {
          printf("%d ", frm[ j ] );
        }

        printf("\n");

      } else if ( !strncmp( strp, "!0", 2 ) ) { /* hard reset */
        _frm_rs( frm );
      } else {

        _i = atoi( strp );

        if ( !_i ) { /* default reset */

          if ( defrm == NULL ) {
            _frm_rs( frm );
          } else {
            _frm_cpy( frm, defrm );
          }

        } else {
          _frm_add( frm, _i ); /* else add new format */
        }

      }

      addSn = false;
      _i = 0;
    }

    if ( addChar && _i < UI_MAX_BUFF_LEN ) {
      strp[ _i ] = c;
      strp[ _i + 1 ] = 0;
      _i++;
    }
  }

}

void _frm( int *frm, int n, va_list list ) {

  int i, _v;
  _frm_rs( frm );

  for ( i=0; i < n; i++ ) {
    _v = va_arg( list, int );
    _frm_add( frm, _v );
  }

}

void ui_frm( Ui *ui, int n, ... ) {
  va_list _args;
  va_start( _args, n );
  _frm( ui->__frm, n, _args );
  va_end( _args );
}

void ui_frms( Ui* ui, const char *frms, ... ) {

  va_list _args;
  char _buff[ UI_MAX_BUFF_LEN ];

  if ( !ui || !frms )
    return;

  va_start( _args, frms );
  vsnprintf( _buff, UI_MAX_BUFF_LEN, frms, _args );
  va_end( _args );

  _frm_parse( ui->__frm, NULL, _buff );

}

Ui *ui_init( int w, int h ) {

  int i;

  Ui *ui = (Ui*) malloc( sizeof( Ui ) );

  if ( ui ) {

    ui->data.last_frame_ms = 0;
    ui->config.min_frame_ms = 0;

    _frm_rs( ui->__frm );

    for ( i=0; i < UI_MAX_BOXES; i++) {
      ui->boxes[ i ] = NULL;
    }

    ui->__pixs = NULL;
    ui->__cache = NULL;
    ui->scr.w = 0;
    ui->scr.h = 0;

    ui_resize( ui, w, h );

    if ( !ui->__pixs || !ui->__cache ) {
      ui_destroy( ui );
    }

  }

  return ui;

}

void ui_resize( Ui *ui, int w, int h ) {

  struct winsize wsize;

  if ( !ui )
    return;

  if ( w == UI_WIN_COLS || h == UI_WIN_ROWS ) {
    ioctl( STDOUT_FILENO, TIOCGWINSZ, &wsize );
  }

  if ( w == UI_WIN_COLS ) {
    w = wsize.ws_col;
  }

  if ( h == UI_WIN_ROWS ) {
    h = wsize.ws_row;
  }

  /* no need for resizing */
  if ( ui->scr.w == w && ui->scr.h == h )
    return;

  kill_pixs( ui->__pixs, ui->__len );
  kill_cpixs( ui->__cache, ui->__len );

  ui->__len = 0;
  ui->scr.w = 0;
  ui->scr.h = 0;

  ui->__pixs = alloc_pixs( w*h );
  ui->__cache = alloc_cpixs( w*h );

  if ( ui->__pixs && ui->__cache ) {
    ui->scr.w = w;
    ui->scr.h = h;
    ui->__len = w*h;
  }

}

void ui_destroy( Ui *ui ) {

  int i;

  if ( !ui )
    return;

  kill_pixs( ui->__pixs, ui->__len );
  kill_cpixs( ui->__cache, ui->__len );

  for ( i=0; i < UI_MAX_BOXES; i++ ) {
    ui_kill_box( ui, i );
  }

  free( ui );

}

void ui_bg( Ui *ui, const char *frms, ... ) {

  int i;
  va_list _args;
  char _buff[ UI_MAX_BUFF_LEN ];
  int __frm[ UI_MAX_FRM_LEN ];

  if ( !ui || !frms )
    return;

  va_start( _args, frms );
  vsnprintf( _buff, UI_MAX_BUFF_LEN, frms, _args );
  va_end( _args );

  _frm_rs( __frm );
  _frm_parse( __frm, NULL, _buff );

  for ( i=0; i < ui->__len; i++ ) {
    _frm_cpy( ui->__pixs[ i ]->frm, __frm );
  }

}

void ui_rs( Ui *ui ) {

  if ( !ui )
    return;

  ui_frm( ui, 3, DEFAULT_TXT_FORMAT, DEFAULT_TXT_BG_COLOR, DEFAULT_TXT_FG_COLOR );

}

void ui_box_bg( Ui *ui, int idx, const char *frms, ... ) {

  int i;
  Ui_box *box;
  va_list _args;
  char _buff[ UI_MAX_BUFF_LEN ];
  int __frm[ UI_MAX_FRM_LEN ];

  box = ui_get_box_by_idx( ui, idx );

  if ( !box || !frms )
    return;

  va_start( _args, frms );
  vsnprintf( _buff, UI_MAX_BUFF_LEN, frms, _args );
  va_end( _args );

  _frm_rs( __frm );
  _frm_parse( __frm, NULL, _buff ); /* just parse only one time */

  for ( i=0; i < box->__len; i++ ) {
    _frm_cpy( box->__pixs[ i ]->frm, __frm );
  }

}

void ui_box_frm( Ui *ui, int idx, int n, ... ) {

  Ui_box *box;
  va_list _args;

  box = ui_get_box_by_idx( ui, idx );

  if ( !box )
    return;

  va_start( _args, n );
  _frm( box->frm, n, _args );
  va_end( _args );

}

void ui_box_frms( Ui* ui, int idx, const char *frms, ... ){

  Ui_box *box;
  va_list _args;
  char _buff[ UI_MAX_BUFF_LEN ];

  box = ui_get_box_by_idx( ui, idx );

  if ( !box || !frms )
    return;

  _frm_rs( box->frm );

  va_start( _args, frms );
  vsnprintf( _buff, UI_MAX_BUFF_LEN, frms, _args );
  va_end( _args );

  _frm_parse( box->frm, NULL, _buff );

}

void ui_box_repos( Ui *ui, int idx, int x, int y ) {

  Ui_box *box;

  box = ui_get_box_by_idx( ui, idx );

  if ( !box )
    return;

  box->x = x;
  box->y = y;

}


int ui_box_get_w( Ui* ui, int idx ) {

  Ui_box *box;

  box = ui_get_box_by_idx( ui, idx );

  if ( !box )
    return -1;

  return box->w;

}

int ui_box_get_h( Ui* ui, int idx ) {

  Ui_box *box;

  box = ui_get_box_by_idx( ui, idx );

  if ( !box )
    return -1;

  return box->h;

}

int ui_box_get_cx( Ui* ui, int idx ) {

  Ui_box *box;

  box = ui_get_box_by_idx( ui, idx );

  if ( !box )
    return -1;

  return box->cx;

}

int ui_box_get_cy( Ui* ui, int idx ) {

  Ui_box *box;

  box = ui_get_box_by_idx( ui, idx );

  if ( !box )
    return -1;

  return box->cy;

}

void ui_box_set_cx_off( Ui* ui, int idx, int cx_off ) {

  Ui_box *box;

  box = ui_get_box_by_idx( ui, idx );

  if ( !box )
    return;

  if ( cx_off < 0 || cx_off >= box->w )
    return;

  box->cx_off = cx_off;

}

void ui_box_set_cx_top( Ui* ui, int idx, int cx_top ) {

  Ui_box *box;

  box = ui_get_box_by_idx( ui, idx );

  if ( !box )
    return;

  if ( cx_top < 0 || cx_top > box->w )
    return;

  box->cx_top = cx_top;

}

void ui_box_get_cursor( Ui* ui, int idx, int* cx, int* cy ) {

  Ui_box *box;

  box = ui_get_box_by_idx( ui, idx );

  if ( !box || !cx || !cy )
    return;

  *cx = box->cx;
  *cy = box->cy;

}

void ui_box_resize( Ui *ui, int idx, int w, int h ) {

  Ui_box *box;

  box = ui_get_box_by_idx( ui, idx );

  if ( !box )
    return;

  kill_pixs( box->__pixs, box->__len );
  box->__len = 0;
  box->cx = 0;
  box->cy = 0;
  box->w = 0;
  box->h = 0;
  box->cx_off = 0;
  box->cx_top = 0;

  box->__pixs = alloc_pixs( w*h );

  if ( box->__pixs ) {
    box->w = w;
    box->h = h;
    box->cx_top = w;
    box->__len = w*h;
  }


}

void ui_clear_box( Ui *ui, int idx ) {

  int i;
  Ui_box *box;

  box = ui_get_box_by_idx( ui, idx );

  if ( !box )
    return;

  box->cx = box->pad[3];
  box->cy = box->pad[0];

  for ( i=0; i < box->__len; i++ ) {
    box->__pixs[ i ]->c = ' ';
  }

}

void ui_clear( Ui *ui ) {

  int i=0;
  Ui_box *box;

  if ( !ui )
    return;

  for ( i=0; i < UI_MAX_BOXES; i++ ) {
    box = ui->boxes[ i ];
    if ( !box ) continue;
    ui_clear_box( ui, box->id );
  }

  for ( i=0; i < ui->__len; i++ ) {
    _frm_rs( ui->__pixs[ i ]->frm );
    ui->__pixs[ i ]->c = ' ';
  }

}

void kill_pixs( Ui_pix **__pixs, int __len ) {

  int i;

  if ( !__pixs )
    return;

  for (i=0; i < __len; i++ ) {
    if ( __pixs[ i ] ) {
      free( __pixs[ i ] );
    }
  }
  free( __pixs );

}

void kill_cpixs( Ui_cpix **__cpixs, int __len ) {

  int i;

  if ( !__cpixs )
    return;

  for ( i=0; i < __len; i++ ) {
    if ( __cpixs[ i ] ) {
      free( __cpixs[ i ] );
    }
  }
  free( __cpixs );

}

Ui_pix **alloc_pixs( int __len ) {

  int i;
  Ui_pix *pix;
  Ui_pix **__pixs = (Ui_pix**) malloc(__len * sizeof(Ui_pix*) );

  if ( __pixs ) {

    for ( i=0; i < __len; i++ ) {

      pix = (Ui_pix*) malloc( sizeof(Ui_pix) );

      if ( pix ) {
        pix->c = ' ';
        __pixs[ i ] = pix;
        _frm_rs( pix->frm );
      } else {
        kill_pixs( __pixs, i-1 );
        break;
      }

    }

  }

  return __pixs;

}

Ui_cpix **alloc_cpixs( int __len ) {

  int i;
  Ui_cpix *cpix;
  Ui_cpix **__cpixs = (Ui_cpix**) malloc(__len * sizeof(Ui_cpix*) );

  if ( __cpixs ) {

    for ( i=0; i < __len; i++ ) {

      cpix = (Ui_cpix*) malloc( sizeof(Ui_cpix) );

      if ( cpix ) {
        cpix->csum = -1;
        cpix->sfrm[0] = '\0';
        __cpixs[ i ] = cpix;
      } else {
        kill_cpixs( __cpixs, i-1 );
        break;
      }

    }

  }

  return __cpixs;

}

void ui_new_box( Ui *ui, int idx, int x, int y, int w, int h ) {

  int i;
  Ui_pix *pix;
  Ui_box *box;

  if ( !ui )
    return;

  /* check new box idx */
  if ( idx < 0 || idx >= UI_MAX_BOXES )
    return;

  if ( ui->boxes[ idx ] )
    return;

  box = (Ui_box*) malloc( sizeof( Ui_box ) );

  if ( box ) {

    box->x = x;
    box->y = y;
    box->w = w;
    box->h = h;
    box->cx = 0;
    box->cy = 0;
    box->cx_off = 0;
    box->cx_top = w;
    box->id = idx;
    box->__len = w*h;
    box->bg = DEFAULT_BOX_BG_COLOR;
    box->pad[0] = 0;
    box->pad[1] = 0;
    box->pad[2] = 0;
    box->pad[3] = 0;

    _frm_rs( box->frm );

    box->__pixs = alloc_pixs( box->__len );

    if ( box->__pixs ) {

      ui->boxes[ idx ] = box; /* store the box inside the ui */

      for (i=0; i < box->__len; i++) {
        pix = box->__pixs[ i ];
        pix->c = ' ';
      }

      ui_dump_box( ui, idx );

    } else {

      ui_kill_box( ui, idx );

    }

  }

}

Ui_box *ui_get_box_by_id( Ui *ui, int id ) {

  int i;
  Ui_box *box = NULL;

  if ( !ui )
    return NULL;

  for ( i=0; i < UI_MAX_BOXES; i++) {

    box = ui->boxes[ i ];

    if ( !box ) continue;

    if ( box->id == id ) {
      return box;
    }

  }

  return box;

}

Ui_box *ui_get_box_by_idx( Ui *ui, int idx ) {

  if ( !ui )
    return NULL;

  if ( idx > -1 && idx < UI_MAX_BOXES )
    return ui->boxes[ idx ];

  return NULL;
}

bool ui_pix_ovf( int x, int y, int w, int h ) {

  int _idx = w*y + x;

  if ( _idx < 0 || _idx >= w*h )
    return true;

  return false;
}

Ui_pix *ui_get_pix( Ui_pix **__pixs, int x, int y, int w, int h ) {

  if ( !__pixs || ui_pix_ovf( x, y, w, h ) )
    return NULL;

  return __pixs[ w*y + x ];
}

void ui_set_pix( Ui_pix **__pixs, int x, int y, int w, int h, Ui_pix pix ) {

  Ui_pix *_pix;

  if ( !__pixs || ui_pix_ovf( x, y, w, h ) )
    return;

  _pix = __pixs[ w*y + x ];

  *_pix = pix;

}

void ui_box_seek( Ui *ui, int idx, int x, int y ) {

  Ui_box *box;

  box = ui_get_box_by_idx( ui, idx );

  if ( !box )
    return;

  if ( y*box->w + x >= box->__len )
		return;

  if ( x > -1 ) box->cx = x;
  if ( y > -1 ) box->cy = y;

}

void ui_dump_box( Ui *ui, int idx ) {

  Ui_box *box;
  Ui_pix *pix, _pix;
  int i, x, y, box_x, box_y, box_w, box_h, scr_w, scr_h;

  box = ui_get_box_by_idx( ui, idx );

  if ( !box )
    return;

  /* shorthands */
  box_x = box->x;
  box_y = box->y;
  box_w = box->w;
  box_h = box->h;
  scr_w = ui->scr.w;
  scr_h = ui->scr.h;

  x = box_x;
  y = box_y;

  for (i=0; i < box->__len; i++) {

    pix = box->__pixs[ i ];
    _pix = *pix;

    if ( x >= box_x + box_w ) {
      y++; /* go to the next line */
      x = box_x; /* fall back to the begining of the new line */
    }

    if ( y >= box_y + box_h ) break;

    ui_set_pix( ui->__pixs, x, y, scr_w, scr_h, _pix );

    x++;

  }

}

void ui_box_pad( Ui *ui, int idx, const char *pad ) {

  Ui_box *box;

  box = ui_get_box_by_idx( ui, idx );

  if ( !box )
    return;

  sscanf( pad, "%d %d %d %d", &box->pad[0], &box->pad[1], &box->pad[2], &box->pad[3] );

  ui_clear_box( ui, idx );

}


void ui_box_put( Ui *ui, int idx, const char *frmt, ... ) {

  Ui_box *box;
  Ui_pix _pix;
  va_list _args;
  char _buff[ UI_MAX_BUFF_LEN ];
  char __frm[ UI_MAX_BUFF_LEN ];

  int i, j, box_w, box_h, *pad, cx_off, cx_top, *cx, *cy;

  box = ui_get_box_by_idx( ui, idx );

  if ( !box || !frmt )
    return;

  va_start( _args, frmt );
  vsnprintf( _buff, UI_MAX_BUFF_LEN, frmt, _args );
  va_end( _args );

  /* shorthands */
  box_w = box->w;
  box_h = box->h;
  cx_off = box->cx_off;
  cx_top = box->cx_top;
  cx = &box->cx; /* cursor x */
  cy = &box->cy; /* cursor y */
  pad = box->pad; /* box padding */

  cx_top = cx_top == box_w ? box_w-pad[1] : cx_top;
  cx_off = !cx_off ? pad[ 3 ] : cx_off;

  /* process string */
  for ( i=0; _buff[ i ]; i++ ) {

    if ( __frmxor( ui->__frm ) == 0 ) { /* if ui format is null use default box format */
      _frm_cpy( _pix.frm, box->frm );
    } else {
      _frm_cpy( _pix.frm, ui->__frm ); /* else use ui format */
    }

    if ( *cx == cx_top - 1 ) {

      if ( i && _buff[ i - 1 ] == ' ' && _buff[ i ] != ' ' ) {
        _pix.c = ' ';
        ui_set_pix( box->__pixs, *cx, *cy, box_w, box_h, _pix );
        (*cx)++;
      } else if ( _buff[ i + 1 ] != ' ' && _buff[ i ] != ' ' ) {
        _pix.c = '-';
        ui_set_pix( box->__pixs, *cx, *cy, box_w, box_h, _pix );
        (*cx)++;

      }

    }


    if ( *cx >= cx_top ) {
      (*cy)++; /* go to the next line */
      *cx = cx_off; /* fall back to the begining of the new line */
    }

    if ( *cy >= box_h - pad[2] ) { /* scroll */

      for ( j=box_w; j < box->__len; j++ ) {
        *(box->__pixs[ j-box_w ]) = *(box->__pixs[ j ]);
        box->__pixs[ j ]->c = ' ';
      }

      (*cy)--;
      *cx = cx_off;
    }

    _pix.c = _buff[ i ];

    if ( _pix.c == '\n' ) {

      while ( *cx < cx_top ) {
        _pix.c = ' ';
        ui_set_pix(box->__pixs, *cx, *cy, box_w, box_h, _pix );
        (*cx)++;
      }

    } else if ( _pix.c == '\t' ) {

      _pix.c = ' ';

      j=0;
      while ( *cx < cx_top && j < UI_TAB_SIZE ) {
        ui_set_pix( box->__pixs, *cx, *cy, box_w, box_h, _pix );
        (*cx)++; j++;
      }

    } else if ( _pix.c == '@' && _buff[ i + 1 ] == '{' ) {

      j=0;
      i+=2;

      while ( _buff[ i ] != '}' && _buff[ i + 1 ] ) {

        if ( j >= UI_MAX_BUFF_LEN ) {
          _frm_rs( ui->__frm );
          break;
        }

        if ( _buff[ i ] != ' ' ) {
          __frm[ j ] = _buff[ i ];
          __frm[ j + 1 ] = 0;
          j++;
        }

        i++;
      }

      _frm_parse( ui->__frm, box->frm, __frm );

    } else {
      ui_set_pix(box->__pixs, *cx, *cy, box_w, box_h, _pix );
      (*cx)++;
    }

  }

}

void ui_kill_box( Ui *ui, int idx ) {

  Ui_box *box;

  box = ui_get_box_by_idx( ui, idx );

  if ( !box )
    return;

  kill_pixs( box->__pixs, box->__len );
  ui->boxes[ idx ] = NULL;
  free( box );

}

Ui_config *ui_config( Ui *ui ) {

  if ( !ui )
    return NULL;

  return &(ui->config);

}

void ui_draw( FILE *stream, Ui *ui ) {

  Ui_pix *pix; /* temporary pixel */
  Ui_cpix *cpix; /* temporary cache pixel */

  int   i,
        j,
        scr_w;
  int   o_xor=0, /* old format check sum */
        xor, /* current pixel format check sum */
        lxor=0; /* last pixel format checsum */

  char  __buff[ 8096 ],
        __frm[ UI_MAX_SFRM_LEN ] = "";

  /* prepare buffer */
  memset( __buff, '\0', sizeof( __buff ) );
  setvbuf( stream, __buff, _IOFBF, sizeof( __buff ) );

  if ( !stream || !ui )
    return;

  scr_w = ui->scr.w;

  for ( i=0; i < ui->__len; i++ ) {

    pix = ui->__pixs[ i ];
    cpix = ui->__cache[ i ];

    if ( !pix ) {
      fprintf( stream, "\033[1;31;47m UI FATAL ERROR \033[0m\n");
      break;
    }

    /* avoid pixel format recomputing */
    xor = __frmxor( pix->frm ); /* format checksum to compare */

    if ( xor != cpix->csum ) { /* compare current pixel with the cache */

      if ( o_xor != xor ) {

        /* reset format buffer */
        strcpy( __frm, "\033[" );

        /* compute pixel format */
        for ( j=0; j < __frmidx( pix->frm ); j++ ) {
          if ( pix->frm[ j ] == -1 ) continue;
          sprintf( __frm + strlen( __frm ), ";%d", pix->frm[ j ] );
        }
        sprintf( __frm + strlen( __frm ), "m" );
        o_xor = xor;
      }

      cpix->csum = xor;
      memcpy( cpix->sfrm, __frm, UI_MAX_SFRM_LEN*sizeof( char ) );

    }

    if ( xor != cpix->csum ) {
      fprintf( stream, "%s", __frm );
    } else {

      if ( xor != lxor ) {
        fprintf( stream, "%s", cpix->sfrm );
        lxor = xor;
      }

    }

    putc( pix->c, stream );

    if ( (i+1)%scr_w == 0 ) {
      fprintf( stream, "\033[0m\n%s", cpix->sfrm );
    }

  }

  fprintf( stream, "\033[0m" );

  fflush( stream );

}

int ui_get_w( Ui *ui ) {
  if ( !ui )
    return -1;

  return ui->scr.w;
}

int ui_get_h( Ui *ui ) {
  if ( !ui )
    return -1;

  return ui->scr.h;
}
