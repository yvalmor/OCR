CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -rdynamic
LIBFLAGS=$(shell pkg-config --libs --cflags gtk+-3.0)
LDFLAGS=-ISDL2 -ISDL2_image

HDR=$(wildcard hdr/*.h)
OBJ=obj
SRC=src

EXEC=bin/ocr.exe

all: $(EXEC)

$(EXEC): $(OBJ) $(HDR)
	@echo "Beginning compilation..."
	@$(CC) $(LIBFLAGS) $(LDFLAGS) -o $@ $^
	@echo "Done!"

$(OBJ)/%.o: $(SRC)/%.c
	@echo "Generation object files"
	@$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	@echo "Cleaning in process..."
	@echo "Removing object files..."
	@rm -rf $(OBJ)
	@echo "Object files removed!"
	@echo "Removing executable..."
	@rm -f $(EXEC)
	@echo "Executable removed!"
	@echo "Cleaning finished!"
  