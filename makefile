all: clean goose set_tb die_tb

goose:
	./target -e goose -c

die_tb:
	./target -e die_tb -c

set_tb:
	./target -e set_tb -c

dist:
	./target -e goose -d

clean:
	./target -e goose --clean -e die_tb --clean -e set_tb --clean
