#ifndef __LIVRABLE3_HPP__
#define __LIVRABLE3_HPP__
#include "Entier.hpp"
#include "Rationnel.hpp"


Entier factorial(Entier & entier);

uint64_t factorial(uint64_t n);

void runTests();

Rationnel suite_Un_Rationnel(unsigned int n, bool print);
Rationnel suite_Vn_Rationnel(unsigned int n, double a, bool print);


#endif