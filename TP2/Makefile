CXX = g++
CXXFLAGS= -std=c++17 -Wall -Wextra -Werror

SRC = Expr.cpp
OBJ = Expr.o

EXEC =  unit_test
all : $(EXEC)



test_Expr : $(OBJ) test_Expr.o
	$(CXX) $(CXXFLAGS) -o $@ $^


unit_test : $(OBJ) unit_test.o
	$(CXX) $(CXXFLAGS) -o $@ $^


%.o : %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f $(EXEC)

fclean: clean
	rm -f *.o


re : fclean all
