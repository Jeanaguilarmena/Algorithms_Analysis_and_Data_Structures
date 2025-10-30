# Makefile para compilar y ejecutar main.cpp con SinglyLinkedList.hpp

CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

TARGET = main
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
