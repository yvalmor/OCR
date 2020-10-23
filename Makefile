CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -rdynamic
LIBFLAGS=$(shell pkg-config --libs --cflags gtk+-3.0)
LDFLAGS=-I"include" -L"lib" -lSDL2 

EXEC=bin/ocr

SRC_DIR=src
OBJ_DIR=obj
HDR_DIR=hdr

SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
HDR=$(wildcard $(HDR_DIR)/*.h)

all: $(EXEC)

$(EXEC): $(HDR)
	@mkdir -p bin
	@$(CC) $(CFLAGS) $(LIBFLAGS) $(LDFLAGS) $(SRC) -o $@

.PHONY: clean

clean:
	@rm -f $(OBJ) $(EXEC) $(wildcard bin/*)