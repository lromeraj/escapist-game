## v1.0
`[OVERALL]`
- First stable release.

# I4

## v0.4.9.1
`[IMPROVEMENTS]`
- `game_rules` module has been improved.
- Improved `ui` function prototype definitions to allow compiler to check format strings.
- `cmd_req()` now handles literal strings that are enclosed between `'` or `"`.
- Improved private function `game_add()`.
- Added help for `save`, `load`, `open` and `turn` commands.
- Light refresh for help interface.
- Improved space picture parser.
- Now you can format text style from `data.dat`.
- Increased max inventory storage to `6`.
- Updated `data.dat`.
- Improved `manager_save()`.
- Updated help.
- Inspect box has been redesigned.

`[NEW]`
- When the game is over a full screen picture will appear.
- Updated `game_loop.c` to allow the draw of the last frame before exiting.
- If you inspect the book with the book, it will not cost object uses.
- Game was renamed to `Escapist`.
- Updated `.ascii_title`.
- Updated `makefile`.
- Updated `target.conf`.
- Implemented space test bench.
- Player bag now is showed over space description.
- Implemented `book` object, you have to wear it for inspecting other objects.
- Implemented `map` object, you have to wear it for inspecting spaces.
- Now you have a use limit for the `book` object.
- Added new meetings.

`[FIXES]`
- Minor fixes.
- Fixed `ui_box_put()` bug that was using uninitialized values.

## v0.4.5
`[OVERALL]`
- Updated `ui` to version `1.1.3-stable`.

`[IMPROVEMENTS]`
- If the terminal size is not enough, an alert will appear saying that more terminal size is required.
- Renamed `ui_box_size()` to `ui_box_resize()`, and `ui_box_pos()` to `ui_box_repos()`.
- Improved function `game_callback_move()`.
- Improved `ui` format check sum.
- Improved `ui` format reset.
- Improved `ui` format copy speed.
- Improved `ui_box_bg()`.
- Improved `ui_bg()`.
- Imporoved `ui_box_draw()`.
- `ui` module now uses a cache to avoid format recomputing.
- `reader` module was renamed to `manager`.
- `reader_load()` was renamed to `manager_load()`.
- Improved `game_get_objects()`.
- Improved game adders.
- Renamed `game_create_from_file()` to `game_load_from_file()`.

`[NEW]`
- Implemented `game_rules` module.
- All game interface was redesigned using the new features of the last `ui` version.
- Now you can set the **max uses** and the initial uses of an object in the configuration file.
- Now you can **save** and **load** the progress of a game.
- To save a game use `save <file_name>`.
- To load a game use `load <file_name>`.
- Implemented private function `game_get()`.
- Introduced `save` command.
- Introduced `turn` command.
- Introduced `open` command.
- Implemented `manager_save()`.
- Introduced **torch** object.
- Now you can illuminate spaces.
- Implemented `game_callback_turn()`.
- Implemented `game_callback_open()`.
- Implemented new module `str`.
- Implemented `ui_box_set_cx_off()`.
- Implemented `ui_frms()`.
- Implemented `ui_box_get_cx()`, `ui_box_get_cy()`, `ui_box_get_w()`, `ui_box_get_h()`, `ui_box_get_cursor()`.
- Implemented new primitives for the object module,` obj_add_link()`, `obj_opens_link()`, `obj_set_attr()`, `obj_get_attr()` and `obj_get_links()`.
- Now you can set **up** and **down** links of the spaces inside configuration file.
- Updated reader module for parsing new object fields like: `_OBJ_LDESCRP`, `_OBJ_LINKS`, `_OBJ_MOVABLE`, `_OBJ_MOVED`, ... the full guide can be found inside `data.dat` file.
- Updated reader module for parsing new space fields: `_SPACE_LDESCRP` and `_SPACE_LIGHT`.
- Updated reader module for parsing game player data.
- Added new function named `game_clean()` that cleans current game data but does not destroy the game itself.
- Implemented `player_get_inventory()`.
- Implemented `set_get_ids()`.
- Implemented `obj_get_links()`.
- Implemented `game_get_links()`.
- Implemented `game_get_spaces()`.

`[FIXES]`
- Fixed an error that was causing problems when the initial object location was not defined inside configuration file (because it was by default in the player bag).

`[OTHER]`
- Overview box was removed (by the moment). Player bag will be showed in the next release.

`[PENDING]`
- Improve `manager_save()`.
- Improve `game_rules` module.
- Improve game dynamic.
- Game documentation.
- Update default `data.dat`.

## v0.4.1

