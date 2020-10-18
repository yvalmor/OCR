CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -rdynamic
LIBFLAGS=$(shell pkg-config --libs --cflags gtk+-3.0)
LDFLAGS=-ISDL2 -ISLD2_image

EXEC=bin/ocr

SRC_DIR=src
OBJ_DIR=obj
HDR_DIR=hdr

SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
HDR=$(wildcard $(HDR_DIR)/*.h)

all: $(EXEC)

$(EXEC): $(HDR)
	@$(CC) $(CFLAGS) $(LIBFLAGS) $(LDFLAGS) $(SRC) -o $@

clean:
	@rm -f $(OBJ) $(EXEC)

.PHONY: clean
