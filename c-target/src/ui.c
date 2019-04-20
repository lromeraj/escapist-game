/**
* @brief Ui source code
*
* @file ui.c
* @author Javier Romera
* @copyright GNU Public License
*/

#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

#define DEFAULT_TXT_BG_COLOR BG_WHITE
#define DEFAULT_TXT_FG_COLOR FG_BLACK
#define DEFAULT_TXT_FORMAT S_DEFAULT
#define DEFAULT_BOX_BG_COLOR BG_WHITE
#define DEFAULT_BG_COLOR BG_WHITE


#define UI_TAB_SIZE 3 /*!< @brief Tab key size */
#define UI_MAX_BOXES 15 /*!< @brief Maximum quantity of boxes per UI */
#define UI_MAX_BUFF_LEN 500 /*!< @brief Maximum buffer length */
#define UI_MAX_FRM 20 /*!< @brief Maximum number of parameters for formatting */

#define UI_MAX_FRM_LEN ( UI_MAX_FRM + 2 )  /*!< @brief Maximum length of the format array */

#define __frmidx( __frm ) ( __frm[ UI_MAX_FRM_LEN - 2 ] ) /* get the destination index of the format */
#define __frmxor( __frm ) ( __frm[ UI_MAX_FRM_LEN - 1 ] ) /* get the checksum of the format */

/*!
* @brief Basic pixel structure
*/
struct _Ui_pix {
  char c; /*!< @brief Pixel char */
  int frm[ UI_MAX_FRM_LEN ]; /*!< @brief Pixel format */
};

