TARGET = HanoiSolver 

# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

# Directorios
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Archivos fuente y objetos
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

# Librerías y directorios de inclusión
LIBS = -lSDL2 -lSDL2_ttf
INCLUDES = -Iinclude

# Regla por defecto
all: $(BINDIR)/$(TARGET)

# Compilar y enlazar el programa
$(BINDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(OBJECTS) -o $@ $(LIBS)

# Compilar los archivos fuente
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Limpiar los archivos generados
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Phony targets
.PHONY: all clean
