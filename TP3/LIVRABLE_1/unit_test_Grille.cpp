#include "Grille.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

// Fonction pour tester le constructeur et l'affichage
void TestConstructeurAffichage() {
    cout << "Test du constructeur et de l'affichage :" << endl;
    Grille g(5, 5);
    g.Affiche();
    cout << "-------------------------------\n";

    cout << "Test Affiche :" << endl;
    Grille g2(5, 5);
    g2.AjouteCellule(1, 1);
    g2.AjouteCellule(1, 2);
    g2.AjouteCellule(2, 1);
    g2.Affiche();
    cout << "-------------------------------\n";
}

// Fonction pour tester AjouteCellule
void TestAjouteCellule() {
    cout << "Test AjouteCellule :" << endl;
    Grille g(5, 5);
    
    try {
        g.AjouteCellule(2, 3);
        if (g.EstOccupee(2, 3))
            cout << "✅ Ajout réussi\n";
        else
            cout << "❌ Erreur: cellule non ajoutée\n";
        
        g.AjouteCellule(6, 6); // Hors limites
        cout << "❌ Erreur: exception non levée pour AjouteCellule(6,6)\n";
    } catch (const out_of_range& e) {
        cout << "✅ Exception attrapée pour AjouteCellule(6,6) : " << e.what() << endl;
    }
    cout << "-------------------------------\n";
}

// Fonction pour tester SupprimeCellule
void TestSupprimeCellule() {
    cout << "Test SupprimeCellule :" << endl;
    Grille g(5, 5);
    g.AjouteCellule(2, 2);
    
    try {
        g.SupprimeCellule(2, 2);
        if (!g.EstOccupee(2, 2))
            cout << "✅ Suppression réussie\n";
        else
            cout << "❌ Erreur: cellule non supprimée\n";
        
        g.SupprimeCellule(6, 6); // Hors limites
        cout << "❌ Erreur: exception non levée pour SupprimeCellule(6,6)\n";
    } catch (const out_of_range& e) {
        cout << "✅ Exception attrapée pour SupprimeCellule(6,6) : " << e.what() << endl;
    }
    cout << "-------------------------------\n";
}

// Fonction pour tester EstOccupee
void TestEstOccupee() {
    cout << "Test EstOccupee :" << endl;
    Grille g(5, 5);
    g.AjouteCellule(1, 1);
    
    if (g.EstOccupee(1, 1))
        cout << "✅ EstOccupee(1,1) fonctionne\n";
    else
        cout << "❌ Erreur: EstOccupee(1,1) ne détecte pas la cellule ajoutée\n";

    if (!g.EstOccupee(0, 0))
        cout << "✅ EstOccupee(0,0) fonctionne\n";
    else
        cout << "❌ Erreur: EstOccupee(0,0) détecte une cellule inexistante\n";

    try {
        g.EstOccupee(6, 6); // Hors limites
        cout << "❌ Erreur: exception non levée pour EstOccupee(6,6)\n";
    } catch (const out_of_range& e) {
        cout << "✅ Exception attrapée pour EstOccupee(6,6) : " << e.what() << endl;
    }
    cout << "-------------------------------\n";
}

// Fonction pour tester NbVoisins
void TestNbVoisins() {
    cout << "Test NbVoisins :" << endl;
    Grille g(5, 5);
    g.AjouteCellule(1, 1);
    g.AjouteCellule(1, 2);
    g.AjouteCellule(2, 1);

    if (g.NbVoisins(2, 2) == 3)
        cout << "✅ NbVoisins(2,2) fonctionne\n";
    else
        cout << "❌ Erreur: NbVoisins(2,2) ne renvoie pas le bon nombre\n";

    try {
        g.NbVoisins(6, 6); // Hors limites
        cout << "❌ Erreur: exception non levée pour NbVoisins(6,6)\n";
    } catch (const out_of_range& e) {
        cout << "✅ Exception attrapée pour NbVoisins(6,6) : " << e.what() << endl;
    }
    cout << "-------------------------------\n";
}


// Fonction principale pour exécuter les tests
int main() {
    TestConstructeurAffichage();
    TestAjouteCellule();
    TestSupprimeCellule();
    TestEstOccupee();
    TestNbVoisins();

    cout << "Tous les tests sont terminés." << endl;
    return 0;
}