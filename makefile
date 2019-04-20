all: ctarget clean goose die_tb set_tb obj_tb player_tb link_tb inventory_tb reader_tb

# main game
goose: ctarget
	./ctarget -e goose -c

# testbenchs
die_tb: ctarget
	./ctarget -e die_tb -c

set_tb: ctarget
	./ctarget -e set_tb -c

obj_tb: ctarget
	./ctarget -e obj_tb -c

player_tb: ctarget
	./ctarget -e player_tb -c

link_tb: ctarget
	./ctarget -e link_tb -c

inventory_tb: ctarget
	./ctarget -e inventory_tb -c

reader_tb: ctarget
	./ctarget -e reader_tb -c

# others

dist: ctarget
	./ctarget -e goose -d

doc: ctarget
	doxygen Doxyfile

clean: ctarget
	./ctarget \
	-e goose --clean \
	-e die_tb --clean \
	-e set_tb --clean \
	-e obj_tb --clean \
	-e player_tb --clean \
	-e link_tb --clean \
	-e inventory_tb --clean \
	-e reader_tb --clean

ctarget:
	gcc -I c-target/inc -c c-target/src/str.c -o c-target/obj/str.o
	gcc -I c-target/inc -c c-target/src/stack.c -o c-target/obj/stack.o
	gcc -I c-target/inc -c c-target/src/target.c -o c-target/obj/target.o
	gcc -I c-target/inc -c c-target/src/ui.c -o c-target/obj/ui.o
	gcc c-target/obj/ui.o c-target/obj/str.o c-target/obj/stack.o c-target/obj/target.o -o ctarget
