#ifndef __RATIONNEL_HPP__
#define __RATIONNEL_HPP__

#include <iostream>
#include "Entier.hpp"

using namespace std;

class Rationnel
{
public :
    // Constructeur
    Rationnel();
    Rationnel(Entier n, Entier d);
    Rationnel(const Rationnel & R);


    //Accesseur
    Entier get_numerateur() const;
    Entier get_denominateur() const;


    // Affiche le rationnel sous forme numerateur / denominateur
    void afficher() const;

    // Renvoie l’approximation flottante
    string valeur_approx() const;

    //simplifie la fraction
    void simplifie();

    //operation d'addition, soustraction, multiplication et division d'un rationnel par un entier ou un autre rationnel

    void ajouter(int n);
    void ajouter(const Rationnel& autre);
    //surcharge de l'operateur + pour ajouter un rationnel et un entier
    Rationnel operator+(int n) const;
    //surcharge de l'operateur + pour ajouter deux rationnel
    Rationnel operator+(const Rationnel& autre) const;
    //surcharge de l'operateur + pour ajouter un rationnel et un entier mais ou l'entier est l'opérande de gauche
    friend Rationnel operator+(int n, const Rationnel & autre);

    void soustraire(int n);
    void soustraire(const Rationnel& autre);
    //surcharge de l'operateur - pour soustraire un rationnel et un entier
    Rationnel operator-(int n) const;
    //surcharge de l'operateur - pour soustraire deux rationnel
    Rationnel operator-(const Rationnel& autre) const;
    //surcharge de l'operateur - pour soustraire un rationnel et un entier mais ou l'entier est l'opérande de gauche
    friend Rationnel operator-(int n, const Rationnel & autre);

    void multiplier(int n);
    void multiplier(const Rationnel& autre);
    //surcharge de l'operateur * pour multiplier un rationnel et un entier
    Rationnel operator*(int n) const;
    //surcharge de l'operateur * pour multiplier deux rationnel
    Rationnel operator*(const Rationnel& autre) const;
    //surcharge de l'operateur * pour multiplier un rationnel et un entier mais ou l'entier est l'opérande de gauche
    friend Rationnel operator*(int n, const Rationnel & autre);

    void diviser(int n);
    void diviser(const Rationnel& autre);
    //surcharge de l'operateur / pour diviser un rationnel et un entier
    Rationnel operator/(int n) const;
    //surcharge de l'operateur / pour diviser deux rationnel
    Rationnel operator/(const Rationnel& autre) const;
    //surcharge de l'operateur / pour diviser un rationnel et un entier mais ou l'entier est l'opérande de gauche
    friend Rationnel operator/(int n, const Rationnel & autre);


    //renvoie true si les rationnel sont égal et false sinon
    bool egale(const Rationnel& autre) const;

    // Surcharge de l'opérateur == (comparaison d'égalité)
    bool operator==(const Rationnel& autre) const;

    //surcharge de l'operateur d'affctation
    Rationnel& operator=(const Rationnel& autre);


private :
    //atribut d'un rationnel
    Entier  numerateur;
    Entier denominateur;

};


#endif
