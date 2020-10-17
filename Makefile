CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99
LIBFLAGS=$(shell pkg-config --libs --cflags gtk+-3.0)
LDFLAGS=-ISDL2 -ISLD2_image

EXEC=bin/ocr

HDR=$(wildcard hdr/*.h)
SRC_DIR=src
OBJ_DIR=obj

FILES=main

OBJS=$(patsubst %,$(OBJ_DIR)/%,$(FILES).o)

all: $(EXEC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(LIBFLAGS) $(LDFLAGS) -c -o $@ $<

$(EXEC): $(OBJS)
	@$(CC) $(LIBFLAGS) -g -o $@ $< $(HDR)

clean:
	@rm -f $(OBJS) $(EXEC)

.PHONY: clean