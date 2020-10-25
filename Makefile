CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -rdynamic
LIBFLAGS=$(shell pkg-config --libs --cflags gtk+-3.0)
LDFLAGS=-I"include" -L"lib" -lSDL2

XORCFLAGS=-Wall -Wextra -Werror -std=c99
XORLIBFLAGS=
XORLDFLAGS=-lm

BIN_DIR=bin
EXEC_OCR=ocr
EXEC_XOR=xor

SRC_DIR=src
OBJ_DIR=obj
HDR_DIR=hdr

XOR=$(SRC_DIR)/network.c
XOR_OBJ=$(OBJ_DIR)/network.o

SRC=$(filter-out $(XOR), wildcard $(SRC_DIR)/*.c)
OBJ=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
HDR=$(wildcard $(HDR_DIR)/*.h)

all: $(EXEC_OCR) $(EXEC_XOR)

$(EXEC_OCR): $(HDR)
	@mkdir -p bin
	@$(CC) $(CFLAGS) $(LIBFLAGS) $(LDFLAGS) $(SRC) -o ($(BIN_DIR)/$@)

$(EXEC_XOR): $(XOR_OBJ)

$(XOR_OBJ): $(HDR)
	@(CC) $(XORCFLAGS) -g -c $(XOR) -o $(OBJ_DIR)/network.o

.PHONY: clean

clean:
	@rm -f $(OBJ) $(EXEC) $(wildcard bin/*)