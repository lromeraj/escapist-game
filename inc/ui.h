/**
* @brief User interface based on chars
*
* @file ui.h
* @author Javier Romera
* @version 1.0.0-stable
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
* @brief Clears all the UI data, including inherit objects like boxes, shapes, ...
* @param {Ui*} ui - The UI that should be clered
*/
void ui_clear( Ui* ui );


/**
* @brief Fills the main UI background with a given color
* @param {Ui*} ui - UI to be filled
* @param {Color} c - The color with which the background will be filled
*/
void ui_bg( Ui* ui, Color c );


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
* @brief Resets the temporary format of the UI to default
* @param {Ui*} ui - the UI where the temporary parameters should be resetted
*/
void ui_rs( Ui* ui );


/**
* @brief Creates a new box
* @param {Ui*} ui - UI where the box should be created
* @param {int} id - The ID with which the box will be referenced
* @param {int} x - The x position of the box ( col of the matrix )
* @param {int} y - The y position of the box ( row of the matrix )
* @param {int} w - The width of the box ( number of cols )
* @param {int} h - The height of the box ( number of rows )
*/
void ui_new_box( Ui* ui, int idx, int x, int y, int w, int h );


/**
* @brief This functions dumps all the box data inside the Ui
* @param {Ui*} ui - The ui where data sohuld be dumped
* @param {int} id - The id of the box to be dumped
*/
void ui_dump_box( Ui *ui, int idx );


/**
* @brief Fills the main box background with a given color
* This function does NOT clear the box buffer
* @param {Ui*} ui - UI where the box is located
* @param {int} id - The id of the box
* @param {Color} c - The color with which the background will be filled
*/
void ui_box_bg( Ui* ui, int idx, Color c );


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
void ui_box_put( Ui* ui, int idx, const char* str, ... );

#endif
