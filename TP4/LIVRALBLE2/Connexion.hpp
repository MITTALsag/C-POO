// Garde d'inclusion pour éviter les inclusions multiples
#ifndef CONNEXION_HPP
#define CONNEXION_HPP

// Inclusions nécessaires
#include "Aeroport.hpp"  // Pour la classe Aeroport
#include <iostream>      // Pour les flux d'entrée/sortie

using namespace std;     // Utilisation de l'espace de noms standard

// Définition de la classe Connexion représentant une liaison entre aéroports
class Connexion {
private:
    // Membres privés
    Aeroport* depart;   // Pointeur vers l'aéroport de départ (non possédé)
    Aeroport* arrivee;  // Pointeur vers l'aéroport d'arrivée (non possédé)
    double duree;       // Durée du vol en heures
    double distance;    // Distance du vol en kilomètres

public:
    // Constructeur
    Connexion(Aeroport* dep, Aeroport* arr, double duree, double distance = 0.0);

    // Destructeur
    ~Connexion() {
        // On ne supprime pas les aéroports car ils sont gérés ailleurs
        depart = nullptr;   // Sécurité : évite les pointeurs pendants
        arrivee = nullptr;  // Sécurité : évite les pointeurs pendants
    }
    
    // Méthodes statiques de lecture/écriture
    
    // Lit une liste de connexions depuis un flux
    static vector<Connexion*> lireFromStream(istream& is, const vector<Aeroport*>& aeroports);
    
    // Écrit une liste de connexions dans un flux
    static void ecrireListeToStream(ostream& os, const vector<Connexion*>& connexions);

    // Getters
    
    Aeroport* getDepart() const { return depart; }   // Accès à l'aéroport de départ
    Aeroport* getArrivee() const { return arrivee; } // Accès à l'aéroport d'arrivée

    // Méthode statique de calcul de distance entre aéroports
    static double calcul_distance(Aeroport* dep, Aeroport* arr);
    
    // Méthodes de calcul de coût
    
    double coutDistance() const { return distance; } // Coût basé sur la distance
    double coutDuree() const { return duree; }      // Coût basé sur la durée
};

#endif // Fin du garde d'inclusion CONNEXION_HPP