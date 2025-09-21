# Compilador
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Archivos fuente
SRCS = main.cpp Ordenador.cpp
# Si Algorithms.h tiene su cpp, agregarlo aquí
# SRCS = main.cpp Ordenador.cpp Algorithms.cpp

# Archivo ejecutable
TARGET = programa

# Regla por defecto
all: $(TARGET)

# Compilar ejecutable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Limpiar archivos generados
clean:
	rm -f $(TARGET) *.o
