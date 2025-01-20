#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <algorithm>
#include "Entier.hpp"

using namespace std;

/*###############################################################*/
/*####################### CONSTRUCTEURS #########################*/
/*###############################################################*/
#pragma region CONSTRUCTEURS

/*
* Constructeur par défaut :
* Initialise un entier avec la valeur 0
*/
Entier::Entier() : isNegative(false) {
    digits.push_back(0); // Ajoute le chiffre 0 au vecteur de chiffres
}

/*
* Constructeur prenant un int64_t :
* Initialise un entier avec la valeur donnée
*/
Entier::Entier(int64_t value) {
    if (value < 0) {
        isNegative = true; // Si la valeur est négative, marque l'entier comme négatif
        value = -value; // Convertit la valeur en positif pour le traitement
    } else {
        isNegative = false; // Sinon, marque l'entier comme positif
    }

    do {
        digits.push_back(value % 10); // Ajoute le dernier chiffre de la valeur au vecteur
        value /= 10; // Supprime le dernier chiffre de la valeur
    } while (value > 0); // Continue jusqu'à ce que la valeur soit 0
}
#pragma endregion


/*###############################################################*/
/*##################### MÉTHODES UTILITAIRES #####################*/
/*###############################################################*/
#pragma region MÉTHODES UTILITAIRES

/*
* Méthode pour normaliser le vecteur de chiffres
* Enlève tous les 0 non utilisés
*/
void Entier::normalize() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back(); // Supprime les 0 non utilisés à la fin du vecteur
    }
    if (digits.size() == 0) //pour qu'il y ait au moins un 0 dans digits
        digits.push_back(0);

    if (digits.size() == 1 && digits[0] == 0) {
        isNegative = false; // Si l'entier est 0, il n'est pas négatif
    }
}

bool Entier::isNeg() const//retourne vrais si l'entier est négatif
{
    return this->isNegative;
}


Entier Entier::abs() const {
    Entier result = *this;
    result.isNegative = false;
    return result;
}
#pragma endregion


/*###############################################################*/
/*############### OPÉRATIONS DE COMPARAISON #####################*/
/*###############################################################*/
#pragma region OPÉRATIONS DE COMPARAISON

/*
* opération de inferieur ou égal entre deux Entier
*/
bool Entier::operator<=(const Entier& other) const {
    // Si les signes sont différents
    if (isNegative != other.isNegative) {
        // Si this est négatif (isNegative = true) et other est positif, this est plus petit --> renvoie bien true
        // Si this est positif (isNegative = false) et other est negatif, this est plus grand --> renvoie bien false
        return isNegative; 
    }

    // Compare les tailles des vecteurs 'digits'
    if (this->digits.size() != other.digits.size())
        if (isNegative) //les deux sont negatif
            return this->digits.size() > other.digits.size(); //retourne vrais si this est plus grand --> plus petit en prenant en compte les signe
        else //les deux sont positif --> retourne vrais si this est plus petit que other
            return this->digits.size() < other.digits.size(); // Si 'this' a moins de chiffres, il est plus petit
     else {
        // Si les tailles sont égales, compare les chiffres un par un de gauche à droite
        for (size_t i = this->digits.size(); i > 0; --i) {
            if (this->digits[i - 1] < other.digits[i - 1]) 
                return true; // Si un chiffre de 'this' est plus petir, 'this' est plus petir

            if (this->digits[i - 1] > other.digits[i - 1])
                return false; // Si un chiffre de 'other' est plus petit, 'this' n'est pas plus petit

        }
        
        return true; //si on sort de la boucle (dans le else) --> les deux Entier sont égaux

    }
    // Si on se retrouve ici, il y a un souci
    throw std::logic_error("Vous ne devriez pas vous trouver ici.");

}

/*
* opération de superieur strict entre deux Entier
*/
bool Entier::operator>(const Entier& other) const {
    return !(*this <= other); //car non(>) = (<=)
}

