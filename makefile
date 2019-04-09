all: clean goose die_tb set_tb obj_tb player_tb link_tb


# main game
goose:
	./target -e goose -c


# testbenchs

die_tb:
	./target -e die_tb -c

set_tb:
	./target -e set_tb -c

obj_tb:
	./target -e obj_tb -c

player_tb:
	./target -e player_tb -c

link_tb:
	./target -e link_tb -c

inventory_tb:
	./target -e inventory_tb -c


# others

dist:
	./target -e goose -d

doc:
	doxygen Doxyfile

clean:
	./target \
	-e goose --clean \
	-e die_tb --clean \
	-e set_tb --clean \
	-e obj_tb --clean \
	-e player_tb --clean \
	-e link_tb --clean \
	-e inventory_tb --clean
