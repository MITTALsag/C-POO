CXX = g++
CXXFLAGS= -g -std=c++17 -Wall -Wextra -Werror

SRC = Expr_poly.cpp
OBJ = Expr_poly.o unit_test.o

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
