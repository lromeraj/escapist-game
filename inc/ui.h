/**
* @brief User interface based on chars
*
* @file ui.h
* @author Javier Romera
* @version 1.1.3-stable
* @date 09/04/2019
* @copyright GNU Public License
*/

#ifndef UI_H
#define UI_H

#include <wchar.h>
#include <stdio.h>

/*!
* @brief Text colors
*/
typedef enum {
  BG_BLACK=40, /*!< Background black */
  BG_RED=41, /*!< Background red */
  BG_GREEN=42, /*!< Background green */
  BG_YELLOW=43, /*!< Background yellow */
  BG_BLUE=44, /*!< Background blue */
  BG_PURPLE=45, /*!< Background purple */
  BG_CYAN=46, /*!< Background cyan */
  BG_WHITE=47, /*!< Background white */
  FG_BLACK=30, /*!< Foreground black */
  FG_RED=31, /*!< Foreground red */
  FG_GREEN=32, /*!< Foreground green */
  FG_YELLOW=33, /*!< Foreground yellow */
  FG_BLUE=34, /*!< Foreground blue */
  FG_PURPLE=35, /*!< Foreground purple */
  FG_CYAN=36, /*!< Foreground cyan */
  FG_WHITE=37 /*!< Foreground white */
} Color;

/*!
* @brief Text formats
*/
typedef enum {
  S_DEFAULT=0, /*!< Resets text format */
  S_BOLD=1,  /*!< Bold text */
  S_DIM=2,  /*!< Small text */
  S_UNDERLINED=4,  /*!< Underlined text */
  S_BLINK=5,  /*!< Blink text */
  S_REVERSE=7,  /*!< Reversed text format */
  S_HIDDEN=9  /*!< Hidden text */
} Format;

typedef struct _Ui_screen Ui_screen;
typedef struct _Ui_pix Ui_pix;
typedef struct _Ui_cpix Ui_cpix;
typedef struct _Ui_box Ui_box;
typedef struct _Ui Ui;


/**
* @brief Initializes UI struct
* @param {int} w - The width of the user interface based on chars
* @param {int} h - The height of the user interface based on chars
* @retval {Ui*} - Returns an UI pointer
*/
Ui* ui_init( int w, int h );


/**
* @brief Destroys UI struct
* @param {Ui*} ui - A pointer to the UI struct
*/
void ui_destroy( Ui* ui );


/**
* @brief Prints all buffered data inside the UI into the stdout
* @param {FILE*} stream - Buffer destination
* @param {Ui*} ui - The UI that sueld be printed
*/
void ui_draw( FILE* stream, Ui* ui );


/**
* @brief Resizes ui screen
* @param {Ui*} ui - A pointer to the UI struct
* @param {int} w - New width (cols)
* @param {int} h - New height (rows)
*/
void ui_resize( Ui *ui, int w, int h );


/**
* @brief Clears all the UI data, including inherit objects like boxes, shapes, ...
* @param {Ui*} ui - The UI that should be clered
*/
void ui_clear( Ui* ui );


/**
* @brief Fills the main ui background with a given string color
* @param {Ui*} ui - ui to fill the background
* @param {char*} frms - background format string
* @param {...} - format string arguments
*/
void ui_bg( Ui* ui, const char *frms, ... ) __attribute__ ( ( format(printf, 2, 3 ) ) );


/**
* @brief Sets a temporary format of the UI
* This means that all the text, shapes and other items will use the format
* that was setted in the last ui_frm() call
* @param {Ui*} ui - UI to set the temporary parameters
* @param {int} n - The number of parameters that will be set
* @param {int} ... - The N parameters to be set, like BG_RED, S_BOLD, ...
*/
void ui_frm( Ui* ui, int n, ... );


/**
* @brief Sets a temporary format from a given string
* This means that all the text, shapes and other items will use the format
* that was setted in the last ui_frms() call
* @param {Ui*} ui - ui to set the temporary parameters
* @param {char*} frms - format string
*/
void ui_frms( Ui* ui, const char *frms, ... ) __attribute__ ( ( format(printf, 2, 3 ) ) );


/**
* @brief Resets the temporary format of the UI to default
* @param {Ui*} ui - the UI where the temporary parameters should be resetted
*/
void ui_rs( Ui* ui );


/**
* @brief Creates a new box
* @param {Ui*} ui - UI where the box should be created
* @param {int} idx - The ID with which the box will be referenced
* @param {int} x - The x position of the box ( col of the matrix )
* @param {int} y - The y position of the box ( row of the matrix )
* @param {int} w - The width of the box ( number of cols )
* @param {int} h - The height of the box ( number of rows )
*/
void ui_new_box( Ui* ui, int idx, int x, int y, int w, int h );


