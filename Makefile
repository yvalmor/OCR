CC=gcc
CFLAGS=-Wall -Wextra -std=c99
LDFLAGS=
LIBFLAGS=$(shell pkg-config --libs --cflags gtk+-2.0)
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
HDR=
EXEC=OCR.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	@echo "Beginning compilation..."
	@$(CC) -o $@ $^ $(LDFLAGS) $(LIBFLAGS)
	@echo "Done!"

main.o: $(HDR)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS) $(LIBFLAGS)

.PHONY: clean mrproper

clean:
	@echo "Cleaning in process..."
	@rm -rf *.o
	@echo "Done!"

mrproper: clean
	@echo "Removing executable"
	@rm -rf $(EXEC)
	@echo "Done!"