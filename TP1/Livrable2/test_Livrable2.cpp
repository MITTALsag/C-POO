#include <iostream>
#include "Rationnel.hpp"
using namespace std;

//Calcul Un comme définit dans le sujet
// si print est true alors affiche Un pour tout n
//cout en O(n)
double suite_Un(unsigned int n, bool print)
{
    // Initialisation des premières valeurs de la suite u_n
    double u0 = 3.0 / 2.0;  // u0 = 3/2
    double u1 = 5.0 / 3.0;  // u1 = 5/3

    double un = u0;  // Initialisation de u_n
    double un1 = u1; // Initialisation de u_(n+1)
    double un2;

    if (n==0)
    {
        if (print)
            cout << "U0 = " << u0 << endl;
        return u0;
    }
    else if (n==1)
    {
        if (print)
        {
            cout << "U0 = " << u0 << endl;
            cout << "U1 = " << u1 << endl;
        }
        return u1;
    }


    if (print)
    {
        cout << "U0 = " << u0 << endl;
        cout << "U1 = " << u1 << endl;
    }

    unsigned int i;
    // Calcul des termes de la suite u_n jusqu'à n
    for (i = 2; i <= n; i++) {
        // Calcul de un+2 selon la formule donnée
        un2 = 2003.0 - (6002.0 / un1) + (4000.0 / (un * un1));

        // Mise à jour des valeurs
        un = un1;
        un1 = un2;

        if (print)
            cout << "U" << i << " = " << un2 << endl;
    }
    return un2;
}


//Calcul Vn comme définit dans le sujet
// si print est true alors affiche Vn pour tout n
//Cout en O(n)
double suite_Vn(unsigned int n, double a, bool print)
{
    // Initialisation de v0
    double v0 = 1.0;  // v0 = 1
    double vn = v0;
    double vn1;

    if (n==0)
    {
        if (print)
            cout << "V0 = " << v0 << endl;
        return v0;
    }

    if (print)
        cout << "V0 = " << v0 << endl;

    unsigned int i;
    // Calcul des termes de la suite v_n jusqu'à n
    for (i = 1; i <= n; i++) {
        // Calcul de vn+1 selon la formule donnée
        vn1 = (vn / 2.0) + (a / (2.0 * vn));

        // Mise à jour de vn
        vn = vn1;


        if (print)
            cout << "V" << i << " = " << vn1 << endl;
    }
    return vn1;
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
