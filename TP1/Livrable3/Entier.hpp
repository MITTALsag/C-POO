#ifndef __ENTIER_HPP__
#define __ENTIER_HPP__

#include <iostream>
#include <vector>
#include <cstdint>
#include <string>

class Entier {
private:
    std::vector<uint8_t> digits; // Vecteur pour stocker les chiffres de l'entier
    bool isNegative; // Indicateur de signe


public:

    Entier(); // Constructeur par défaut
    Entier(int64_t value); // Constructeur prenant un int64_t
    
    // Méthode pour normaliser le vecteur de chiffres
    //enlève tous les 0 non utilisé
    void normalize(); 
    bool isNeg() const; //retourne vrais si l'entier est négatif



    bool operator==(const Entier& other) const;
    bool operator==(const uint64_t n ) const;

    bool operator!=(const Entier& other) const;
    bool operator!=(const uint64_t n ) const;

    bool operator<(const Entier& other) const;
    bool operator>(const Entier& other) const;
    
    bool operator<=(const Entier& other) const;
    bool operator>=(const Entier& other) const;

    Entier operator+(const Entier& other) const; // Opérateur d'addition
    Entier operator+(const uint64_t n) const; // Opérateur d'addition

    Entier operator-(const Entier& other) const; // Opérateur de soustraction
    Entier operator-(const uint64_t n) const; // Opérateur de soustraction
    Entier operator-() const; // Opérateur pour changer le signe de l'Entier

    Entier operator*(const Entier& other) const; // Opérateur de multiplication
    Entier operator*(const uint64_t n) const; // Opérateur de multiplication



    Entier operator/(const Entier& other) const;
    Entier operator/(const uint64_t n) const;
    Entier operator%(const Entier& other) const;
    Entier operator%(const uint64_t n) const;





    std::string toString() const; // Méthode pour convertir l'entier en chaîne de caractères
    friend std::ostream& operator<<(std::ostream& os, const Entier& entier); // Opérateur de flux de sortie

    std::string divideReal(const Entier& other) const;
    Entier gcd_Entier(const Entier& other) const;
    Entier abs() const;


};



#endif // ENTIER_HPP
