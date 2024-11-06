# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Target executable name
TARGET = manual-append

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): manual-append.c
	$(CC) $(CFLAGS) -o $(TARGET) manual-append.c

# Clean up
clean:
	rm -f $(TARGET)

