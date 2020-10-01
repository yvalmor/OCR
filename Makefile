CC=gcc
CFLAGS=$(shell pkg-config --libs --cflags gtk+-2.0) -Wall -Wextra -std=c99
LDFLAGS=$
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
HDR=
EXEC=OCR.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	@echo "Beginning compilation..."
	@$(CC) $(LIBFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Done!"

main.o: $(HDR)

%.o: %.c
	@$(CC) $(LIBFLAGS) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@echo "Cleaning in process..."
	@rm -rf *.o
	@echo "Done!"

mrproper: clean
	@echo "Removing executable"
	@rm -rf $(EXEC)
	@echo "Done!"