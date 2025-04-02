#include <iostream>
#include <fstream>
#include <memory>
#include "Aeroport.hpp"
#include "Connexion.hpp"

int main() {
    // Fichiers d'entrée
    const string fichierAeroportsIn = "aeroports_in.txt";
    const string fichierConnexionsIn = "connexions_in.txt";
    
    // Fichiers de sortie
    const string fichierAeroportsOut = "aeroports_out.txt";
    const string fichierConnexionsOut = "connexions_out.txt";

    // 1. Lecture des aéroports
    ifstream finAeroports(fichierAeroportsIn);
    if (!finAeroports) {
        cerr << "Erreur: Impossible d'ouvrir " << fichierAeroportsIn << endl;
        return 1;
    }
    
    auto aeroports = Aeroport::lireFromStream(finAeroports);
    cout << "Lu " << aeroports.size() << " aéroports depuis " << fichierAeroportsIn << endl;

    // 2. Lecture des connexions
    ifstream finConnexions(fichierConnexionsIn);
    if (!finConnexions) {
        cerr << "Erreur: Impossible d'ouvrir " << fichierConnexionsIn << endl;
        return 1;
    }
    
    auto connexions = Connexion::lireFromStream(finConnexions, aeroports);
    cout << "Lu " << connexions.size() << " connexions depuis " << fichierConnexionsIn << endl;

    // 3. Écriture des aéroports en sortie
    ofstream foutAeroports(fichierAeroportsOut);
    if (!foutAeroports) {
        cerr << "Erreur: Impossible de créer " << fichierAeroportsOut << endl;
        return 1;
    }
    
    Aeroport::ecrireListeToStream(foutAeroports, aeroports);
    cout << "Écrit " << aeroports.size() << " aéroports dans " << fichierAeroportsOut << endl;

    // 4. Écriture des connexions en sortie
    ofstream foutConnexions(fichierConnexionsOut);
    if (!foutConnexions) {
        cerr << "Erreur: Impossible de créer " << fichierConnexionsOut << endl;
        return 1;
    }
    
    Connexion::ecrireListeToStream(foutConnexions, connexions);
    cout << "Écrit " << connexions.size() << " connexions dans " << fichierConnexionsOut << endl;

    return 0;
}