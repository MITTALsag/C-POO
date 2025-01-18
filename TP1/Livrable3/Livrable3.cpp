#include <iostream>
#include "Entier.hpp"
#include "test_Livrable3.hpp"


int main(void)
{
    runTests();
    Entier ent = (12);
    Entier E = factorial(ent);
    std::cout << E << std::endl;

}