/**
* @brief Changes the position of a box
* @param {Ui*} ui - UI where the box is stored
* @param {int} idx - The ID with which the box will be referenced
* @param {int} x - The new x position of the box ( col of the matrix )
* @param {int} y - The new y position of the box ( row of the matrix )
*/
void ui_box_repos( Ui *ui, int idx, int x, int y );


/**
* @brief Changes the size of a box
* @param {Ui*} ui - UI where the box is stored
* @param {int} idx - The ID with which the box will be referenced
* @param {int} w - The new width of the box ( number of cols )
* @param {int} h - The new height of the box ( number of rows )
*/
void ui_box_resize( Ui *ui, int idx, int w, int h );


/**
* @brief This functions dumps all the box data inside the Ui
* @param {Ui*} ui - The ui where data sohuld be dumped
* @param {int} id - The id of the box to be dumped
*/
void ui_dump_box( Ui *ui, int idx );


/**
* @brief Fills the main box background with a given string color
* This function does NOT clear the box buffer
* @param {Ui*} ui - UI where the box is located
* @param {int} id - The id of the box
* @param {char*} frms - background format string
* @param {...} - fromat string arguments
*/
void ui_box_bg( Ui* ui, int idx, const char *frms, ... ) __attribute__ ( ( format(printf, 3, 4 ) ) );


/**
* @brief Get the width of a box (columns)
* @param {Ui*} ui - UI where the box is located
* @param {int} idx - box index
* @retval returns the width of a box (number of columns)
*/
int ui_box_get_w( Ui* ui, int idx );


/**
* @brief Get the height of a box (rows)
* @param {Ui*} ui - UI where the box is located
* @param {int} idx - box index
* @retval returns the height of a box (number of rows)
*/
int ui_box_get_h( Ui* ui, int idx );


/**
* @brief Get the position of the cursor inside a box (column)
* @param {Ui*} ui - UI where the box is located
* @param {int} idx - box index
* @retval returns the position of the 'x' cursor (column)
*/
int ui_box_get_cx( Ui* ui, int idx );


/**
* @brief Get the position of the cursor inside a box (row)
* @param {Ui*} ui - UI where the box is located
* @param {int} idx - box index
* @retval returns the position of the 'y' cursor (row)
*/
int ui_box_get_cy( Ui* ui, int idx );

/**
* @brief Sets an offset for the 'x' cursor (column)
* When the the box is overflowed by it's width the cursor will be
* resetted to the 'x' position + 'x' offset
* @param {Ui*} ui - UI where the box is located
* @param {int} idx - box index
* @param {int} cx_off - 'x' cursor offset
*/
void ui_box_set_cx_off( Ui* ui, int idx, int cx_off );


/**
* @brief Get the position of the cursor inside a box (column & row)
* @param {Ui*} ui - UI where the box is located
* @param {int} idx - box index
* @param {int*} cx - where the 'x' cursor should be copied
* @param {int*} cy - where the 'y' cursor should be copied
*/
void ui_box_get_cursor( Ui* ui, int idx, int* cx, int* cy );


/**
* @brief Changes the cursor position of a box
* @param {Ui*} ui - UI where the box is located
* @param {int} id - The id of the box
* @param {int} x - Cursor x position ( col matrix )
* @param {int} y - Curosr y position ( row matrix )
*/
void ui_box_seek( Ui* ui, int idx, int x, int y );


/**
* @brief Sets the default format for the content of the box
* @param {Ui*} ui - UI where the box is located
* @param {int} id - The id of the box
* @param {int} n - Number of parameters
* @param {...} - Style parameters
*/
void ui_box_frm( Ui* ui, int idx, int n, ... );


/**
* @brief Sets the default format for the content of the box by a given string
* @param {Ui*} ui - ui where the box is located
* @param {int} id - the id of the box
* @param {char*} frms - format string
* @param {...} - format string arguments
*/
void ui_box_frms( Ui* ui, int idx, const char *frms, ... ) __attribute__ ( ( format(printf, 3, 4 ) ) );


/**
* @brief Clears the box buffer
* @param {Ui*} ui - UI where the box is located
* @param {int} id - The id of the box
*/
void ui_clear_box( Ui* ui, int idx );


/**
* @brief Sets the padding of a box
* @param {Ui*} ui - UI where the box is located
* @param {int} id - The id of the box
* @param {char*} pad - The padding of the box "<top> <right> <bottom> <left>"
*/
void ui_box_pad( Ui* ui, int idx, const char* pad );


/**
* @brief Updates the box buffer with a given string
* @param {Ui*} ui - UI where the box is located
* @param {int} id - The id of the box
* @param {char*} str - String format
* @param {...} - String format arguments
*/
void ui_box_put( Ui* ui, int idx, const char* str, ... ) __attribute__ ( ( format(printf, 3, 4 ) ) );

#endif
