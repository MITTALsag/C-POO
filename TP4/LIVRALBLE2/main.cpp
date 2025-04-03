#include "Aeroport.hpp"
#include "Connexion.hpp"
#include "Graphe.hpp"
#include <fstream>
#include <memory>

using namespace std;

int main() {

    // Lecture des aéroports depuis un fichier
    ifstream fichierAeroports("aeroports_in.txt");
    if (!fichierAeroports) {
        cerr << "Erreur: Impossible d'ouvrir aeroports_in.txt" << endl;
        return 1;
    }

    auto aeroports = Aeroport::lireFromStream(fichierAeroports);

    //  Lecture des connexions depuis un fichier
    ifstream fichierConnexions("connexions_in.txt");
    if (!fichierConnexions) {
        cerr << "Erreur: Impossible d'ouvrir connexions_in.txt" << endl;
        return 1;
    }

    auto connexions = Connexion::lireFromStream(fichierConnexions, aeroports);

    // Création du réseau aérien
    Graphe<Aeroport, Connexion, std::string> reseauAerien(aeroports, connexions, true, true, 
        [](Connexion* c) { return c->coutDuree(); });

    // Affichage du réseau
    cout << "=== RESEAU AERIEN ===" << endl;
    reseauAerien.afficher();

    return 0;
}