# Compile
all:
	g++ -I ./include src/*.cpp -o main

# Rule to remove all .o files and all executables
clean:
	- rm -f *.o
	- find . -maxdepth 1 -executable -type f \( ! -name "Makefile" \) -delete

.PHONY: clean