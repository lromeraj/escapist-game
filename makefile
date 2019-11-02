all: ctarget clean escapist

# main game
escapist: ctarget
	./ctarget -e escapist -c

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

space_tb:
	./ctarget -e space_tb -c

# others

dist: ctarget
	./ctarget -e goose -d

doc: ctarget
	doxygen Doxyfile

clean: ctarget
	./ctarget \
	-e escapist --clean \
	-e die_tb --clean \
	-e set_tb --clean \
	-e obj_tb --clean \
	-e player_tb --clean \
	-e link_tb --clean \
	-e inventory_tb --clean \
	-e space_tb --clean
ctarget:
	if [ ! -e "c-target" ]; then git clone https://github.com/lromeraj/c-target; fi
	cd c-target && make ctarget && cp ctarget ../ && make clean


