# Makefiles is an easy way to compile everything with the appropriate flags and library
# Compiles everything (all the headers)
all: lab2

# Uses gcc to compile with different flags
# Creates the lab2 executable
lab2:
	gcc -Wall -std=gnu99 -g -o lab2 lab2.c

# Deletes the lab2 executable
# Useful if you want a fresh start or do not know if you have the most up to date executable
clean:
	-rm -rf lab2