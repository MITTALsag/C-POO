#include <iostream>
#include <numeric> // Pour std::gcd
#include "Rationnel.hpp"

using namespace std;


/*###############################################################*/
/*****************/
/* Constructeurs */
/*****************/

/*
* Constructeur par défaut :
* Initialise un rationnel avec le numérateur à 0 et le dénominateur à 1
*/
Rationnel::Rationnel()
{
    numerateur = 0;
    denominateur = 1;
}

/*
* Constructeur avec paramètres :
* Initialise un rationnel avec le numérateur 'n' et le dénominateur 'd', 
* et simplifie la fraction.
* Vérifie que le dénominateur n'est pas 0 avant l'initialisation.
*/
Rationnel::Rationnel(int n, int d) : numerateur(n), denominateur(d)
{
    if (d == 0) {
        throw invalid_argument("Le dénominateur ne peut pas être zéro.");
    }
    simplifie();
}

/*
* Constructeur de copie :
* Initialise un rationnel en copiant les valeurs d'un autre rationnel 'R'
*/
Rationnel::Rationnel(const Rationnel & R) :  numerateur(R.numerateur), denominateur(R.denominateur) {}

/*###############################################################*/
/*************************/
/* Accesseurs (Getters) */
/*************************/

/*
* Accesseur pour obtenir le numérateur du rationnel
* Renvoie le numérateur
*/
int Rationnel::get_numerateur() const
{
    return numerateur;
}

/*
* Accesseur pour obtenir le dénominateur du rationnel
* Renvoie le dénominateur
*/
int Rationnel::get_denominateur() const
{
    return denominateur;
}

/*###############################################################*/
/************************/
/* Méthodes d'affichage */
/************************/

/*
* Affiche le rationnel sous forme numérateur/denominateur
*/
void Rationnel::afficher() const
{
    cout << numerateur << "/" << denominateur << endl;
}



/*###############################################################*/
/************************/
/* Méthodes utilitaires */
/************************/


/*
* Simplifie la fraction en divisant le numérateur et le dénominateur par leur PGCD
* Garantit que le dénominateur soit positif
*/
void Rationnel::simplifie()
{
    // Récupère le PGCD du numérateur et du dénominateur
    int pgcd = gcd(numerateur, denominateur);
    numerateur /= pgcd;
    denominateur /= pgcd;
    if (denominateur < 0) { // Garder un dénominateur positif
        numerateur = -numerateur;
        denominateur = -denominateur;
    }
}

/*
* Renvoie l'approximation flottante du rationnel
* Divise le numérateur par le dénominateur et renvoie le résultat en tant que double
*/
double Rationnel::valeur_approx() const
{
    return static_cast<double>(numerateur) / static_cast<double>(denominateur);
}

/*###############################################################*/
/**********************/
/* Opérations de base */
/**********************/

/*
* Méthode pour ajouter un entier 'n' au rationnel
* Utilise la formule a/b + n = (a + b * n) / b
*/
void Rationnel::ajouter(int n)
{
    numerateur = n * denominateur + numerateur;
    simplifie();
}

/*
* Méthode pour ajouter un autre rationnel 'autre' au rationnel courant
* Utilise la formule (a/b + c/d) = (a * d + b * c) / (b * d)
*/
void Rationnel::ajouter(const Rationnel& autre)
{
    // Récupère le numérateur et le dénominateur du rationnel 'autre'
    int num_autre = autre.numerateur;
    int denum_autre = autre.denominateur;
    numerateur = (numerateur * denum_autre) + (num_autre * denominateur);
    denominateur *= denum_autre;
    simplifie();
}



/*
* Méthode pour soustraire un entier 'n' au rationnel
* Utilise la methode ajouter en transformant n en -n
*/
void Rationnel::soustraire(int n)
{
    ajouter(-n);
}

/*
* Méthode pour soustraire un autre Rationnel
* Crée un Rationnel négatif de l'autre et effectue l'addition
*/
void Rationnel::soustraire(const Rationnel& autre)
{
    // Récupère le numérateur et le dénominateur de l'autre Rationnel
    int num_autre = autre.numerateur;
    int denum_autre = autre.denominateur;
    // Ajouter le Rationnel négatif de l'autre
    ajouter(Rationnel(-num_autre, denum_autre));
}


/*
* Méthode pour multiplier un Rationnel par un entier
*/
void Rationnel::multiplier(int n)
{
    numerateur *= n;
    simplifie();
}

/*
* Méthode pour multiplier un Rationnel par un autre Rationnel
*/
void Rationnel::multiplier(const Rationnel& autre)
{
    numerateur *= autre.numerateur;
    denominateur *= autre.denominateur;
    simplifie();
}

/*
* Méthode pour diviser un Rationnel par un entier
*/
void Rationnel::diviser(int n)
{
    if (n == 0)
    {
        throw invalid_argument("Le dénominateur ne peut pas être zéro.");
    }
    denominateur *= n;
    simplifie();
}

