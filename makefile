all: clean goose set_tb die_tb

goose:
	./target -e goose -c

die_tb:
	./target -e die_tb -c

set_tb:
	./target -e set_tb -c

link_tb:
	./target -e link_tb -c

inventory_tb:
	./target -e inventory_tb -c

dist:
	./target -e goose -d

docs:
	doxygen Doxyfile

clean:
	./target \
	-e goose --clean \
	-e die_tb --clean \
	-e set_tb --clean \
	-e link_tb --clean \
	-e inventory_tb --clean