/*
* opération de inferieur strict entre deux Entier
*/
bool Entier::operator<(const Entier& other) const {
    // Si les signes sont différents
    if (isNegative != other.isNegative) {
        // Si this est négatif (isNegative = true) et other est positif, this est plus petit --> renvoie bien true
        // Si this est positif (isNegative = false) et other est negatif, this est plus grand --> renvoie bien false
        return isNegative; 
    }

    // Compare les tailles des vecteurs 'digits'
    if (this->digits.size() != other.digits.size())
        if (isNegative) //les deux sont negatif
            return this->digits.size() > other.digits.size(); //retourne vrais si this est plus grand --> plus petit en prenant en compte les signe
        else //les deux sont positif --> retourne vrais si this est plus petit que other
            return this->digits.size() < other.digits.size(); // Si 'this' a moins de chiffres, il est plus petit
     else {
        // Si les tailles sont égales, compare les chiffres un par un de gauche à droite
        for (size_t i = this->digits.size(); i > 0; --i) {
            if (this->digits[i - 1] < other.digits[i - 1]) 
                return true; // Si un chiffre de 'this' est plus petir, 'this' est plus petir

            if (this->digits[i - 1] > other.digits[i - 1])
                return false; // Si un chiffre de 'other' est plus petit, 'this' n'est pas plus petit

        }
        return false; //si on sort de la boucle (dans le else) --> les deux Entier sont égaux donc retourner false

    }
    // Si on se retrouve ici, il y a un souci
    throw std::logic_error("Vous ne devriez pas vous trouver ici.");


}

/*
* opération de superieur ou égal entre deux Entier
*/
bool Entier::operator>=(const Entier& other) const {
    return !(*this < other); //car non(>=) = (<)
}

/*
* Operateur d'egalité
*/
bool Entier::operator==(const Entier& other) const {
    // Si les signes sont différents ou la taille des tableau ne sont pas égal
    if ((isNegative != other.isNegative) || (this->digits.size() != other.digits.size())) {
        return false; 
    }

    for (size_t i = 0;  i < this->digits.size(); i++) {
            if (this->digits[i] != other.digits[i]) 
                return false; // Si un chiffre de 'this' != de un chiffre de other
        }
        
    return true; //si tout les chiffre sont égaux
}


/*
* Operateur d'egalité
*/
bool Entier::operator==(const uint64_t n) const {
    Entier other = n;
    return *this == other;
}

/*
* Operateur de non egalité
*/
bool Entier::operator!=(const Entier& other) const {
    return !(*this == other);
}


/*
* Operateur de non egalité
*/
bool Entier::operator!=(const uint64_t n) const {
        return !(*this == n);

}

#pragma endregion



/*###############################################################*/
/*###################### OPÉRATIONS DE BASE #####################*/
/*###############################################################*/
#pragma region OPÉRATIONS DE BASE

/*
* Opérateur d'addition pour deux entiers
*/
Entier Entier::operator+(const Entier& other) const {
    Entier result;
    result.digits.clear(); // Initialise le vecteur de chiffres de la résultante

    // Taille maximale entre this->digits et other.digits
    size_t maxSize = std::max(this->digits.size(), other.digits.size());

    // Gestion du signe de this et other
    if (isNegative && other.isNegative) // Si les deux opérandes sont négatives
        result.isNegative = true;
    else if (!isNegative && !other.isNegative) // Si les deux opérandes sont positives
        result.isNegative = false;
    else // Si elles ne sont pas du même signe
    {
        if (isNegative) // Si l'opérande de gauche est négative et l'opérande de droite positive
        {
            return other - (-*this);
        }
        else // Si l'opérande de droite est négative et l'opérande de gauche positive
            return *this - (-other);
    }

    uint8_t carry = 0; // Initialise la retenue
    // Boucle pour additionner chaque chiffre
    for(size_t i=0 ; i<maxSize ; i++) {

        uint8_t sum = carry; // Initialise la somme avec la retenue
        if (i < digits.size()) sum += digits[i]; // Ajoute le chiffre courant si disponible
        if (i < other.digits.size()) sum += other.digits[i]; // Ajoute le chiffre de l'autre entier si disponible

        result.digits.push_back(sum % 10); // Ajoute le dernier chiffre de la somme au vecteur de la résultante
        carry = sum / 10; // Met à jour la retenue
    }
    if (carry != 0)
        result.digits.push_back(carry);

    result.normalize(); // Normalise le vecteur de chiffres de la résultante
    return result; // Retourne la résultante
}

