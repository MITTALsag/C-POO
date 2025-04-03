#ifndef GRAPHE_HPP
#define GRAPHE_HPP

#include <vector>
#include <map>          // Inclure pour map
#include <set>          // Inclure pour set
#include <algorithm>    // Inclure pour sort
#include <functional>   // Inclure pour function
#include <stdexcept>    // Inclure pour logic_error
#include <utility>      // Inclure pour pair
using namespace std;


template <typename Sommet, typename Arete, typename ID_Type>
class Graphe;



template <typename Sommet, typename Arete, typename ID_Type>
class Graphe {
private:
    vector<Sommet*> sommets;
    vector<vector<pair<ID_Type, double>>> listeAdjacence; // (id_sommet, poids)
    bool oriente;
    bool pondere;
    
    // Retourne l'index d'un sommet dans le vecteur
    int getIndexSommet(const ID_Type id) const{
        for (size_t i = 0; i < sommets.size(); ++i) {
            if (sommets[i]->getIdentificateur() == id) {
                return static_cast<int>(i);
            }
        }
        throw invalid_argument("Sommet non trouvé");
    }

public:
    // Constructeur générique avec fonction de poids personnalisable
    template <typename FuncPoids>
    Graphe(const std::vector<Sommet*>& sommetsInit,
           const std::vector<Arete*>& aretesInit,
           bool estOriente,
           bool estPondere,
           FuncPoids getPoids) // Valeur par défaut
        : oriente(estOriente), pondere(estPondere)
    {
        // Code commun
        for (auto s : sommetsInit) {
            sommets.push_back(s);
            listeAdjacence.emplace_back();
        }
        
        // Utilisation de la fonction de poids fournie
        for (auto a : aretesInit) {
            ajouterArete(a->getDepart()->getIdentificateur(),
                        a->getArrivee()->getIdentificateur(),
                        pondere ? getPoids(a) : 0.0);
        }
    }

    // Constructeur pour un graphe vide
    Graphe(bool estOriente = false, bool estPondere = false) : oriente(estOriente), pondere(estPondere) {} 

    ~Graphe() {
        for (auto s : sommets) delete s;
    }

    // Ajoute un sommet au graphe
    void ajouterSommet(Sommet* sommet) {
        if (!sommet || sommet->getIdentificateu() == "" ) throw invalid_argument("Sommet invalide");
        // Vérifie si le sommet existe déjà
        for (auto s : sommets) {
            if (s->getIdentificateur() == sommet->getIdentificateur()) {
                throw invalid_argument("Sommet déjà existant");
            }
        }
        // Ajoute le sommet
        sommets.push_back(sommet);
        listeAdjacence.push_back(vector<pair<ID_Type, double>>());
    }


    // Ajoute une arête entre deux sommets
    void ajouterArete(const ID_Type idDepart, const ID_Type idArrivee, double poids) {
        Sommet* depart = trouverSommet(idDepart);
        Sommet* arrivee = trouverSommet(idArrivee);
        
        if (!depart || !arrivee) 
            throw invalid_argument("Un des sommets n'existe pas");
    
        listeAdjacence[getIndexSommet(idDepart)].push_back({idArrivee, poids});
        
        if (!oriente) {
            listeAdjacence[getIndexSommet(idArrivee)].push_back({idDepart, poids});
        }
    }
    
    // Trouve un sommet par son ID
    Sommet* trouverSommet(const ID_Type id) const {
        for (auto s : sommets) {
            if (s->getIdentificateur() == id) return s;
        }
        return nullptr;
    }
    // Affiche le graphe
    void afficher() const {
        cout << "Graphe " << (oriente ? "orienté" : "non orienté") 
                  << " et " << (pondere ? "pondéré" : "non pondéré") << endl;
        
        for (size_t i = 0; i < sommets.size(); ++i) {
            cout << sommets[i]->getIdentificateur() << " -> ";
            for (const auto& voisin : listeAdjacence[i]) {
                cout << voisin.first;
                if (pondere) cout << "(" << voisin.second << ")";
                cout << " ";
            }
            cout << endl;
        }
    }

    vector<ID_Type> parcoursLargeur(const ID_Type& depart) const {
        vector<ID_Type> resultat;
        set<ID_Type> visites;
        queue<ID_Type> file;
    
        file.push(depart);
        visites.insert(depart);
    
        while (!file.empty()) {
            ID_Type courant = file.front();
            file.pop();
            resultat.push_back(courant);
    
            int index = getIndexSommet(courant);
            for (const auto& voisin : listeAdjacence[index]) {
                if (visites.find(voisin.first) == visites.end()) {
                    visites.insert(voisin.first);
                    file.push(voisin.first);
                }
            }
        }
    
        return resultat;
    }

