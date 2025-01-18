#include <cassert>
#include "Rationnel.hpp"


//test les methode de constructeur, d'approx, de simplifie de la classe Rationnel
void test_methodes(void)
{
    // Test de la méthode afficher
    Rationnel r1(4, 6);
    std::cout << "Test afficher: ";
    r1.afficher();  // Devrait afficher "2/3"
    std::cout << std::endl;

    // Test de la méthode valeur_approx
    double approx = r1.valeur_approx();
    std::cout << "Test valeur_approx: " << approx << std::endl;  // Devrait afficher 0.666666
    assert(approx == 2.0 / 3.0); // Vérification

    // Test de la méthode simplifie
    Rationnel r2(8, -16);  // Cette fraction doit se simplifier en -1/2
    r2.simplifie();
    std::cout << "Test simplifie: ";
    r2.afficher();  // Devrait afficher "-1/2"
    std::cout << std::endl;

    // Test simplification de 10/20
    Rationnel r3(10, 20);  // Cette fraction doit se simplifier en 1/2
    r3.simplifie();
    std::cout << "Test simplifie: ";
    r3.afficher();  // Devrait afficher "1/2"
    std::cout << std::endl;
    // Test simplification de 10/20
    Rationnel r(10, -100);  // Cette fraction doit se simplifier en 1/2
    r.simplifie();
    std::cout << "Test simplifie autre : ";
    r.afficher();  // Devrait afficher "1/2"
    std::cout << std::endl;

    // Test simplification d'une fraction déjà simplifiée
    Rationnel r4(7, 13);  // Cette fraction est déjà simplifiée
    r4.simplifie();
    std::cout << "Test simplifie: ";
    r4.afficher();  // Devrait afficher "7/13"
    std::cout << std::endl;

    // Test simplification d'une fraction négative
    Rationnel r5(-9, 27);  // Cette fraction doit se simplifier en -1/3
    r5.simplifie();
    std::cout << "Test simplifie: ";
    r5.afficher();  // Devrait afficher "-1/3"
    std::cout << std::endl;

    std::cout << "Tous les tests simplifie, valeur_approx et afficher sont passés avec succès !" << std::endl;
}

// test toutes les méthodes d'operation de la classe Rationnel, y compris les opérateurs surchargés
void test_methodes_opp(void)
{
    // Test du constructeur par défaut
    Rationnel R1;
    assert(R1 == Rationnel(0,1));

    // Test du constructeur avec paramètres
    Rationnel R2(4, 6);
    assert(R2 == Rationnel(4,6));
    assert(R2 == Rationnel(2,3));

    // Test du constructeur de copie
    Rationnel R3(R2);
    assert(R3 == Rationnel(4,6));
    assert(R3 == Rationnel(2,3));


    Rationnel R4(10, -20);
    // Test de l'ajout d'un entier
    R4.ajouter(3);
    assert(R4 == Rationnel(5,2));

    // Test de l'ajout d'un autre rationnel
    R4.ajouter(Rationnel(1, 4));
    assert(R4 == Rationnel(11,4));

    // Test de l'addition via l'opérateur +
    Rationnel R5 = R4 + Rationnel(1, 4); // Ajout d'un rationnel
    assert(R5 == Rationnel(12,4)); //12/4 == 3
    assert(R4 == Rationnel(11,4)); //R4 pas modifier

    // Test de l'addition d'un entier via l'opérateur +
    Rationnel R6 = R4 + 2; // Ajout d'un entier
    assert(R6 == Rationnel(19,4));
    assert(R4 == Rationnel(11,4)); //R4 pas modifier

    // Test de la soustraction d'un entier
    R4.soustraire(2);
    assert(R4 == Rationnel(3,4));

    // Test de la soustraction d'un autre rationnel
    R4.soustraire(Rationnel(1, 8));
    assert(R4 == Rationnel(5,8));

    // Test de la soustraction via l'opérateur -
    Rationnel R7 = R4 - Rationnel(1, 8); // Soustraction d'un rationnel
    assert(R7 == Rationnel(4,8));
    assert(R7 == Rationnel(1,2));
    assert(R4 == Rationnel(5,8)); //R4 pas modifier

    // Test de la soustraction d'un entier via l'opérateur -
    Rationnel R8 = R4 - 1; // Soustraction d'un entier
    assert(R8 == Rationnel(-3,8));
    assert(R4 == Rationnel(5,8)); //R4 pas modifier

    // Test de la multiplication par un entier
    R4.multiplier(3);
    assert(R4 == Rationnel(15,8));

    // Test de la multiplication par un autre rationnel
    R4.multiplier(Rationnel(2, 5));
    assert(R4 == Rationnel(3,4));

    // Test de la multiplication via l'opérateur *
    Rationnel R9 = R4 * Rationnel(2, 5); // Multiplication d'un rationnel
    assert(R9 == Rationnel(3,10));
    assert(R4 == Rationnel(3,4)); //R4 pas modifier

    // Test de la multiplication d'un entier via l'opérateur *
    Rationnel R10 = R4 * 3; // Multiplication d'un entier
    assert(R10 == Rationnel(9,4));
    assert(R4 == Rationnel(3,4)); //R4 pas modifier

    // Test de la division par un entier
    R4.diviser(2);
    assert(R4 == Rationnel(3,8));

    // Test de la division par un autre rationnel
    R4.diviser(Rationnel(9, 20));
    assert(R4 == Rationnel(5,6));

    // Test de la division via l'opérateur /
    Rationnel R11 = R4 / Rationnel(10, 9); // Division d'un rationnel
    assert(R11 == Rationnel(3,4));
    assert(R4 == Rationnel(5,6)); //R4 pas modifier

    // Test de la division d'un entier via l'opérateur /
    Rationnel R12 = R4 / 2; // Division par un entier
    assert(R12 == Rationnel(5,12));
    assert(R4 == Rationnel(5,6)); //R4 pas modifier

    // Test de l'assignation =
    Rationnel R13(1, 2);
    R13 = R2; // Assignation d'un rationnel à un autre
    assert(R13 == Rationnel(2, 3));

    // Test de l'assignation avec simplification
    Rationnel R14(6, 9);
    R14 = R2; // Assignation avec simplification
    assert(R14 == Rationnel(2, 3));

    std::cout << "Tous les tests de surcharge d'opérateurs sont passés avec succès !" << std::endl;
}

