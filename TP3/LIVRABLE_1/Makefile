CXX = g++
CXXFLAGS= -g -std=c++17 -Wall -Wextra -Werror

SRC = Grille.cpp Jeu.cpp
OBJ = Grille.o Jeu.o

EXEC =  Livrable1 unit_test_Grille
all : $(EXEC)



Livrable1 : $(OBJ) Livrable1.o
	$(CXX) $(CXXFLAGS) -o $@ $^

unit_test_Grille : $(OBJ) unit_test_Grille.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o : %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f $(EXEC)

fclean: clean
	rm -f *.o


re : fclean all
