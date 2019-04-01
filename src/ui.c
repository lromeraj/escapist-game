/**
* @brief Ui source code
*
* @file ui.c
* @author Javier Romera
* @date 17/03/2019
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

#define UI_MAX_BUFF_LEN 500 /*!< @brief Maximum buffer length */
#define UI_MAX_FRM_LEN 100 /*!< @brief Maximum format length */
#define UI_TAB_SIZE 3 /*!< @brief Tab key size */
#define UI_MAX_BOXES 15 /*!< @brief Maximum quantity of boxes per UI */

/*!
* @brief Basic pixel structure
*/
struct _Ui_pix {
  char c; /*!< @brief Pixel char */
  char frm[ UI_MAX_FRM_LEN ];  /*!< @brief Pixel format */
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
  char frm[ UI_MAX_FRM_LEN ]; /*!< @brief Default format for the content of the box */
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
  char __frm[ UI_MAX_FRM_LEN ]; /*!< @brief Temporary format */
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


int vsnprintf( char *buf, size_t size, const char *fmt, va_list list );
int snprintf(char *buf, size_t size, const char *fmt, ...);

/*******************************/

void ui_frm( Ui *ui, int num, ... ) {

  int i;
  char _buff[ UI_MAX_FRM_LEN ] = "\033[";
  va_list _args;
  int _arg;

  va_start( _args, num );

  for ( i=0; i < num; i++ ) {

    _arg = va_arg( _args, int );

    sprintf( _buff+strlen( _buff ), "%d", _arg );

    if ( i < num-1 ) {
      sprintf( _buff+strlen( _buff ), ";" );
    }

  }

  sprintf( _buff+strlen( _buff ), "m" );
  strncpy( ui->__frm, _buff, UI_MAX_FRM_LEN );


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

    for ( i=0; i < UI_MAX_BOXES; i++) {
      ui->boxes[ i ] = NULL;
    }

    ui_frm( ui, 1, S_DEFAULT );

    ui->__pixs = alloc_pixs( ui->__len );

    if ( ui->__pixs ) {

      for ( i=0; i < ui->__len; i++ ) {
        pix = ui->__pixs[ i ];
        pix->c = ' ';
        strcpy( pix->frm, ui->__frm );
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
    sprintf( ui->__pixs[ i ]->frm, "\033[%dm", c );
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
    sprintf( box->__pixs[ i ]->frm, "\033[%dm", c );
  }

  ui_dump_box( ui, idx );

}

void ui_box_frm( Ui *ui, int idx, const char *frmt, ... ) {

  Ui_box *box;
  va_list _args;
  char _buff[ UI_MAX_FRM_LEN ];

  box = ui_get_box_by_idx( ui, idx );

  if ( !box || !frmt )
    return;

  va_start( _args, frmt );
  vsnprintf( _buff, UI_MAX_FRM_LEN, frmt, _args );
  va_end( _args );

  strncpy( box->frm, _buff, UI_MAX_FRM_LEN );

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
  Ui_pix **__pixs = (Ui_pix**) malloc( __len * sizeof(Ui_pix*) );

  if ( __pixs ) {

    for ( i=0; i < __len; i++ ) {

      pix = (Ui_pix*) malloc( sizeof(Ui_pix) );

      if ( pix ) {
        __pixs[ i ] = pix;
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

    box->id = idx;
    box->x = x;
    box->y = y;
    box->w = w;
    box->h = h;
    box->cx = 0;
    box->cy = 0;
    box->bg = DEFAULT_BOX_BG_COLOR;
    box->frm[ 0 ] = 0;
    box->__len = w*h;

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
  char __frm[ UI_MAX_FRM_LEN ];

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

    sprintf( _pix.frm, "%s", ui->__frm ); /* set pix format with the temp ui format */

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

    } else if ( _pix.c == '\033' ) {

      j=0;
      while ( _pix.c != 'm' ) {

        if ( j >= UI_MAX_FRM_LEN ) { /* format overflow */
          strcpy( __frm, "\033[0" );
          j=3;
          break;
        }

        __frm[ j ] = _pix.c;
        __frm[ j + 1 ] = 0;
        j++; i++;
        _pix.c = _buff[ i ];

      }

      __frm[ j ] = 'm';
      __frm[ j + 1 ] = 0;

      if ( !strcmp( __frm, "\033[0m" ) ) {
        strncpy( ui->__frm, box->frm, UI_MAX_FRM_LEN );
      } else {
        snprintf( ui->__frm, UI_MAX_FRM_LEN, "%s", __frm );
      }

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

  int i, scr_w;
  Ui_pix *pix;

  if ( !stream || !ui )
    return;

  scr_w = ui->scr.w;

  for ( i=0; i < ui->__len; i++ ) {

    pix = ui->__pixs[ i ];

    if ( !pix ) {
      fprintf( stream, "\033[1;31;47m UI FATAL ERROR \033[0m\n");
      break;
    }

    fprintf( stream, "%s%c\033[0m",pix->frm, pix->c );

    if ( (i+1)%scr_w == 0 ) {
      fprintf( stream, "\n");
    }

  }

}
