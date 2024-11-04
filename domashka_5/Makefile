# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Target executable
TARGET = hacker-rm

# Build target
all: $(TARGET)

$(TARGET): hacker-rm.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) hacker-rm.cpp

# Clean target to remove build artifacts
clean:
	rm -f $(TARGET)

