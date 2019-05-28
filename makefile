all: ctarget clean escapist

# main game
escapist: ctarget
	./ctarget -e escapist -c

# others
dist: ctarget
	./ctarget -e goose -d

clean: ctarget
	./ctarget -e escapist -cl
ctarget:
	if [ ! -e "c-target" ]; then git clone https://github.com/lromeraj/c-target; fi
	cd c-target && make ctarget && cp ctarget ../ && make clean


