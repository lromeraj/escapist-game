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
#define FRM_LEN 30
#define TAB_SIZE 3
#define MAX_BOXES 10

/*!
* @brief Basic pixel structure
*/
struct _Ui_pix {
  char c; /*!< @brief Pixel char */
  char frm[ FRM_LEN ];  /*!< @brief Pixel format */
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
  int pad[4];  /*!< @brief Box padding */
  Color bg;  /*!< @brief Background color */
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
  Ui_box *boxes[ MAX_BOXES ]; /*!< @brief Boxes */
  Ui_pix **__pixs; /*!< @brief Pixels buffer */
  int __len; /*!< @brief Number of pixels */
  char __frm[ FRM_LEN ]; /*!< @brief Temporary format */
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


/** Gets a pixel that is located in a given position
* @param {Ui_pix**} __pixs - the array where the pixel should be located
* @param {int} x - Represents the x position ( column of the matrix )
* @param {int} y - Represents the y position ( row of the matrix )
* @param {int} w - Represents the space width
* @param {int} h - Represents the space height
* @retval {Ui_pix*} - Returns a pointer to the found pixel, else returns NULL
*/
Ui_pix *ui_get_pix( Ui_pix **__pixs, int x, int y, int w, int h );


/** Sets a given pixel in a given position
* @param {Ui_pix**} __pixs - the array where the pixel should be located
* @param {int} x - Represents the x position ( column of the matrix )
* @param {int} y - Represents the y position ( row of the matrix )
* @param {int} w - Represents the space width
* @param {int} h - Represents the space height
* @param {Ui_pix} pix - Struct of the pixel to be setted
*/
void ui_set_pix( Ui_pix **__pixs, int x, int y, int w, int h, Ui_pix pix );


/** Finds a box in a given UI
* @param {Ui*} ui - UI where the box should be located
* @param {int} id - The id of the requested box
* @retval {Ui_box*} - If the box was found returns a pointer
* to the requested box, else returns NULL
*/
Ui_box* ui_get_box( Ui* ui, int id );


/** This functions dumps all the box data inside the Ui
* @param {Ui*} ui - The ui where data sohuld be dumped
* @param {int} id - The id of the box to be dumped
*/
void ui_dump_box( Ui *ui, int id );

/** Destroys a given box
* @param {Ui_box*} box - Box pointer to be destroyed
*/
void ui_kill_box( Ui_box* );

/*******************************/

void ui_frm( Ui *ui, int num, ... ) {

  int i;
  char _buff[ 100 ] = "\e[";
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
  strcpy( ui->__frm, _buff );

  va_end( _args );
}

Ui *ui_init( int w, int h ) {

  Ui *ui = (Ui*) calloc( 1, sizeof( Ui ) );
  Ui_pix *pix;
  int i;

  if ( ui ) {

    ui->scr.w = w;
    ui->scr.h = h;
    ui->__len = w*h;

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

  if ( ui ) {

    kill_pixs( ui->__pixs, ui->__len );

    for ( i=0; i < MAX_BOXES; i++ ) {
      ui_kill_box( ui->boxes[i] );
    }

    free( ui );

  }

}

void ui_bg( Ui *ui, Color c ) {

  int i;

  if ( ui ) {
    for ( i=0; i < ui->__len; i++ ) {
      sprintf( ui->__pixs[ i ]->frm, "\e[%dm", c );
    }
  }

}

void ui_rs( Ui *ui ) {

  if ( !ui )
    return;

  ui_frm( ui, 3, DEFAULT_TXT_FORMAT, DEFAULT_TXT_BG_COLOR, DEFAULT_TXT_FG_COLOR );

}

void ui_box_bg( Ui *ui, int id, Color c ) {

  int i;
  Ui_box *box;
  if ( ui ) {
    box = ui_get_box( ui, id );
    if ( box ) {
      box->bg = c;
      for (i=0; i < box->__len; i++ ) {
        sprintf( box->__pixs[ i ]->frm, "\e[%dm", c );
      }
      ui_dump_box( ui, id );
    }
  }
}

void ui_clear_box( Ui *ui, int id ) {

  int i;
  Ui_box *box;

  if ( !ui )
    return;

  box = ui_get_box( ui, id );

  if ( !box )
    return;

  box->cx = box->pad[3]; // reset
  box->cy = box->pad[0];

  for ( i=0; i < box->__len; i++ ) {
    box->__pixs[ i ]->c = ' ';
  }

}

void ui_clear( Ui *ui ) {

  int i=0;

  while ( ui->boxes[ i ] ) {
    ui_clear_box( ui, ui->boxes[ i ]->id );
    i++;
  }

}

void kill_pixs( Ui_pix **__pixs, int __len ) {

  int i;

  if ( __pixs ) {
    for (i=0; i < __len; i++ ) {
      if ( __pixs[ i ] ) {
        free( __pixs[ i ] );
      }
    }
    free( __pixs );
  }

}

Ui_pix **alloc_pixs( int __len ) {

  int i;
  Ui_pix *pix;
  Ui_pix **__pixs = (Ui_pix**) calloc( __len, sizeof(Ui_pix*) );

  if ( __pixs ) {
    for ( i=0; i < __len; i++ ) {

      pix = (Ui_pix*) calloc( 1, sizeof(Ui_pix) );

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

void ui_new_box( Ui *ui, int id, int x, int y, int w, int h ) {

  int i;
  Ui_pix *pix;
  Ui_box *box;
  static int _idx=0;

  // check new box id
  for ( i=0; i < _idx; i++ ) {
    box = ui->boxes[i];
    if ( box->id == id )
      return;
  }

  if ( _idx < MAX_BOXES ) {

    box = (Ui_box*) calloc( 1, sizeof( Ui_box ) );

    if ( box ) {

      box->id = id;
      box->x = x;
      box->y = y;
      box->w = w;
      box->h = h;
      box->bg = DEFAULT_BOX_BG_COLOR;
      box->__len = w*h;
      box->cx = 0;
      box->cy = 0;

      box->__pixs = alloc_pixs( box->__len );

      if ( box->__pixs ) {

        ui->boxes[ _idx ] = box; // store the box inside the ui

        for (i=0; i < box->__len; i++) {
          pix = box->__pixs[ i ];
          pix->c = ' ';
          sprintf( pix->frm, "%s", ui->__frm );
        }

        _idx++;

        ui_dump_box( ui, id );

      } else {
        ui_kill_box( box );
      }

    }

  }

}

Ui_box *ui_get_box( Ui *ui, int id ) {

  int i;
  Ui_box *box = NULL;

  for ( i=0; i<MAX_BOXES; i++) {

    box = ui->boxes[i];

    if ( box ) {
      if ( box->id != id ) {
        box = NULL;
      } else {
        break;
      }
    }
  }

  return box;

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

void ui_box_seek( Ui *ui, int id, int x, int y ) {

  Ui_box *box;

  if ( !ui )
    return;

  box = ui_get_box( ui, id );

  if ( !box )
    return;

  if ( y*box->w + x >= box->__len )
		return;

  box->cx = x;
  box->cy = y;

}

void ui_dump_box( Ui *ui, int id ) {

  Ui_box *box;
  Ui_pix *pix, _pix;
  int i, x, y, box_x, box_y, box_w, box_h, scr_w, scr_h;

  box = ui_get_box( ui, id );

  if ( !box )
    return;

  // shorthands
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
      y++; // go to the next line
      x = box_x; // fall back to the begining of the new line
    }

    if ( y >= box_y + box_h ) break;

    ui_set_pix( ui->__pixs, x, y, scr_w, scr_h, _pix );

    x++;

  }

}

void ui_box_pad( Ui *ui, int id, const char *pad ) {

  Ui_box *box;

  box = ui_get_box( ui, id );

  if ( !box )
    return;

  sscanf( pad, "%d %d %d %d", &box->pad[0], &box->pad[1], &box->pad[2], &box->pad[3] );

  ui_clear_box( ui, id );

}

void ui_box_put( Ui *ui, int id, const char *fmt, ... ) {

  Ui_box *box;
  Ui_pix _pix;
  va_list _args;
  char _buff[1000];
  int i, j, box_w, box_h, *pad, *cx, *cy;

  box = ui_get_box( ui, id );

  if ( !box )
    return;

  va_start( _args, fmt );
  vsprintf( _buff, fmt, _args );
  va_end( _args );


  // shorthands
  box_w = box->w;
  box_h = box->h;
  cx = &box->cx; // cursor x
  cy = &box->cy; // cursor y
  pad = box->pad;

  // concat
  for ( i=0; _buff[i]; i++ ) {

    if ( *cx >= box_w - pad[1] ) {
      (*cy)++; // go to the next line
      *cx = pad[3]; // fall back to the begining of the new line
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

    sprintf( _pix.frm, "%s", ui->__frm ); // set pix format with the temp ui format

    if ( _pix.c == '\n' ) {

      while ( *cx < box_w - pad[1] ) {
        _pix.c = ' ';
        ui_set_pix(box->__pixs, *cx, *cy, box_w, box_h, _pix );
        (*cx)++;
      }

    } else if ( _pix.c == '\t' ) {

      _pix.c = ' ';

      j=0;
      while ( *cx < box_w - pad[1] && j < TAB_SIZE ) {
        ui_set_pix( box->__pixs, *cx, *cy, box_w, box_h, _pix );
        (*cx)++; j++;
      }

    } else {
      ui_set_pix(box->__pixs, *cx, *cy, box_w, box_h, _pix );
      (*cx)++;
    }

  }

  // dump the box data to the ui buffer
  ui_dump_box( ui, id );

}

void ui_kill_box( Ui_box *box  ) {

  if ( box ) {
    kill_pixs( box->__pixs, box->__len );
    free( box );
  }

}

void ui_draw( Ui *ui ) {

  int i, j;
  int scr_w = ui->scr.w;
  int scr_h = ui->scr.h;

  /* !!! IMPROVE THIS
  * Use only one bucle
  */
  for ( i=0; i < scr_h; i++ ) {

    for ( j=0; j < scr_w; j++ ) {

      Ui_pix *pix = ui_get_pix( ui->__pixs, j, i, scr_w, scr_h );

      if ( !pix ) {
          printf("\e[1;31;47m UI FATAL ERROR \e[0m\n");
          return;
      }

      printf( "%s%c\e[0m",pix->frm, pix->c );

    }

    printf("\n");

  }

}
