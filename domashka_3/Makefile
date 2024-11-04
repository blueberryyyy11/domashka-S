# Compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20

# Target executable
TARGET = read-file

# Source files
SRC = read-file.cpp

# Default target to build the executable
all: $(TARGET)

.PHONY: clean

$(TARGET): read-file.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) read-file.cpp

# Clean up build files
clean:
	rm -f $(TARGET)


