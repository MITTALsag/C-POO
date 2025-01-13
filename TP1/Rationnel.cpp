#include <iostream>
#include <numeric> // Pour std::gcd
#include "Rationnel.hpp"


using namespace std;


/*###############################################################*/

/*****************/
/* Constructeurs */
/*****************/


// Constructeur par defaut met 0/1 dans le rationnel
Rationnel::Rationnel()
{
    numerateur = 0;
    denominateur = 1;
}

// autre constructeur cree le rationnel n/d et simplifie la fraction
// verifie que le denominateur n'est pas 0
Rationnel::Rationnel(int n, int d) : numerateur(n), denominateur(d)
{
    if (d == 0) {
        throw invalid_argument("Le dénominateur ne peut pas être zéro.");
    }
    simplifie();
}


Rationnel::Rationnel(const Rationnel & R) :  numerateur(R.numerateur), denominateur(R.denominateur) {}

/*###############################################################*/

//Accesseurs
int Rationnel::get_numerateur() const
{
    return numerateur;
}

int Rationnel::get_denominateur() const
{
    return denominateur;
}


// Affiche le rationnel sous forme numerateur / denominateur
void Rationnel::afficher() const
{
    cout << numerateur << "/" << denominateur << endl;
}

// Renvoie l’approximation flottante
double Rationnel::valeur_approx() const
{
    return static_cast<double>(numerateur) / static_cast<double>(denominateur);
}

//simplifie la fraction
void Rationnel::simplifie()
{
    //recupere le pgcd du numerateur et du denominateur
    //et simplifier le numerateur et le denominateur par le pgcd
    int pgcd = gcd(numerateur, denominateur);
    numerateur /= pgcd;
    denominateur /= pgcd;
    if (denominateur < 0) { // Garder un dénominateur positif
        numerateur = -numerateur;
        denominateur = -denominateur;
    }
}


//operation d'addition, soustraction, multiplication et division d'un rationnel par un entier ou un autre rationnel
void Rationnel::ajouter(int n)
{
    numerateur = n * denominateur + numerateur;
    simplifie();
}

void Rationnel::ajouter(const Rationnel& autre)
{
    //recuperer le numerateur n et le denominateur d de autre
    //puis utiliser la formule d'addition classique
    int num_autre = autre.numerateur;
    int denum_autre = autre.denominateur;
    numerateur = (numerateur * denum_autre) + (num_autre * denominateur);
    denominateur *= denum_autre;
    simplifie();

}

void Rationnel::soustraire(int n)
{
    ajouter(-n);
}

void Rationnel::soustraire(const Rationnel& autre)
{
    //recuperer le numerateur n et le denominateur d de autre
    //puis creer un nouveau rationnel R = -autre et faire l'addition de R a l'objet
    int num_autre = autre.numerateur;
    int denum_autre = autre.denominateur;

    ajouter(Rationnel(-num_autre, denum_autre));
}

void Rationnel::multiplier(int n)
{
    numerateur *= n;
    simplifie();
}

void Rationnel::multiplier(const Rationnel& autre)
{
    //recuperer le numerateur n et le denominateur d de autre
    //puis utiliser la formule de multiplication classique
    int num_autre = autre.numerateur;
    int denum_autre = autre.denominateur;
    numerateur *= num_autre;
    denominateur *= denum_autre;
    simplifie();
}

void Rationnel::diviser(int n)
{
    if (n == 0)
    {
        throw invalid_argument("Le dénominateur ne peut pas être zéro.");
    }
    denominateur *= n;
    simplifie();
}

void Rationnel::diviser(const Rationnel& autre)
{
    //recuperer le numerateur n et le denominateur d de autre
    //puis utiliser la formule de division classique
    int num_autre = autre.numerateur;
    int denum_autre = autre.denominateur;
    numerateur *= denum_autre;
    denominateur *= num_autre;
    simplifie();
}


bool Rationnel::egale(const Rationnel& autre) const
{
    return (numerateur * autre.denominateur) == (denominateur * autre.numerateur);
}

// Surcharge de l'opérateur ==
bool Rationnel::operator==(const Rationnel& autre) const {
    return egale(autre);
}















