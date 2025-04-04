#include <iostream>
#include <fstream>
#include "Graphe.hpp"
#include "Aeroport.hpp"
#include "Connexion.hpp"

using namespace std;

vector<Aeroport*> chargerAeroports(const string& fichier) {
    ifstream file(fichier);
    if (!file) {
        throw runtime_error("Impossible d'ouvrir le fichier des aéroports");
    }
    return Aeroport::lireFromStream(file);
}

vector<Connexion*> chargerConnexions(const string& fichier, const vector<Aeroport*>& aeroports) {
    ifstream file(fichier);
    if (!file) {
        throw runtime_error("Impossible d'ouvrir le fichier des connexions");
    }
    return Connexion::lireFromStream(file, aeroports);
}

void testerReseauAerien() {
    try {
        // 1. Chargement des données (identique)
        cout << "Chargement des aéroports..." << endl;
        auto aeroports = chargerAeroports("aeroports_in.txt");
            
        cout << "Chargement des connexions..." << endl;
        auto connexions = chargerConnexions("connexions_in.txt", aeroports);

        // 2. Création du graphe avec coût basé sur la DURÉE
        cout << "\nCreation du graphe (pondere par duree)..." << endl;
        Graphe<Aeroport, Connexion, string> grapheDuree(
            aeroports, connexions, true, true,
            [](Connexion* c) { return c->coutDuree(); }  // On utilise coutDuree() ici
        );
        grapheDuree.afficher();

        // 3. Test BFS (identique structure, mais sur grapheDuree)
        cout << "\n=== PARCOURS EN LARGEUR (BFS) DEPUIS CDG - DUREES ===" << endl;
        auto bfs = grapheDuree.parcoursLargeur("CDG");
        for (const auto& id : bfs) {
            // Ajout du nom pour plus de clarté
            Aeroport* a = grapheDuree.trouverSommet(id);
            cout << id << " (" << a->getNom() << ") ";
        }

        // 4. Test DFS (identique structure, mais sur grapheDuree)
        cout << "\n\n=== PARCOURS EN PROFONDEUR (DFS) DEPUIS CDG - DUREES ===" << endl;
        auto dfs = grapheDuree.parcoursProfondeur("CDG");
        for (const auto& id : dfs) {
            Aeroport* a = grapheDuree.trouverSommet(id);
            cout << id << " (" << a->getNom() << ") ";
        }

        // 5. Test Kruskal version DURÉE
        cout << "\n\n=== ARBRE COUVRANT MINIMUM (KRUSKAL) - DUREES ===" << endl;
        Graphe<Aeroport, Connexion, string> grapheNonOrienteDuree(
            aeroports, connexions, false, true,
            [](Connexion* c) { return c->coutDuree(); }  // Version durée
        );
        auto arbreDuree = grapheNonOrienteDuree.kruskal();
        arbreDuree.afficher();

        // 6. Test Floyd-Warshall version DURÉE
        cout << "\n=== PLUS COURTS CHEMINS (FLOYD-WARSHALL) - DUREES ===" << endl;
        auto durees = grapheDuree.floydWarshall();  // Calcul des durées minimales
            
        // Affichage des temps de trajet minimaux
        cout << "Duree minimale CDG -> JFK: " << durees["CDG"]["JFK"] << " heures" << endl;
        cout << "Duree minimale CDG -> HND: " << durees["CDG"]["HND"] << " heures" << endl;
        cout << "Duree minimale JFK -> DXB: " << durees["JFK"]["DXB"] << " heures" << endl;

        // Exemple de calcul d'itinéraire avec escales
        cout << "\nExemple d'itineraire CDG -> HND:" << endl;
        cout << " - Vol direct: " << durees["CDG"]["HND"] << " heures" << endl;
        cout << " - Via JFK et DXB: " 
            << durees["CDG"]["JFK"] + durees["JFK"]["DXB"] + durees["DXB"]["HND"] 
            << " heures" << endl;


        
    } catch (const exception& e) {
        cerr << "Erreur: " << e.what() << endl;
    }
}

int main() {
    testerReseauAerien();
    return 0;
}