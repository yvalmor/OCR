CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -pedantic -Werror
LIBFLAGS=$(shell pkg-config --libs --cflags gtk+-2.0)

SRC=src/$(wildcard *.c)
OBJ=obj/$(SRC:.c=.o)
HDR=src/$(wildcard *.h)

EXEC=bin/ocr.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	@echo "Beginning compilation..."
	@$(CC) -o $@ $^ $(LDFLAGS) $(LIBFLAGS)
	@echo "Done!"

main.o: $(HDR)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS) $(LIBFLAGS)

.PHONY: clean

clean:
	@echo "Cleaning in process..."
	@rm -rf *.o
	@echo "Done!"
	@echo "Removing executable"
	@rm -rf $(EXEC)
	@echo "Done!"