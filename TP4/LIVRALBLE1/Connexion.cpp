// Inclusion des fichiers nécessaires
#include "Connexion.hpp"  // Pour la classe Connexion
#include <cmath>          // Pour les fonctions mathématiques (sin, cos, etc.)
#include <sstream>        // Pour le traitement des chaînes
#include <iostream>       // Pour les messages d'erreur

using namespace std;

// Constante : rayon de la Terre en kilomètres
const double RAYON_TERRE = 6371.0;

/*
 * Constructeur de Connexion
 * Initialise les attributs avec les valeurs passées en paramètres
 */
Connexion::Connexion(Aeroport* dep, Aeroport* arr, double duree, double distance)
    : depart(dep),       // Aéroport de départ
      arrivee(arr),      // Aéroport d'arrivée
      duree(duree),      // Durée du vol en heures
      distance(distance) // Distance du vol en km (calculée si non fournie)
{}

/*
 * Méthode statique pour lire des connexions depuis un flux
 * Format attendu : "ID_DEP ID_ARR DUREE"
 */
vector<Connexion*> Connexion::lireFromStream(istream& is, const vector<Aeroport*>& aeroports) {
    vector<Connexion*> connexions; // Liste résultat
    string ligne;                 // Pour stocker chaque ligne lue

    // Lecture ligne par ligne
    while (getline(is, ligne)) {
        istringstream iss(ligne); // Flux pour parser la ligne
        string idDep, idArr;     // Identifiants des aéroports
        double duree;            // Durée du vol

        // Extraction des valeurs depuis la ligne
        if (iss >> idDep >> idArr >> duree) {
            // Recherche des aéroports correspondants
            Aeroport* dep = nullptr;
            Aeroport* arr = nullptr;

            for (const auto& a : aeroports) {
                if (a->getIdentificateur() == idDep) dep = a;
                if (a->getIdentificateur() == idArr) arr = a;
            }

            // Si les aéroports sont trouvés
            if (dep && arr) {
                // Calcul de la distance automatique
                double distance = calcul_distance(dep, arr);
                // Création de la connexion
                Connexion* c = new Connexion(dep, arr, duree, distance);
                connexions.push_back(c);
                
                // Mise à jour des aéroports
                dep->ajouterAller(arr);
                arr->ajouterRetour(dep);
            } else {
                // Gestion d'erreur si aéroport non trouvé
                cerr << "Erreur: Aéroport introuvable pour la connexion " 
                     << idDep << " -> " << idArr << endl;
                exit(1); // Arrêt du programme
            }
        }
    }
    return connexions;
}

/*
 * Méthode pour écrire une liste de connexions dans un flux
 * Format : "ID_DEP ID_ARR DUREE DISTANCE"
 */
void Connexion::ecrireListeToStream(ostream& os, const vector<Connexion*>& connexions) {
    for (const auto& connexion : connexions) {
        // Écriture des informations
        os << connexion->getDepart()->getIdentificateur() << " "
           << connexion->getArrivee()->getIdentificateur() << " "
           << connexion->coutDuree() << " "
           << connexion->coutDistance();
        
        // Saut de ligne sauf pour la dernière connexion
        if (&connexion != &connexions.back()) {
            os << "\n";
        }
    }
}

/*
 * Méthode statique pour calculer la distance entre deux aéroports
 * Utilise la formule haversine (sphère)
 */
double Connexion::calcul_distance(Aeroport* dep, Aeroport* arr) {
    // Conversion des degrés en radians
    double lat1 = dep->getLatitude() * M_PI / 180.0;
    double lon1 = dep->getLongitude() * M_PI / 180.0;
    double lat2 = arr->getLatitude() * M_PI / 180.0;
    double lon2 = arr->getLongitude() * M_PI / 180.0;
    
    // Différences de coordonnées
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;
    
    // Calcul intermédiaire
    double a = sin(dlat/2) * sin(dlat/2) 
             + cos(lat1) * cos(lat2) * sin(dlon/2) * sin(dlon/2);
    
    // Calcul final
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    
    // Distance = rayon * angle
    return RAYON_TERRE * c;
}