# I3

## v0.3.8

`[FIXES]`
- Fixed segmentation fault when `space_parser()` was trying to use a null pointer,
specifically when working with the string that contains the drawing of the space.
- Fixed a bug in the function `cmd_req()` that was preventing a correct input parsing.
If the string was not ending with the char `\n` the parser was ignoring null char `\0`.
- Fixed an `Ui` bug that caused a false filling of boxes when using other Ui's at the same time.

`[IMPROVEMENTS]`
- Added new authors to the header.
- Reordered code inside the file `game.c`.
- Improved `Reader` module functions.
- Improved function `g_engine_paint_game()`.
- Improved function `parse_space()`.
- Game screen has been redesigned.
- Removed blue background.
- File `data.dat` has been adapted to the new features.

`[NEW]`
- Implemented `Link` module.
- Implemented new `Game` getters like `game_get_link_by_id()`, `game_get_links()`, ...
- Implemented new `Game` adder `game_add_link()`.
- Implemented new `Reader` function `reader_load_links()`.
- Implemented new `Space` functions, `space_set_link()`, `space_get_link()`.
- The following primitives have been removed from `Space` module: `space_set_north()`,
`space_get_north()`, `space_set_east()`, `space_get_east()`, `space_set_east()`,
`space_get_south()`, `space_set_south()`, `space_set_west()` and `space_get_west()`.
The use of that functions has been simplified to `space_set_link()` and `space_get_link()`. To specify the cardinal point where the link
should be set or gotten, you have to pass an extra argument.
- Now you can use file records. That files stores commands of a previous game.
Use it with `target -e goose -c -r < rec1.goo`.
- Added objects description, `obj_set_descrp()` and `obj_get_descrp()`.
- New help user interface.
- Added `help` command, now you can see more information about the commands.

`[UPCOMING]`
- Data file generator.
- Reader improvements.
- `inspect` command.

## v0.3.5

`[OVERVIEW]`
- No visible memory leaks by the moment.

`[FIXES]`
- Fixed a bug in function `set_has_id()` it was returning `true` when the given id was `-1`.

`[IMPROVEMENTS]`
- Improved functions responsible of taking and dropping objects.
- Improved game stability.
- Improved file `data.dat`.
- Overview now shows more information about the objects and the player.

`[NEW]`
- Implemented inventory module.
- The player can wear more than one object at a time.
- Added more code documentation.
- Implemented new `Game` getters like `game_get_object_by_name()`, `game_get_object_by_idx()`.
- `game_get_object()` has been renamed to `game_get_object_by_id()`.
- Now you can take or drop objects by it's name or it's id.
To `take|drop` an object by it's id use `take|drop -i <id>`, by name use `take|drop -n <name>` or just `take|drop <name>`.

## v0.3.1

`[IMPROVEMENTS]`
- Improved `Game` module.
- Main `Game` structure is now private.
- Adapted modules to the new privatization.
- `_kill()` function now needs an argument to return an exit code.
- Improved `target` script.

`[NEW]`
- Implemented `game_get_objects()`.
- Implemented `game_get_die()`.
- Implemented `game_get_cmd()`.
- Implemented `game_get_player()`.
- Added code documentation.

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
