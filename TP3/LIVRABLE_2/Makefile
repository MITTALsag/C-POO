CXX = g++
CXXFLAGS= -g -std=c++17 -Wall -Wextra -Werror wx-config --cxxflags
LDLIBS=wx-config --libs

SRC = Grille.cpp Jeu.cpp
OBJ = Grille.o Jeu.o

EXEC =  Livrable2
all : $(EXEC)



Livrable2 : $(OBJ) Livrable2.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o : %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f $(EXEC)

fclean: clean
	rm -f *.o


re : fclean all
