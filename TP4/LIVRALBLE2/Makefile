# Compilateur et options
CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -Wextra -I.

# Fichiers sources et headers
SRCS = Aeroport.cpp Connexion.cpp main.cpp
HDRS = Aeroport.hpp Connexion.hpp Graphe.hpp
OBJS = $(SRCS:.cpp=.o)
TARGET = aeroport_program

# Règle par défaut
all: $(TARGET)

# Règle de compilation principale
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Règle spéciale pour Graphe.cpp (template)
Graphe.o: Graphe.cpp Graphe.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle générique pour les autres fichiers objets
%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle pour nettoyer
clean:
	rm -f $(OBJS) $(TARGET)

# Règle pour réinstaller
re: clean all

# Règles factices
.PHONY: all clean re