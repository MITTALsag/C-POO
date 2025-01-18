#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include "Entier.hpp"

// Factorielle avec de grand entier
Entier factorial(Entier & entier) {
    if (entier.isNeg())
        throw std::invalid_argument("entier négatif dans la fonction factorielle.");

    Entier result(1);
    Entier i(1);
    while(i < entier)
    {
        result = result * i;
        i = i +1;
    }
    return result;
}


//factorielle avec un unsigned int 
Entier factorial(unsigned int n) {
    Entier result(1);
    for (unsigned int i = 2; i <= n; ++i) {
        result = result * i;
    }
    return result;
}


void runTests() {
    // Création de deux objets Entier avec des valeurs initiales
    Entier a(123412341234);
    Entier b(567856785678);

    // Tests des opérateurs arithmétiques
    Entier c = a + b; // Addition
    Entier d = a - b; // Soustraction
    Entier d2 = b - a; // Soustraction dans le sens inverse
    Entier d3 = a - a; // Soustraction nul
    Entier e = a * b; // Multiplication
    Entier g = -a;    // Opérateur unaire pour changer le signe

    // Affichage des résultats des opérations arithmétiques
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "a + b: " << c << std::endl;
    std::cout << "a - b: " << d << std::endl;
    std::cout << "b - a: " << d2 << std::endl;
    std::cout << "a - a: " << d3 << std::endl;
    std::cout << "a * b: " << e << std::endl;
    std::cout << "-a: " << g << std::endl;

    // Tests des opérateurs de comparaison
    std::cout << "a < b: " << (a < b ? "true" : "false") << std::endl;
    std::cout << "a > b: " << (a > b ? "true" : "false") << std::endl;

    // Tests des opérateurs avec des entiers
    Entier h = a + 10; // Addition avec un entier
    std::cout << "10 + a: " << h << std::endl;

    Entier i = a * 10; // Multiplication avec un entier
    std::cout << "a * 10: " << i << std::endl;

}
