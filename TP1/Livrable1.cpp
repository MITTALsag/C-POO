#include <iostream>
#include <cassert>
#include "Rationnel.hpp"

int main() {
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
    
    // Test du constructeur par défaut
    Rationnel R1;
    assert(R1.get_numerateur() == 0 && R1.get_denominateur() == 1);

    // Test du constructeur avec paramètres
    Rationnel R2(4, 6);
    assert(R2.get_numerateur() == 2 && R2.get_denominateur() == 3);

    // Test du constructeur de copie
    Rationnel R3(R2);
    assert(R3.get_numerateur() == 2 && R3.get_denominateur() == 3);


    Rationnel R4(10, -20);
    // Test de l'ajout d'un entier
    R4.ajouter(3);
    assert(R4.get_numerateur() == 5 && R4.get_denominateur() == 2);
    assert(R4.egale(Rationnel (5,2)));
    assert(R4 == (Rationnel (5,2)));


    // Test de l'ajout d'un autre rationnel
    R4.ajouter(Rationnel(1, 4));
    assert(R4.get_numerateur() == 11 && R4.get_denominateur() == 4);
    assert(R4.egale(Rationnel (11,4)));
    assert(R4 == (Rationnel (11,4)));


    // Test de la soustraction d'un entier
    R4.soustraire(2);
    assert(R4.get_numerateur() == 3 && R4.get_denominateur() == 4);
    assert(R4.egale(Rationnel (3,4)));
    assert(R4 == (Rationnel (3,4)));


    // Test de la soustraction d'un autre rationnel
    R4.soustraire(Rationnel(1, 8));
    assert(R4.get_numerateur() == 5 && R4.get_denominateur() == 8);
    assert(R4.egale(Rationnel (5,8)));
    assert(R4 == (Rationnel (5,8)));


    // Test de la multiplication par un entier
    R4.multiplier(3);
    assert(R4.get_numerateur() == 15 && R4.get_denominateur() == 8);
    assert(R4.egale(Rationnel (15,8)));
    assert(R4 == (Rationnel (15,8)));
    assert(R4 == (Rationnel (30,16))); //toujours egale car * 2


    // Test de la multiplication par un autre rationnel
    R4.multiplier(Rationnel(2, 5));
    assert(R4.get_numerateur() == 3 && R4.get_denominateur() == 4);
    assert(R4.egale(Rationnel (3,4)));
    assert(R4 == (Rationnel (3,4)));
    assert(R4 == (Rationnel (-3,-4))); //toujours egale car * -1


    // Test de la division par un entier
    R4.diviser(2);
    assert(R4.get_numerateur() == 3 && R4.get_denominateur() == 8);
    assert(R4.egale(Rationnel (3,8)));
    assert(R4 == (Rationnel (3,8)));
    assert(R4 == (Rationnel (30,80))); //toujours egale car *10


    // Test de la division par un autre rationnel
    R4.diviser(Rationnel(3, 8));
    assert(R4.get_numerateur() == 1 && R4.get_denominateur() == 1);
    assert(R4.egale(Rationnel (1,1)));
    assert(R4.egale(Rationnel (1,1)));
    assert(R4.egale(Rationnel (120,120))); //toujours egale car 120/120 =1
    




    // Test de l'égalité
    Rationnel R5(1, 1);
    assert(R4.egale(R5));

    std::cout << "Tous les tests sont passés avec succès !" << std::endl;
    return 0;
}
