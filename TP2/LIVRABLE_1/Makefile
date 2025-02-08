CXX = g++
CXXFLAGS= -g -std=c++17 -Wall -Wextra -Werror

SRC = Expr.cpp
OBJ = Expr.o unit_test.o

EXEC =  Livrable1
all : $(EXEC)



Livrable1 : $(OBJ) Livrable1.o
	$(CXX) $(CXXFLAGS) -o $@ $^


%.o : %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f $(EXEC)

fclean: clean
	rm -f *.o


re : fclean all
