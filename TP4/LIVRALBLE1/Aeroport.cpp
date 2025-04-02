// Inclusion des fichiers d'en-tête nécessaires
#include "Aeroport.hpp"  // Définition de la classe Aeroport
#include "Connexion.hpp" // Déclaration de la classe Connexion
#include <sstream>       // Pour utiliser istringstream

using namespace std;     // Utilisation de l'espace de noms standard

/* 
 * Implémentation du constructeur de Aeroport
 * Initialise les attributs avec les valeurs passées en paramètres
 * Format: identifiant, nom, latitude, longitude
 */
Aeroport::Aeroport(const string& id, const string& nom, double lat, double lon)
    : identificateur(id),   // Initialisation de l'identifiant
      nom(nom),            // Initialisation du nom
      latitude(lat),       // Initialisation de la latitude
      longitude(lon) {}    // Initialisation de la longitude

/*
 * Méthode statique pour lire une liste d'aéroports depuis un flux
 * Paramètre:
 *   - is: flux d'entrée (peut être un fichier ou autre)
 * Retourne:
 *   - vector<Aeroport*>: liste des aéroports lus
 */
vector<Aeroport*> Aeroport::lireFromStream(istream& is) {
    vector<Aeroport*> aeroports; // Vecteur résultat
    string ligne;                // Pour stocker chaque ligne lue

    // Lecture ligne par ligne
    while (getline(is, ligne)) {
        istringstream iss(ligne); // Flux pour parser la ligne
        string id, nom;
        double lat, lon;

        // Extraction des valeurs depuis la ligne
        if (iss >> id >> nom >> lat >> lon) {
            // Création d'un nouvel aéroport et ajout au vecteur
            aeroports.push_back(new Aeroport(id, nom, lat, lon));
        }
        // Note: les lignes mal formatées sont ignorées silencieusement
    }

    return aeroports; // Retourne la liste complète
}

/*
 * Méthode pour écrire les informations de l'aéroport dans un flux
 * Format: "identifiant nom latitude longitude"
 */
void Aeroport::ecrire(std::ostream& os) const {
    os << identificateur << " " << nom << " " 
       << latitude << " " << longitude;
}

/*
 * Méthode statique pour écrire une liste d'aéroports dans un flux
 * Paramètres:
 *   - os: flux de sortie
 *   - aeroports: liste des aéroports à écrire
 * Format: un aéroport par ligne
 */
void Aeroport::ecrireListeToStream(ostream& os, const vector<Aeroport*>& aeroports) {
    for (const auto& a : aeroports) {
        a->ecrire(os);  // Écrit les infos de l'aéroport
        os << "\n";     // Saut de ligne entre chaque aéroport
    }
}