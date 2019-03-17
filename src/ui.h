/**
 * @brief User interface based on chars
 *
 * @file ui.h
 * @author Javier Romera
 * @version 0.6.1
 * @date 17/03/2019
 * @copyright GNU Public License
 */

#ifndef UI_H
#define UI_H

#define MAX_BOXES 10 /*!< Maximum number of boxes */

/*!
* @brief Text colors
*/
typedef enum {
  BG_BLACK=40,
  BG_RED=41,
  BG_GREEN=42,
  BG_YELLOW=43,
  BG_BLUE=44,
  BG_PURPLE=45,
  BG_CYAN=46,
  BG_WHITE=47,
  FG_BLACK=30,
  FG_RED=31,
  FG_GREEN=32,
  FG_YELLOW=33,
  FG_BLUE=34,
  FG_PURPLE=35,
  FG_CYAN=36,
  FG_WHITE=37
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
typedef struct _Ui_box Ui_box;
typedef struct _Ui Ui;


/** Initializes UI struct
* @param {int} w - The width of the user interface based on chars
* @param {int} h - The height of the user interface based on chars
* @retval {Ui*} - Returns an UI pointer
*/
Ui* ui_init( int w, int h );


/** Destroys UI struct
* @param {Ui*} ui - A pointer to the UI struct
*/
void ui_destroy( Ui* ui );


/** Prints all buffered data inside the UI into the stdout
* @param {Ui*} ui - The UI that sueld be printed
*/
void ui_draw( Ui* ui );


/** Clears all the UI data, including inherit objects like boxes, shapes, ...
* @param {Ui*} ui - The UI that should be clered
*/
void ui_clear( Ui* ui );


/** Fills the main UI background with a given color
* @param {Ui*} ui - UI to be filled
* @param {Color} c - The color with which the background will be filled
*/
void ui_bg( Ui* ui, Color c );


/** Sets a temporary format of the UI
* This means that all the text, shapes and other items will use the format
* that was setted in the last ui_frm() call
* @param {Ui*} ui - UI to set the temporary parameters
* @param {int} n - The number of parameters that will be set
* @param {int} ... - The N parameters to be set, like BG_RED, S_BOLD, ...
*/
void ui_frm( Ui* ui, int n, ... );


/** Resets the temporary format of the UI to default
* @param {Ui*} ui - the UI where the temporary parameters should be resetted
*/
void ui_rs( Ui* ui );


/** Creates a new box
* @param {Ui*} ui - UI where the box should be used
* @param {int} id - The ID with which the box will be referenced
* @param {int} x - The x position of the box ( col of the matrix )
* @param {int} y - The y position of the box ( row of the matrix )
* @param {int} w - The width of the box ( number of cols )
* @param {int} h - The height of the box ( number of rows )
*/
void ui_new_box( Ui* ui, int id, int x, int y, int w, int h );


/** Fills the main box background with a given color
* This function does NOT clear the box buffer
* @param {Ui*} ui - UI where the box is located
* @param {int} id - The id of the box
* @param {Color} c - The color with which the background will be filled
*/
void ui_box_bg( Ui* ui, int id , Color c );


/** Changes the cursor position of a box
* @param {Ui*} ui - UI where the box is located
* @param {int} id - The id of the box
* @param {int} x - Cursor x position ( col matrix )
* @param {int} y - Curosr y position ( row matrix )
*/
void ui_box_seek( Ui* ui, int id, int x, int y );


/** Clears the box buffer
* @param {Ui*} ui - UI where the box is located
* @param {int} id - The id of the box
*/
void ui_clear_box( Ui* ui, int id );


/** Sets the padding of a box
* @param {Ui*} ui - UI where the box is located
* @param {int} id - The id of the box
* @param {char*} pad - The padding of the box "<top> <right> <bottom> <left>"
*/
void ui_box_pad( Ui* ui, int id, const char* pad );


/** Updates the box buffer with a given string
* @param {Ui*} ui - UI where the box is located
* @param {int} id - The id of the box
* @param {char*} str - String format
* @param {...} - String format arguments
*/
void ui_box_put( Ui* ui, int id, const char* str, ... );

#endif
