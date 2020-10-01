CC=gcc
CFLAGS=-Wall -Wextra -std=c99
LIBFLAGS=(pkg-config --libs --cflags gtk+-2.0)
EXEC=OCR.exe

all:
	@echo "Beginning compilation..."
	@echo "Done!"

clean:
	@echo "Cleaning in process..."
	@rm -rf *.o
	@echo "Done!"

mrproper: clean
	@echo "Removing executable"
	@echo "Done!"