/*!
* @brief Main box structure
*/
struct _Ui_box {
  Ui_pix **__pixs; /*!< @brief Pixels array */
  int id; /*!< @brief Box identification */
  int x; /*!< @brief Coordenate x */
  int y; /*!< @brief Coordenate y */
  int w; /*!< @brief Width */
  int h; /*!< @brief Height */
  int cx; /*!< @brief Position of the x cursor */
  int cy;  /*!< @brief Position of the y cursor */
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
* @brief Main UI structure
*/
struct _Ui {
  Ui_screen scr; /*!< @brief Screen */
  Ui_box *boxes[ UI_MAX_BOXES ]; /*!< @brief Boxes */
  Ui_pix **__pixs; /*!< @brief Pixels buffer */
  int __len; /*!< @brief Number of pixels */
  int __frm[ UI_MAX_FRM_LEN ]; /*!< @brief Temporary format */
};

/****** PRIVATE FUNCTIONS ******/

/**
* @brief Reserves memory to alloc a certain quantity of pixels
* @param {int} __len - The quantity of pixels to be allocted
* @retval {Ui_pix**} - Returns a pointer which points to other pixels pointers
*/
Ui_pix **alloc_pixs( int __len );


/**
* @brief This function destroys an array of pixels to liberate memory
* @param {Ui_pix**} __pixs - Pointer which points to the data
* @param {int} __len - The length of the pixs matrix
*/
void kill_pixs( Ui_pix **__pixs, int __len );


/**
* @brief Checks if a given position ( usually for pixels ) is overflowing the max size
* @param {int} x - Represents the x position ( column of the matrix )
* @param {int} y - Represents the y position ( row of the matrix )
* @param {int} w - Represents the space width
* @param {int} h - Represents the space height
* @retval {bool} - Returns a boolean value, false if there is no overflow, else true
*/
bool ui_pix_ovf( int x, int y, int w, int h );


/**
* @brief Gets a pixel that is located in a given position
* @param {Ui_pix**} __pixs - the array where the pixel should be located
* @param {int} x - Represents the x position ( column of the matrix )
* @param {int} y - Represents the y position ( row of the matrix )
* @param {int} w - Represents the space width
* @param {int} h - Represents the space height
* @retval {Ui_pix*} - Returns a pointer to the found pixel, else returns NULL
*/
Ui_pix *ui_get_pix( Ui_pix **__pixs, int x, int y, int w, int h );


/**
* @brief Sets a given pixel in a given position
* @param {Ui_pix**} __pixs - the array where the pixel should be located
* @param {int} x - Represents the x position ( column of the matrix )
* @param {int} y - Represents the y position ( row of the matrix )
* @param {int} w - Represents the space width
* @param {int} h - Represents the space height
* @param {Ui_pix} pix - Struct of the pixel to be setted
*/
void ui_set_pix( Ui_pix **__pixs, int x, int y, int w, int h, Ui_pix pix );

/**
* @brief Finds a box by it's id (slow)
* @param {Ui*} ui - UI where the box should be located
* @param {int} id - The id of the requested box
* @retval {Ui_box*} - If the box was found returns a pointer
* to the requested box, else returns NULL
*/
Ui_box* ui_get_box_by_id( Ui* ui, int id );


/**
* @brief Gets a box by it's idx (fast)
* @param {Ui*} ui - UI where the box should be located
* @param {int} id - The id of the requested box
* @retval {Ui_box*} - The box at the given index (can be NULL)
*/
Ui_box* ui_get_box_by_idx( Ui* ui, int idx );


/**
* @brief Destroys a given box
* @param {Ui*} ui - Ui where the box should be removed
* @param {int} idx - Box index
*/
void ui_kill_box( Ui* ui, int idx );


/**
* @brief Resets the format
* @param {int*} frm - Format array to be reseted
*/
void _frm_rs( int *frm );


/**
* @brief Copies source format into destinationformat
* @param {int*} dest - Format array destination
* @param {int*} src - Format array source
*/
void _frm_cpy( int *dest, int *src );


/**
* @brief Adds a value to a given format
* @param {int*} frm - Format array to be modified
* @param {int} v - Value to be added
*/
void _frm_add( int *frm, int v );


/**
* @brief Adds a list of values into a format array
* @param {int*} frm - format array destination
* @param {int} n - Number of parameters to be added
* @param {va_list} list - List of parameters to be inserted
*/
void _frm( int *frm, int n, va_list list );


/**
* @brief Parses a given format string into a number format array
* @param {int*} frm - Format destination
* @param {int*} defrm - Default format in case of reset
* @param {char*} sfrm - Format string
*/
void _frm_parse( int *frm, int *defrm, const char *sfrm );

int vsnprintf( char *buf, size_t size, const char *fmt, va_list list );
int snprintf( char *buf, size_t size, const char *fmt, ... );

/*******************************/


/** formatting functions *****************/
void _frm_rs( int *frm ) {

  int i;

  if ( !frm )
    return;

  for ( i=0; i < UI_MAX_FRM; i++ ) {
    frm[ i ] = -1;
  }

  __frmxor( frm ) = 0;
  __frmidx( frm ) = 0;

  _frm_add( frm, 0 );

}

void _frm_cpy( int *dest, int *src ) {

  int i;

  if ( !dest || !src )
    return;

  for ( i=0; i < UI_MAX_FRM_LEN; i++ ) {
    dest[ i ] = src[ i ];
  }

}

void _frm_add( int *frm, int v ) {

  int _i;

  if ( !frm )
    return;

  _i = __frmidx( frm );

  if ( _i < UI_MAX_FRM ) {
    frm[ _i ] = v;
    __frmxor( frm ) += v;
    __frmxor( frm ) = __frmxor( frm ) << 3 | __frmxor( frm ) >> (32 - 3);
    __frmidx( frm )++;
  }

}

void _frm_parse( int *frm, int *defrm, const char *sfrm ) {

  int i, j, _i, len;
  short r, g, b;
  char c;
  bool addChar, addSn;
  char strp[ UI_MAX_BUFF_LEN ] = ""; /* string parameter */

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

      if ( !strncmp( strp, "frgb", 4 ) ) {
        sscanf( strp, "frgb(%hd,%hd,%hd)", &r, &g, &b );
        _frm_add( frm, 38 );
        _frm_add( frm, 2 );
        _frm_add( frm, r );
        _frm_add( frm, g );
        _frm_add( frm, b );
      } else if ( !strncmp( strp, "brgb", 4 ) ) {
        sscanf( strp, "brgb(%hd,%hd,%hd)", &r, &g, &b );
        _frm_add( frm, 48 );
        _frm_add( frm, 2 );
        _frm_add( frm, r );
        _frm_add( frm, g );
        _frm_add( frm, b );
      } else if ( !strncmp( strp, "$", 1 ) ) {

        for (j=0; j<UI_MAX_FRM_LEN; j++) {
          printf("%d ", frm[ j ] );
        }

        printf("\n");

      } else {

        _i = atoi( strp );

        if ( !_i && defrm != NULL ) {
          _frm_cpy( frm, defrm );
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

Ui *ui_init( int w, int h ) {

  Ui *ui = (Ui*) malloc( sizeof( Ui ) );
  Ui_pix *pix;
  int i;

  if ( ui ) {

    ui->scr.w = w;
    ui->scr.h = h;
    ui->__len = w*h;
    _frm_rs( ui->__frm );

    for ( i=0; i < UI_MAX_BOXES; i++) {
      ui->boxes[ i ] = NULL;
    }

    ui_frm( ui, 1, S_DEFAULT );

    ui->__pixs = alloc_pixs( ui->__len );

    if ( ui->__pixs ) {

      for ( i=0; i < ui->__len; i++ ) {
        pix = ui->__pixs[ i ];
        pix->c = ' ';
        _frm_cpy( pix->frm,  ui->__frm );
      }

    } else {
      ui_destroy( ui );
    }

  }

  return ui;

}

void ui_destroy( Ui *ui ) {

  int i;

  if ( !ui )
    return;

  kill_pixs( ui->__pixs, ui->__len );

  for ( i=0; i < UI_MAX_BOXES; i++ ) {
    ui_kill_box( ui, i );
  }

  free( ui );

}

void ui_bg( Ui *ui, Color c ) {

  int i;

  if ( !ui )
    return;

  for ( i=0; i < ui->__len; i++ ) {
    _frm_rs( ui->__pixs[ i ]->frm );
    _frm_add( ui->__pixs[ i ]->frm, c );
  }

}

void ui_rs( Ui *ui ) {

  if ( !ui )
    return;

  ui_frm( ui, 3, DEFAULT_TXT_FORMAT, DEFAULT_TXT_BG_COLOR, DEFAULT_TXT_FG_COLOR );

}

void ui_box_bg( Ui *ui, int idx, Color c ) {

  int i;
  Ui_box *box;

  box = ui_get_box_by_idx( ui, idx );

  if ( !box )
    return;

  box->bg = c;

  for (i=0; i < box->__len; i++ ) {
    _frm_rs( box->__pixs[ i ]->frm );
    _frm_add( box->__pixs[ i ]->frm, c );
  }

  ui_dump_box( ui, idx );

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

Ui_pix **alloc_pixs( int __len ) {

  int i;
  Ui_pix *pix;
  Ui_pix **__pixs = (Ui_pix**) malloc(__len * sizeof(Ui_pix*) );

  if ( __pixs ) {

    for ( i=0; i < __len; i++ ) {

      pix = (Ui_pix*) malloc( sizeof(Ui_pix) );

      if ( pix ) {
        __pixs[ i ] = pix;
        _frm_rs( pix->frm );
        pix->c = '\0';
      } else {
        kill_pixs( __pixs, i-1 );
        break;
      }

    }

  }

  return __pixs;

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

  box->cx = x;
  box->cy = y;

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

  int i, j, box_w, box_h, *pad, *cx, *cy;

  box = ui_get_box_by_idx( ui, idx );

  if ( !box || !frmt )
    return;

  va_start( _args, frmt );
  vsnprintf( _buff, UI_MAX_BUFF_LEN, frmt, _args );
  va_end( _args );

  /* shorthands */
  box_w = box->w;
  box_h = box->h;
  cx = &box->cx; /* cursor x */
  cy = &box->cy; /* cursor y */
  pad = box->pad; /* box padding */

  /* concat */
  for ( i=0; _buff[ i ]; i++ ) {

    if ( *cx >= box_w - pad[1] ) {
      (*cy)++; /* go to the next line */
      *cx = pad[3]; /* fall back to the begining of the new line */
    }

    if ( *cy >= box_h - pad[2] ) {

      for ( j=box_w; j < box->__len; j++ ) {
        *(box->__pixs[ j-box_w ]) = *(box->__pixs[ j ]);
        box->__pixs[ j ]->c = ' ';
      }

      (*cy)--;
      *cx=pad[3];
    }

    _pix.c = _buff[ i ];

    if ( __frmxor( ui->__frm ) == 0 ) { /* if ui format is null use default box format */
      _frm_cpy( _pix.frm, box->frm );
    } else {
      _frm_cpy( _pix.frm, ui->__frm ); /* else use ui format */
    }

    if ( _pix.c == '\n' ) {

      while ( *cx < box_w - pad[1] ) {
        _pix.c = ' ';
        ui_set_pix(box->__pixs, *cx, *cy, box_w, box_h, _pix );
        (*cx)++;
      }

    } else if ( _pix.c == '\t' ) {

      _pix.c = ' ';

      j=0;
      while ( *cx < box_w - pad[1] && j < UI_TAB_SIZE ) {
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

void ui_draw( FILE *stream, Ui *ui ) {

  Ui_pix *pix; /* temporary pixel */
  int i, j, scr_w;
  int o_xor=0, /* old format check sum */
      xor;  /* current format check sum */
  char __frm[ UI_MAX_BUFF_LEN ] = "\033[";

  if ( !stream || !ui )
    return;

  scr_w = ui->scr.w;

  for ( i=0; i < ui->__len; i++ ) {

    pix = ui->__pixs[ i ];

    if ( !pix ) {
      fprintf( stream, "\033[1;31;47m UI FATAL ERROR \033[0m\n");
      break;
    }

    /* avoid pixel format recomputing */
    xor = __frmxor( pix->frm ); /* request format checksum to compare */

    if ( o_xor != xor ) {

      /* reset format buffer */
      strcpy( __frm, "\033[" );

      /* compute pixel format */
      for ( j=0; j < UI_MAX_FRM; j++ ) {
        if ( pix->frm[j] == -1 ) continue;
        sprintf( __frm + strlen( __frm ), ";%d", pix->frm[ j ] );
      }
      sprintf( __frm + strlen( __frm ), "m" );
      o_xor = xor;
    }

    fprintf( stream, "%s%c", __frm, pix->c );

    if ( (i+1)%scr_w == 0 ) {
      fprintf( stream, "\033[0m\n");
    }

  }

}
