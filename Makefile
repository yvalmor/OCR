CC=gcc
CFLAGS=-Wall -Wextra -std=c99
LIBFLAGS=$(pkg-config --libs --cflags gtk+-2.0)
EXEC=OCR.exe

all: ocr

ocr: main.c
	@echo "Beginning compilation..."
	@$(CC) $(LIBFLAGS) main.c -o $(EXEC) $(CFLAGS)
	@echo "Done!"

clean:
	@echo "Cleaning in process..."
	@rm -rf *.o
	@echo "Done!"

mrproper: clean
	@echo "Removing executable"
	@rm -rf $(EXEC)
	@echo "Done!"