/*
* Opérateur d'addition pour un entier et un uint64_t
*/
Entier Entier::operator+(const uint64_t n) const {
    return *this + Entier(n); // Utilise l'opérateur d'addition pour deux entiers
}

/*
* Opérateur de soustraction pour deux entiers
*/
Entier Entier::operator-(const Entier& other) const {
    Entier result;
    result.digits.clear(); // Initialise le vecteur de chiffres de la résultante

    // Gestion du signe de this et other
    if (*this < other){
        result = other - *this;
        result.isNegative = true;
        return result;
    }
    else if (*this > other)
        result.isNegative = false;
    else
    {
        result.normalize();
        return result;
    }

    // Taille maximale entre this->digits et other.digits
    size_t maxSize = std::max(this->digits.size(), other.digits.size());

    uint8_t borrow = 0; // Initialise la retenue
    // Boucle pour soustraire chaque chiffre
    for (size_t i = 0; i < maxSize; ++i) {
        int8_t diff = this->digits[i] - borrow; // Initialise la différence avec la retenue
        if (i < other.digits.size()) diff -= other.digits[i]; // Soustrait le chiffre de l'autre entier si disponible

        if (diff < 0) {
            diff += 10; // Emprunte 10 si la différence est négative
            borrow = 1; // Met à jour la retenue
        } else {
            borrow = 0; // Réinitialise la retenue
        }

        result.digits.push_back(diff); // Ajoute le dernier chiffre de la différence au vecteur de la résultante
    }

    result.normalize(); // Normalise le vecteur de chiffres de la résultante
    return result; // Retourne la résultante
}


/*
* Opérateur de soustraction pour un entier et un uint64_t
*/
Entier Entier::operator-(const uint64_t n) const {
    return *this - Entier(n); // Utilise l'opérateur de soustraction pour deux entiers
}

/*
* Opérateur pour changer le signe de l'entier
*/
Entier Entier::operator-() const {
    Entier result = *this; // Copie l'entier courant
    result.isNegative = !result.isNegative; // Inverse le signe
    return result; // Retourne la résultante
}

/*
* Opérateur de multiplication pour deux entiers
*/
Entier Entier::operator*(const Entier& other) const {
    Entier result;
    result.digits.clear(); // Initialise le vecteur de chiffres de la résultante

    // Gestion du signe de this et other
    result.isNegative = (isNegative != other.isNegative); // Le résultat est négatif si les signes sont différents

    // Taille maximale entre this->digits et other.digits
    size_t maxSize = this->digits.size() + other.digits.size();
    std::vector<uint8_t> temp(maxSize, 0); // Vecteur temporaire pour accumuler les résultats intermédiaires

    // Boucle pour multiplier chaque chiffre
    for (size_t i = 0; i < this->digits.size(); ++i) {
        int carry = 0; // Initialise la retenue
        for (size_t j = 0; j < other.digits.size(); ++j) {
            int prod = this->digits[i] * other.digits[j] + carry + temp[i + j]; // Calcule le produit
            temp[i + j] = prod % 10; // Met à jour le chiffre dans le vecteur temporaire
            carry = prod / 10; // Met à jour la retenue
        }
        if (carry > 0) {
            temp[i + other.digits.size()] = carry; // Ajoute la retenue finale au vecteur temporaire
        }
    }

    // Copie les résultats intermédiaires dans result.digits
    result.digits = temp;

    result.normalize(); // Normalise le vecteur de chiffres de la résultante
    return result; // Retourne la résultante
}

/*
* Opérateur de multiplication pour un entier et un uint64_t
*/
Entier Entier::operator*(const uint64_t n) const {
    return *this * Entier(n); // Utilise l'opérateur de multiplication pour deux entiers
}

