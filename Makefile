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