# I3

## v0.3.1

`[IMPROVEMENTS]`
- Improved `game` module.
- Main `Game` structure is now private.
- Adapted modules to the new privatization.
- `_kill()` function now needs an argument to return an exit code.
- Improved `target` script.

`[NEW]`
- Implemented `game_get_objects()`.
- Implemented `game_get_die()`.
- Implemented `game_get_cmd()`.
- Implemented `game_get_player()`.

# I2

## v0.2.9
`[OVERALL]`
* Final release of the second iteration.

`[FIXES]`
- Minor bug fixes.
- Minor text fixes.

`[NEW]`
- Added some new code comments.

## v0.2.8
`[FIXES]`
- Fixed id conflicts.
- Fixed set bug when deleting an id with value 0.

`[IMPROVEMENTS]`
- Improved game stability.
- New map interface.
- Privatized some structures.
- Improved game frames.
- Improved game callback functions.
- Commands now show more information.
- Module `command` has been renamed to `cmd`.

 `[NEW]`
- Added two new commands `left` and `right`.
- Added space pictures.
- Added `log` module.
- Main loop now handles keyboard signals.
- Added a logger, use it with: `-l <log_name>`

## v0.2.3
`[FIXES]`
- Many bugs fixed.
- Fixed a lot of memory leaks.

`[NEW]`
- Added `ui_box_seek()`, now you can change the cursor position of a box.
- Implemented scroll boxes.
- Added `set` module and it's primitives.
- Support for multiple objects.
- Commands now handles arguments too.
- Now you can go next n cells.
- Now you can go back n cells.
- New game die.
- Added `roll` command.
- Added `dice` module.
- Added command answers.
- Now you can "take" a certain object of a cell.

`[IMPROVEMENTS]`
- Commands now shows more information
- Overview panel has been redesigned.
- Feedback panel has been redesigned.
- Improved game stability.
- Improved paint logic.
- Improved map parser.
- Improved command handling.
- Renamed command "leave" to "drop" to avoid conflicts with "left" and "right" command.

# I1
## v0.1.7.1
 `[FIXES]`
- Fixed default initialization parameters.
- Fixed an issue that caused a bad insertion of carriage returns when calling `ui_put_box()`.
- Fixed box overflowing.
- Minor `g_engine` fixes.
[IMPROVEMENTS]
- Improved ui_box_put() performance.
- If you put a string inside a box using ui_box_put() and the last char is a new line `\n`.
  the remaining chub of the line will be filled with the last remembered parameters.
- Improved UI stability such as pixels getters and setters ( avoiding overflows ).
- Fixed OVERVIEW ui box.
- Fixed FEEDBACK ui box.
- Fixed memory leaks.

 `[NEW]`
- `ui_dump_box()` dumps the data of a box inside the ui buffer ( private function by the moment ).
- `ui_box_pad()` sets the padding of a box ( internal margin ).
  the correct padding format is `<top> <right> <bottom> <left>`, for example: `1 2 1 2`.
	> NOTE: when you call this function the box buffer is cleared, so make sure to call it before any `ui_put_box()` call.

- `ui_draw()` will print a FATAL ERROR message if a pixel could not be printed.
- Removed `ui_txt_bg()`, `ui_txt_fg()`, `ui_txt_frm()`, all of them have been fusioned into `ui_frm()`.
  which can set multiple formats like color, background, ..., at the same time.
- Renamed `ui_txt_rs()` to `ui_rs()`, this function now resets temporary parameters to default.
- Added code documentation.

`[IMPROVEMENTS]`
- Game interface is now more colorful.
- Improved `newboard.dat` file.
- OVERVIEW box now shows more information about the player and the object.

`[UPCOMING]`
- Scroll-boxes.
- Shapes.
- Box decorations.

## v0.1.3

`[NEW]`
- Implemented `object` module.
- Implemented `player` module.
- A new board was introduced, with `12` cells; cells `5` and `9` have been linked together (east/west).
- Majority of functions were commented.
- The `screen` module was completely redesigned,
the name has been changed to `ui`.
- Two new keyboard inputs, `take` and `leave` were introduced, allowing players to pick up and drop objects.

`[IMPROVEMENTS]`
- `graphic_engine` has been renamed by "g_engine".
- `game` module was modified in order to use new modules.
- `g_engine` was adapted for working with the new "ui" module.
