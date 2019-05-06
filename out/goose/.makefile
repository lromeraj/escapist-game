TARGET = goose
SRC = ./src
OBJ = ./obj
CFILES = $(wildcard $(SRC)/*.c)
OFILES = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(CFILES))
LIBS = -lm
CFLAGS = -Wall

all: clean goose

$(TARGET): $(OFILES)
	$(CC) $(OFILES) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $(LIBS) -o $@ $^

dist:
	zip -r "goose_`date '+%Y%d%m'`.zip" ../goose/ -x "../goose/*.zip" "../goose/*.o"

clean:
	find . -type f -name '*.o' -delete
	rm -rf $(TARGET)
