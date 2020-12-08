CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -rdynamic
LIBFLAGS=$(shell pkg-config --libs --cflags gtk+-3.0)
LDFLAGS=-I"include" -L"lib" -lSDL2

XOR_CFLAGS=-Wall -Wextra -Werror -std=c99
XOR_LDFLAGS=-lm

BIN_DIR=bin
EXEC_OCR=ocr
EXEC_XOR=xor

SRC_DIR=src
OBJ_DIR=obj
HDR_DIR=hdr

XOR=$(SRC_DIR)/network.c
XOR_OBJ=$(OBJ_DIR)/network.o

SRC=$(filter-out $(XOR) src/json.c, $(wildcard $(SRC_DIR)/*.c))
OBJ=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
HDR=$(wildcard $(HDR_DIR)/*.h)

all: $(EXEC_OCR) $(EXEC_XOR)

$(EXEC_OCR): $(HDR)
	@mkdir -p bin
	@$(CC) $(CFLAGS) $(LIBFLAGS) $(LDFLAGS) $(SRC) -g -o $(BIN_DIR)/$@

$(EXEC_XOR):
	@mkdir -p bin
	@$(CC) -g -lm -Wall -Wextra -std=c99 src/network.c -o $(BIN_DIR)/$@

.PHONY: clean

clean:
	@rm -rf $(OBJ) $(XOR_OBJ) $(wildcard $(BIN_DIR)/*)
