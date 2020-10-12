CC=gcc
CFLAGS=-Wall -Wextra -std=c99
LIBFLAGS=$(shell pkg-config --libs --cflags gtk+-3.0)

SRC_DIR=src
OBJ_DIR=obj
HDR_DIR=hdr

SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
HDR=$(wildcard $(HDR_DIR)/*.h)

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
	@rm -rf $(OBJ)
	@echo "Done!"
	@echo "Removing executable"
	@rm -f $(EXEC)
	@echo "Done!"