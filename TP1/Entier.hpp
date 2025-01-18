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

    // Méthode pour normaliser le vecteur de chiffres
    //enlève tous les 0 non utilisé
    void normalize(); 

public:
    Entier(); // Constructeur par défaut
    Entier(int64_t value); // Constructeur prenant un int64_t
    bool isNeg() const; //retourne vrais si l'entier est négatif

    Entier operator+(const Entier& other) const; // Opérateur d'addition
    Entier operator+(const uint64_t n) const; // Opérateur d'addition

    Entier operator-(const Entier& other) const; // Opérateur de soustraction
    Entier operator-(const uint64_t n) const; // Opérateur de soustraction
    Entier operator-() const; // Opérateur pour changer le signe de l'Entier

    Entier operator*(const Entier& other) const; // Opérateur de multiplication
    Entier operator*(const uint64_t n) const; // Opérateur de multiplication

    bool operator<(const Entier& other) const;
    bool operator>(const Entier& other) const;


    std::string toString() const; // Méthode pour convertir l'entier en chaîne de caractères
    friend std::ostream& operator<<(std::ostream& os, const Entier& entier); // Opérateur de flux de sortie


};



#endif // ENTIER_HPP
