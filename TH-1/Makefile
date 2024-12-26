CXX = g++
CXXFLAGS = -std=c++11 -O2 -pthread
TARGET = array-summary

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	rm -f $(TARGET)

