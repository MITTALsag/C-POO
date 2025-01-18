CXX = clang++
CXXFLAGS= -std=c++17 -Wall -Wextra -Werror -g

SRC = Rationnel.cpp Entier.cpp
OBJ = Rationnel.o Entier.o

EXEC = Livrable3
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
