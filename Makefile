CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -rdynamic -lm -O3
LIBFLAGS=$(shell pkg-config --libs --cflags gtk+-3.0)
LDFLAGS=-I"include" -L"lib" -lSDL2 -ljson-c

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

SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
HDR=$(wildcard $(HDR_DIR)/*.h)

all: $(EXEC_OCR)

$(EXEC_OCR): $(HDR)
	@mkdir -p bin
	@$(CC) $(CFLAGS) $(LIBFLAGS) $(LDFLAGS) $(SRC) -o $(BIN_DIR)/$@

.PHONY: clean

clean:
	@rm -rf $(OBJ) $(wildcard $(BIN_DIR)/*)