/*
*Operation de division entiere par un Entier
*/
Entier Entier::operator/(const Entier& other) const {
    // Vérifie si le diviseur est zéro et lève une exception si c'est le cas
    if (other.digits.empty() || (other.digits.size() == 1 && other.digits[0] == 0)) {
        throw std::runtime_error("Division by zero");
    }

    // Initialise le résultat
    Entier result;
    result.digits.clear();
    result.isNegative = (isNegative != other.isNegative); // Détermine le signe du résultat

    // Copie le dividende et le diviseur en ignorant leurs signes
    Entier dividend(*this);
    dividend.isNegative = false;
    Entier divisor(other);
    divisor.isNegative = false;

    // Initialise le quotient
    Entier quotient;
    quotient.digits.clear();
    quotient.isNegative = false;

    // Boucle de division
    while (dividend >= divisor) {
        dividend = dividend - divisor; // Soustrait le diviseur du dividende
        quotient = quotient + 1; // Incrémente le quotient
    }

    // Assigne les chiffres du quotient au résultat
    result.digits = quotient.digits;
    result.normalize(); // Normalise le résultat
    return result; // Retourne le résultat
}

/*
*Operation de division entiere par un int
*/
Entier Entier::operator/(const uint64_t n) const {
    // Vérifie si le diviseur est zéro et lève une exception si c'est le cas
    if (n == 0) {
        throw std::runtime_error("Division by zero");
    }

    return *this / Entier(n);
}

Entier Entier::operator%(const Entier& other) const
{
    if (other.digits.empty() || (other.digits.size() == 1 && other.digits[0] == 0)) {
        throw std::invalid_argument("Division by zero");
    }

    Entier quotient = *this / other;
    Entier remainder = *this - (quotient * other);

    remainder.isNegative = isNegative; // Conserver le signe du dividende
    remainder.normalize();

    return remainder;
}

Entier Entier::operator%(const uint64_t n) const
{
    return *this % Entier(n);
}

std::string Entier::divideReal(const Entier& other) const {
    if (other.digits.empty() || (other.digits.size() == 1 && other.digits[0] == 0)) {
        throw std::invalid_argument("Division by zero");
    }

    Entier quotient = *this / other;
    Entier remainder = *this - (quotient * other); // == *this % other

    std::string result = quotient.toString();

    if (!remainder.digits.empty()) {
        result += ".";
        remainder = remainder.abs();
        Entier divisor = other.abs();

        std::vector<uint8_t> fractionalPart;
        for (int i = 0; i < 10; ++i) { // Limite à 10 chiffres après la virgule
            remainder = remainder * 10;
            Entier digit = remainder / divisor;
            fractionalPart.push_back(digit.digits[0]);
            remainder = remainder - (digit * divisor); // == remainder % divisor
        }

        for (auto it = fractionalPart.begin(); it != fractionalPart.end(); ++it) {
            result += static_cast<char>(*it + '0');
        }
    }

    return result;
}

// Fonction pour trouver le PGCD
Entier Entier::gcd_Entier(const Entier& other) const {
    Entier a = *this;
    Entier b = other;

    while (b != Entier(0)) {
        Entier temp = b;
        b = a % b;
        a = temp;
    }

    return a.abs();
}

#pragma endregion


/*###############################################################*/
/*#################### MÉTHODES D'AFFICHAGE #####################*/
/*###############################################################*/
#pragma region MÉTHODES AFFICHAGE

/*
* Méthode pour convertir l'entier en chaîne de caractères
*/
string Entier::toString() const {
    string result;
    for (int i = digits.size() - 1; i >= 0; --i) {
        result += '0' + digits[i]; // Convertit chaque chiffre en caractère et l'ajoute à la chaîne
    }
    if (isNegative) {
        result = '-' + result; // Ajoute le signe négatif si nécessaire
    }
    return result; // Retourne la chaîne de caractères
}

/*
* Opérateur de flux de sortie
*/
ostream& operator<<(ostream& os, const Entier& entier) {
    os << entier.toString(); // Utilise la méthode toString pour convertir l'entier en chaîne de caractères
    return os; // Retourne le flux de sortie
}

#pragma endregion
