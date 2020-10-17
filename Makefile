CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -rdynamic
LIBFLAGS=$(shell pkg-config --libs --cflags gtk+-3.0)
LDFLAGS=-ISDL2 -ISDL2_image

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
	@$(CC) -o $@ $^ $(LIBFLAGS) $(LDFLAGS)
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
  