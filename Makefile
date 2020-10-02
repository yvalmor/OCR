CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -pedantic -Werror
LIBFLAGS=$(shell pkg-config --libs --cflags gtk+-2.0)

SRC_DIR=src
OBJ_DIR=obj

SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
HDR=

EXEC=bin/ocr.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	@echo "Beginning compilation..."
	@$(CC) -o $@ $^ $(LIBFLAGS)
	@echo "Done!"

$(OBJ_DIR)/main.o: $(HDR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) -o $@ -c $< $(CFLAGS) $(LIBFLAGS)

.PHONY: clean

clean:
	@echo "Cleaning in process..."
	@rm -rf $(OBJS)
	@echo "Done!"
	@echo "Removing executable"
	@rm -f $(EXEC)
	@echo "Done!"