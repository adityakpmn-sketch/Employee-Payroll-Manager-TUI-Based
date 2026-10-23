# Compiler and flags
CC = gcc
DFLAGS = -Wall -Wextra -std=c99 $(CFLAGS)
CFLAGS = -lm

# Name of your final executable program
TARGET = Payroll

# Source files
SRC = main.c

# Default rule (runs when you just type 'make')
all: $(TARGET)

run: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -w -o $(TARGET) && ./$(TARGET)

debug:
	$(CC) $(DFLAGS) $(SRC) -o $(TARGET)

# Rule to build the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# If you are using ncurses, use this line instead for the compile rule:
#	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lncurses

# Clean up built files (runs when you type 'make clean')
clean:
	rm -f $(TARGET)
