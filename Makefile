CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -pedantic -Werror
LIBFLAGS=$(shell pkg-config --libs --cflags gtk+-2.0)

SRC=%.c src/
OBJ=$(SRC:.c=.o) obj/
HDR=

EXEC=bin/ocr.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	@echo "Beginning compilation..."
	@$(CC) -o $@ $^ $(LIBFLAGS)
	@echo "Done!"

main.o: $(HDR)

/%.o: $(SRC)/%.c
	@$(CC) -o $@ -c $< $(CFLAGS) $(LIBFLAGS)

.PHONY: clean

clean:
	@echo "Cleaning in process..."
	@rm -rf *.o
	@echo "Done!"
	@echo "Removing executable"
	@rm -f $(EXEC)
	@echo "Done!"