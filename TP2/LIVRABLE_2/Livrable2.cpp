#include <iostream>
#include "unit_test.hpp"

/* Fonction main pour exécuter les tests */
int main() {
    // Exécution des tests

    test_affiche();
    test_simplifie_Cst();

    std::cout << std::endl;
    std::cout << "Test du sujet : " << std::endl;
    test_sujet();

    

    return 0;
}
