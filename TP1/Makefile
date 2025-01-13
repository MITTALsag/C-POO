CXX = g++
CXXFLAGS= -std=c++17 -Wall -Wextra -Werror

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)


all : Livrable1 Livrable2 Livrable3



Livrable% : $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^


%.o : %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean :
	rm -f test_Rationnel

fclean: clean
	rm -f *.o


re : fclean all
