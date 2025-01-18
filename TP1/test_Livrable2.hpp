#ifndef __LIVRABLE2_HPP__
#define __LIVRABLE2_HPP__

#include "Rationnel.hpp"

//Calcul Un comme définit dans le sujet
double suite_Un(unsigned int n, bool print);


//Calcul Vn comme définit dans le sujet
double suite_Vn(unsigned int n, double a, bool print);


//Calcul Un comme définit dans le sujet en Rationnel
Rationnel suite_Un_Rationnel(unsigned int n, bool print);

//Calcul Vn comme définit dans le sujet en Rationnel
Rationnel suite_Vn_Rationnel(unsigned int n, double a, bool print);

#endif
