# Makefiles is an easy way to compile everything with the appropriate flags and library
# Compiles everything (all the headers)
all: lab2

# Uses g++ to compile with different flags
# Creates the lab2 executable
lab2:
	g++ `pkg-config --cflags opencv4` -o lab2 lab2.cpp `pkg-config --libs opencv4`

# Deletes the lab2 executable
# Useful if you want a fresh start or do not know if you have the most up to date executable
clean:
	-rm -rf lab2