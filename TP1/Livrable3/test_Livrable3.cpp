#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include "Entier.hpp"
#include "Rationnel.hpp"
using namespace std;

// Factorielle avec de grand entier
Entier factorial(Entier & entier) {
    if (entier.isNeg())
        throw std::invalid_argument("entier négatif dans la fonction factorielle.");

    Entier result(1);
    Entier i(1);
    while(i < entier || i == entier)
    {
        result = result * i;
        i = i +1;
    }
    return result;
}


//factorielle avec un unsigned int 
uint64_t factorial(uint64_t n) {
    uint64_t result = 1;
    for (uint64_t i = 2; i <= n; ++i) {
        result = result * i;
    }
    return result;
}

// Fonction pour tester la classe Entier
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
    Entier f = a / b; // Division
    Entier f2 = Entier(12345) / Entier(123); // Division 2
    Entier f3 = b / a; // Division 3
    Entier f4 = a / a; // Division 4
    std::string g = a.divideReal(b); //Divion Réel
    Entier h = -a;    // Opérateur unaire pour changer le signe

    // Affichage des résultats des opérations arithmétiques
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "a + b: " << c << std::endl;
    std::cout << "a - b: " << d << std::endl;
    std::cout << "b - a: " << d2 << std::endl;
    std::cout << "a - a: " << d3 << std::endl;
    std::cout << "a * b: " << e << std::endl;
    std::cout << "a / b: " << f << std::endl;
    std::cout << "12345 / 123: " << f2 << std::endl;
    std::cout << "b / a: " << f3 << std::endl;
    std::cout << "a / a: " << f4 << std::endl;
    std::cout << "a / b (réel): " << g << std::endl;
    std::cout << "-a: " << h << std::endl;

    // Tests des opérateurs de comparaison
    std::cout << "a < b: " << (a < b ? "true" : "false") << std::endl;
    std::cout << "a > b: " << (a > b ? "true" : "false") << std::endl;

    // Tests des opérateurs avec des entiers
    Entier i = a + 10; // Addition avec un entier
    std::cout << "10 + a: " << i << std::endl;

    Entier j = a - 10; // Soustraction avec un entier
    std::cout << "10 - a: " << i << std::endl;

    Entier k = a * 10; // Multiplication avec un entier
    std::cout << "a * 10: " << k << std::endl;

    Entier l = a / 1000000; // Division avec un entier
    std::cout << "a / 1000000: " << l << std::endl;
    
    std::string m = a.divideReal(1000000); // Division avec un entier
    std::cout << "a / 1000000 (réel): " << m << std::endl;
    
    // Tests de l'opérateur %
    Entier remainder = a % b;
    std::cout << "a % b: " << remainder << std::endl;

    Entier remainder2 = a % 1000000;
    std::cout << "a % 1000000: " << remainder2 << std::endl;

    // Tests du PGCD
    Entier gcdResult = a.gcd_Entier(b);
    std::cout << "PGCD(a, b): " << gcdResult << std::endl;

    Entier gcdResult2 = a.gcd_Entier(1000000);
    std::cout << "PGCD(a, 1000000): " << gcdResult2 << std::endl;

}




//Calcul Un comme définit dans le sujet en Rationnel
Rationnel suite_Un_Rationnel(unsigned int n, bool print)
{

    // Initialisation des premières valeurs de la suite u_n
    Rationnel u0(3,2);  // u0 = 3/2
    Rationnel u1(5,3);  // u1 = 5/3

    Rationnel un = u0;  // Initialisation de u_n
    Rationnel un1 = u1; // Initialisation de u_(n+1)
    Rationnel un2;

    if (n==0)
    {
        if (print)
        {
            cout << "U0 = " << u0.valeur_approx() << " = ";;
            u0.afficher();
        }
        return u0;
    }
    else if (n==1)
    {
        if (print)
        {
            cout << "U0 = " << u0.valeur_approx() << " = ";;
            u0.afficher();
            cout << "U1 = " << u1.valeur_approx() << " = ";;
            u1.afficher();
        }
        return u1;
    }


    if (print)
    {
        cout << "U0 = " << u0.valeur_approx() << " = ";;
        u0.afficher();
        cout << "U1 = " << u1.valeur_approx() << " = ";;
        u1.afficher();
    }

    unsigned int i;
    // Calcul des termes de la suite u_n jusqu'à n
    for (i = 2; i <= n; i++) {
        // Calcul de un+2 selon la formule donnée
        un2 = 2003 - (6002 / un1) + (4000 / (un*un1));

        // Mise à jour des valeurs
        un = un1;
        un1 = un2;


        if (print)
        {
            cout << "U" << i << " = " << un2.valeur_approx() << " = ";
            un2.afficher();
        }
    }
    return un1;
}




//Calcul Vn comme définit dans le sujet en Rationnel
Rationnel suite_Vn_Rationnel(unsigned int n, double a, bool print)
{

    Rationnel v0(1, 1);  // v0 = 1

    if (n==0)
    {
        if (print)
        {
            cout << "V0 = " << v0.valeur_approx() << " = ";;
            v0.afficher();
        }
        return v0;
    }

    if (print)
    {
        cout << "V0 = " << v0.valeur_approx() << " = ";;
        v0.afficher();
    }

    // Calcul de la suite v
    Rationnel vn = v0; // v0
    Rationnel vn1; //vn+1

    unsigned int i;
    // Calcul des termes de la suite u_n jusqu'à n
    for (i = 2; i <= n; i++) {
        // Calcul de vn+1 selon la formule donnée
        vn1 = (vn / 2) + (a/(vn*2));

        // Mise à jour des valeurs
        vn = vn1;

        if (print)
        {
            cout << "V" << i << " = " << vn1.valeur_approx() << " = ";
            vn1.afficher();
        }
    }
    return vn;

}
