#ifndef __RATIONNEL_H__
#define __RATIONNEL_H__

#include <iostream>

using namespace std;

class Rationnel
{
public :
    // Constructeur
    Rationnel();
    Rationnel(int n, int d);
    Rationnel(const Rationnel & R);


    //Accesseur
    int get_numerateur() const;
    int get_denominateur() const;


    // Affiche le rationnel sous forme numerateur / denominateur
    void afficher() const;

    // Renvoie l’approximation flottante
    double valeur_approx() const;

    //simplifie la fraction
    void simplifie();

    //operation d'addition, soustraction, multiplication et division d'un rationnel par un entier ou un autre rationnel
    void ajouter(int n);
    void ajouter(const Rationnel& autre);

    void soustraire(int n);
    void soustraire(const Rationnel& autre);

    void multiplier(int n);
    void multiplier(const Rationnel& autre);

    void diviser(int n);
    void diviser(const Rationnel& autre);


    //renvoie true si les rationnel sont égal et false sinon
    bool egale(const Rationnel& autre) const;

    // Surcharge de l'opérateur == (comparaison d'égalité)
    bool operator==(const Rationnel& autre) const;

private :
    //atribut d'un rationnel
    int  numerateur;
    int denominateur;

};



/* test des méthodes de la classe Rationnel */
bool test_valeur_approx();





#endif