`[FIXES]`
- Minor text fixes.
- `Ui` now initializes correctly all pixels.

`[IMPROVEMENTS]`
- `reader` module has been renewed.
- `reader` module now uses an other syntax to read configuration file.
- Renamed `reader_load_<item>()` by `reader_load()`, this function now needs an extra argument to know which items should be loaded from configuration file, that are: `_RD_SPACES`, `_RD_OBJS` and `_RD_LINKS` (by the moment).
- `data.dat` file now has a new visual syntax to simplify game configuration.
- `reader` module now warns (in detail) about parsing errors.
- `reader` module introduces new concept of blocks and attributes, that means, each block has it's own properties (attributes) and each property has it's own values, based on `JSON` format, but NOT recursively, that is, one property can not have another block.
- Updated object and player test-benches.
- Updated `space` module.

`[UPCOMING]`
- `C-target` written in `C` language.

## v0.4.0.1

`[NEW]`
- Updated `space` module.
- Implemented `space_set_light()`, `space_get_light()` and `space_toggle_light()`.

`[IMPROVEMENTS]`
- Improved game `reader` module, now is more robust.

# I3

## v0.3.9.9

`[OVERALL]`
- Final release of the third iteration.
- Updated `Ui` to `v1.0.0-stable`.

`[FIXES]`
- Minor bugs fixed.
- Minor text fixes.

`[IMPROVEMENTS]`
- Improved `Ui` speed.
- Improved `Ui` format parser.
- Improved game stability and reliability.

`[NEW]`
- Added new comments.
- Overview box now shows player's bag.
- Added new proceedings to the `meetings/` folder.
- Added test bench of `player`, `object`, `inventory` and `link`.

## v0.3.9.5

`[OVERALL]`
- Updated `Ui` to `v0.9.8-stable`.

`[IMPROVEMENTS]`
- Removed help box, use `help` command to see information about the commands.
- Added description of the spaces.
- Improved `set` test bench.
- Improved `Ui` speed.
- Improved `Ui` format parsing.
- `Ui` now uses less memory.
- Improved `inspect` command. Use `inspect -s` to inspect current space, and `inspect -o <name>` to inspect an object by it's name.
- Updated game help.
- Game interface now has a new fresh look.

`[NEW]`
- Created `rec_I2.goo` and `rec_I3.goo`.

`[FIXES]`
- Fixed a bug in function `set_add_id()`, it was returning `OK` when the given id was `-1`.
- Fixed `target` script bug that was not compiling after file modifications.
- Fixed a syntax error inside `.clang_complete` which was causing problems with the `linter`.
- Fixed a bug inside function `game_callback_take()`, it was ignoring the max size of the bag.

## v0.3.9.1

`[IMPROVEMENTS]`
- `target` script updated to version `1.1.0`.
- `target` script is now hundred times faster.
- `target` script now supports global/shared configuration for the environments.
- Added new option `INCDIR`, this represents the include directory.
- Created new directory `inc/`, the header files should be located in this directory.
- File `target.conf` was adapted to the new modifications.

`[FIXES]`
- Fixed `Ui` uninitialized values.
- Adapted `die_tb.c` to the new modifications.
- Adapted `set_tb.c` to the new modifications.

## v0.3.9

`[OVERVIEW]`
- Updated `Ui` module to version `0.9.5-stable`.

`[IMPROVEMENTS]`
- Improved `Ui` performance.
- `Ui` is now more stable and solid.
- `Ui` rendering is now `60% faster` than before.
- Frame is now **rendered and drawn** in approximately **`2.7 ms`** before was ~ `7-8 ms`
- Improved `ui_box_put()`, now you can add text styling in the same call.
- General improvements and adaptations in the graphic engine.

`[FIXES]`
- Fixed a bug that caused user interface problems when the user input was including special chars like `\033`.
- Fixed compiler errors and warnings when using `-ansi -pedantic` compilation flags.

`[NEW]`
- Now you can inspect spaces and objects with the `inspect` command.

`[OTHER]`
- IMPORTANT: removed wide char support in the `Ui` (by the moment).


## v0.3.8.2

`[OVERVIEW]`
- Updated `Ui` module to version `0.7.1-beta`.

`[FIXES]`
- `Ui` module now supports wide char strings, now you can print any Unicode char at the cost
of memory.
- Minor text fixes.

`[IMPROVEMENTS]`
- Improved `Ui` performance.
- `Ui` module is now more stable and solid.
- Added black background.

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
`space_get_north()`, `space_set_east()`, `space_get_east()`,
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
