CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -pedantic -Werror
LIBFLAGS=$(shell pkg-config --libs --cflags gtk+-2.0)

SRC=src/$(wildcard *.c)
OBJ=$(SRC:.c=.o)
OBJ_DIR=obj
HDR=

EXEC=bin/ocr.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	@echo "Beginning compilation..."
	@$(CC) -o $@ $^ $(LIBFLAGS)
	@echo "Done!"

main.o: $(HDR)

$(OBJ_DIR)/%.o: $(SRC)/%.c
	@$(CC) -o $@ -c $< $(CFLAGS) $(LIBFLAGS)

.PHONY: clean

clean:
	@echo "Cleaning in process..."
	@rm -f $(OBJ)/*.o
	@echo "Done!"
	@echo "Removing executable"
	@rm -f $(EXEC)
	@echo "Done!"