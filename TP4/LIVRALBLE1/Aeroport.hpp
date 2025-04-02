#ifndef AEROPORT_HPP
#define AEROPORT_HPP

// Inclusion des bibliothèques nécessaires
#include <string>    // Pour utiliser le type string
#include <vector>    // Pour utiliser les vecteurs
#include <iostream>  // Pour les entrées/sorties

using namespace std; // Utilisation de l'espace de noms standard

// Déclaration anticipée de la classe Connexion (permet de l'utiliser dans les signatures)
class Connexion;

// Définition de la classe Aeroport
class Aeroport {
private:
    // Attributs privés
    string identificateur;  // Code de l'aéroport (ex: "CDG")
    string nom;            // Nom complet de l'aéroport
    double latitude;       // Coordonnée géographique
    double longitude;      // Coordonnée géographique
    
    // Liste des aéroports accessibles directement (vols sortants)
    vector<Aeroport*> Aller;
    
    // Liste des aéroports ayant une liaison vers cet aéroport (vols entrants)
    vector<Aeroport*> Retour;

public:
    // Constructeur - Initialise un nouvel aéroport
    Aeroport(const string& id, const string& nom, double lat, double lon);

    // Destructeur - Nettoie la mémoire
    ~Aeroport() {
        // Supprime tous les aéroports dans les listes Aller et Retour
        for (auto a : Aller) delete a;
        for (auto a : Retour) delete a;
    }

    // Méthodes statiques pour la lecture/écriture
    
    // Lit une liste d'aéroports depuis un flux d'entrée
    static vector<Aeroport*> lireFromStream(std::istream& is);
    
    // Écrit les informations de l'aéroport dans un flux de sortie
    void ecrire(std::ostream& os) const;
    
    // Écrit une liste complète d'aéroports dans un flux
    static void ecrireListeToStream(ostream& os, const vector<Aeroport*>& aeroports);
    
    // Getters - Méthodes d'accès aux attributs
    
    string getIdentificateur() const { return identificateur; }
    string getNom() const { return nom; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
    
    // Méthodes d'accès aux listes de connexions
    
    // Retourne la liste des aéroports accessibles directement
    const vector<Aeroport*>& getAller() const { return Aller; }
    
    // Retourne la liste des aéroports ayant une liaison vers cet aéroport
    const vector<Aeroport*>& getRetour() const { return Retour; }

    // Méthodes pour ajouter des connexions
    
    // Ajoute un aéroport accessible depuis cet aéroport
    void ajouterAller(Aeroport* c) { Aller.push_back(c); }
    
    // Ajoute un aéroport qui a une liaison vers cet aéroport
    void ajouterRetour(Aeroport* c) { Retour.push_back(c); }
};

#endif // Fin du garde d'inclusion AEROPORT_HPP