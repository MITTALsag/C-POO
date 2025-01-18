CXX = g++
CXXFLAGS= -std=c++17 -Wall -Wextra -Werror

SRC = Rationnel.cpp Entier.cpp
OBJ = Rationnel.o Entier.o

EXEC = Livrable1 Livrable2 Livrable3
all : $(EXEC)



Livrable% : $(OBJ) Livrable%.o test_Livrable%.o
	$(CXX) $(CXXFLAGS) -o $@ $^


%.o : %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f $(EXEC)

fclean: clean
	rm -f *.o


re : fclean all
