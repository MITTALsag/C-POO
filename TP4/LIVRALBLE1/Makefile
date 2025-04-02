# Compilateur et options
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Fichiers sources et headers
SRCS = Aeroport.cpp Connexion.cpp main.cpp
HDRS = Aeroport.hpp Connexion.hpp
OBJS = $(SRCS:.cpp=.o)
TARGET = Aeroport_program

# Règle par défaut
all: $(TARGET)

# Règle de compilation principale
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Règle générique pour les fichiers objets
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle pour nettoyer
clean:
	rm -f $(OBJS) $(TARGET)

# Règle pour réinstaller
re: clean all

# Indique que ces règles ne correspondent pas à des fichiers
.PHONY: all clean re