/*
* Méthode pour diviser un Rationnel par un autre Rationnel
* Recuperer le numerateur n et le denominateur d de autre
* puis utiliser la formule de division classique
*/
void Rationnel::diviser(const Rationnel& autre)
{
    
    int num_autre = autre.numerateur;
    int denum_autre = autre.denominateur;
    numerateur *= denum_autre;
    denominateur *= num_autre;
    simplifie();
}


/*###############################################################*/
/**************************************/
/* Surcharge des opérateur +, -, *, / */
/**************************************/

//surcharge de l'operateur + pour ajouter un rationnel et un entier
Rationnel Rationnel::operator+(int n) const
{
    Rationnel R = *this;    //R = la partie gauche de l'opération
    R.ajouter(n);           //modification de R pour lui ajouter l'entier n
    return R;
}

//surcharge de l'operateur + pour ajouter deux rationnel
Rationnel Rationnel::operator+(const Rationnel& autre) const
{
    Rationnel R = *this;    //R = la partie gauche de l'opération
    R.ajouter(autre);       //modification de R pour lui ajouter le rationnel autre
    return R;
}

//surcharge de l'operateur + pour ajouter un rationnel et un entier mais ou l'entier est l'opérande de gauche
Rationnel operator+(int n, const Rationnel & autre)
{
    return autre + n; // = n + autre (comutatif)
}


//surcharge de l'operateur - pour soustraire un rationnel et un entier
Rationnel Rationnel::operator-(int n) const
{
    Rationnel R = *this;    //R = la partie gauche de l'opération
    R.soustraire(n);        //modification de R pour lui soustraire l'entier n
    return R;
}

//surcharge de l'operateur - pour soustraire deux rationnel
Rationnel Rationnel::operator-(const Rationnel& autre) const
{
    Rationnel R = *this;    //R = la partie gauche de l'opération
    R.soustraire(autre);    //modification de R pour lui soustraire le rationnel autre
    return R;
}

//surcharge de l'operateur - pour soustraire un rationnel et un entier mais ou l'entier est l'opérande de gauche
Rationnel operator-(int n, const Rationnel & autre)
{
    return Rationnel(n,1) - autre; //car pas comutatif
}



//surcharge de l'operateur * pour multiplier un rationnel et un entier
Rationnel Rationnel::operator*(int n) const
{
    Rationnel R = *this;    //R = la partie gauche de l'opération
    R.multiplier(n);        //modifie de R pour lui multiplier l'entier n
    return R;
}

//surcharge de l'operateur * pour multiplier deux rationnel
Rationnel Rationnel::operator*(const Rationnel& autre) const
{
    Rationnel R = *this;    //R = la partie gauche de l'opération
    R.multiplier(autre);    //modifie de R pour lui multiplier le rationnel autre
    return R;
}

//surcharge de l'operateur * pour multiplier un rationnel et un entier mais ou l'entier est l'opérande de gauche
Rationnel operator*(int n, const Rationnel & autre)
{
    return autre * n; // = n * autre (comutatif)
}


//surcharge de l'operateur / pour diviser un rationnel et un entier
Rationnel Rationnel::operator/(int n) const
{
    if (n == 0) {
        throw std::invalid_argument("Division par zéro.");
    }
    Rationnel R = *this;    //R = la partie gauche de l'opération
    R.diviser(n);           //modifie de R pour lui diviser l'entier n
    return R;
}

//surcharge de l'operateur / pour diviser deux rationnel
Rationnel Rationnel::operator/(const Rationnel& autre) const
{
    if (autre.numerateur == 0) {
            throw std::invalid_argument("Division par zéro.");
        }
    Rationnel R = *this;    //R = la partie gauche de l'opération
    R.diviser(autre);       //modifie de R pour lui diviser le rationnel autre
    return R;
}
//surcharge de l'operateur / pour diviser un rationnel et un entier mais ou l'entier est l'opérande de gauche
Rationnel operator/(int n, const Rationnel & autre)
{
    if (n == 0)
        return Rationnel();

    return Rationnel(n,1) / autre; //car pas comutatif
}
/*###############################################################*/
/*****************/
/* Comparaison */
/*****************/

/*
* Vérifie si un rationnel est égal à un autre
* Utilise la formule a/b == c/d si et seulement si a * d == b * c
*/
bool Rationnel::egale(const Rationnel& autre) const
{
    return (numerateur * autre.denominateur) == (denominateur * autre.numerateur);
}

/*
* Surcharge de l'opérateur == pour comparer deux rationnels
*/
bool Rationnel::operator==(const Rationnel& autre) const {
    return egale(autre);
}

//surcharge de l'operateur d'affctation
Rationnel& Rationnel::operator=(const Rationnel& autre)
{
    if (this != &autre)  // Vérification pour éviter l'auto-affectation
    {
        numerateur = autre.numerateur;
        denominateur = autre.denominateur;
        simplifie(); // Simplification après l'affectation
    }
    return *this;
}


