CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++17
TARGET = interactive-shell

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	rm -f $(TARGET)