    vector<ID_Type> parcoursProfondeur(const ID_Type& depart) const {
        vector<ID_Type> resultat;
        set<ID_Type> visites;
        stack<ID_Type> pile;
    
        pile.push(depart);
        visites.insert(depart);
    
        while (!pile.empty()) {
            ID_Type courant = pile.top();
            pile.pop();
            resultat.push_back(courant);
    
            int index = getIndexSommet(courant);
            for (const auto& voisin : listeAdjacence[index]) {
                if (visites.find(voisin.first) == visites.end()) {
                    visites.insert(voisin.first);
                    pile.push(voisin.first);
                }
            }
        }
    
        return resultat;
    }

    Graphe<Sommet, Arete, ID_Type> kruskal() const {
        // Vérification que le graphe est non orienté
        if (oriente) {
            throw logic_error("Kruskal ne s'applique qu'aux graphes non orientes");
        }
    
        // Structure pour l'union-find avec map ordinaire
        map<ID_Type, ID_Type> parent;
        for (const auto& sommet : sommets) {
            parent[sommet->getIdentificateur()] = sommet->getIdentificateur();
        }
    
        // Fonction pour trouver la racine avec compression de chemin
        function<ID_Type(ID_Type)> trouver = [&](ID_Type id) {
            if (parent[id] != id) {
                parent[id] = trouver(parent[id]);
            }
            return parent[id];
        };
    
        // Trier toutes les arêtes par poids croissant
        vector<pair<double, pair<ID_Type, ID_Type>>> aretes;
        for (size_t i = 0; i < sommets.size(); ++i) {
            ID_Type idU = sommets[i]->getIdentificateur();
            for (const auto& voisin : listeAdjacence[i]) {
                ID_Type idV = voisin.first;
                if (idU < idV) { // Éviter les doublons dans un graphe non orienté
                    aretes.emplace_back(voisin.second, make_pair(idU, idV));
                }
            }
        }
        sort(aretes.begin(), aretes.end());
    
        // Construire l'arbre couvrant minimum
        Graphe<Sommet, Arete, ID_Type> arbre(false, true);
        
        // Copier les sommets
        for (const auto& sommet : sommets) {
            arbre.ajouterSommet(new Sommet(*sommet));
        }
    
        // Ajouter les arêtes de l'arbre couvrant
        for (const auto& arete : aretes) {
            ID_Type u = arete.second.first;
            ID_Type v = arete.second.second;
            ID_Type racineU = trouver(u);
            ID_Type racineV = trouver(v);
    
            if (racineU != racineV) {
                arbre.ajouterArete(u, v, arete.first);
                parent[racineV] = racineU; // Union
            }
        }
    
        return arbre;
    }

    std::map<ID_Type, std::map<ID_Type, double>> floydWarshall() const {
        std::map<ID_Type, std::map<ID_Type, double>> distances;
    
        // 1. Initialisation de la matrice des distances
        for (const auto& u : sommets) {
            ID_Type idU = u->getIdentificateur();
            for (const auto& v : sommets) {
                distances[idU][v->getIdentificateur()] = std::numeric_limits<double>::infinity();
            }
            distances[idU][idU] = 0.0; // Distance d'un sommet à lui-même
        }
    
        // 2. Remplissage avec les arêtes existantes
        for (size_t i = 0; i < sommets.size(); ++i) {
            ID_Type idU = sommets[i]->getIdentificateur();
            for (const auto& voisin : listeAdjacence[i]) {
                distances[idU][voisin.first] = voisin.second;
            }
        }
    
        // 3. Algorithme principal de Floyd-Warshall
        for (const auto& k : sommets) {
            ID_Type idK = k->getIdentificateur();
            for (const auto& i : sommets) {
                ID_Type idI = i->getIdentificateur();
                for (const auto& j : sommets) {
                    ID_Type idJ = j->getIdentificateur();
                    if (distances[idI][idK] + distances[idK][idJ] < distances[idI][idJ]) {
                        distances[idI][idJ] = distances[idI][idK] + distances[idK][idJ];
                    }
                }
            }
        }
    
        return distances;
    }
   
};

#endif // GRAPHE_HPP