#include <iostream>
#include <vector>
#include <stdexcept>
#include "Grille.hpp"

using namespace std;

/* Classe Jeu :
    - représente un jeu de la vie
    - contient une grille de cellule
    - permet de faire avancer le jeu d'une génération
*/
class Jeu {
public:
    /* Constructeur */
    Jeu(int l, int c, int w=250);

    /* Fait avancer le jeu d'une génération */
    void Avance();
    
    /* Affiche la grille */
    void Affiche() const;

    /* Ajoute une cellule a la case (i,j) */
    void AjouteCellule(int i, int j);

    /* Supprime une cellule a la case (i,j) */
    void SupprimeCellule(int i, int j);

    /* Renvoie true si la case (i,j) est occupé */
    int NbVoisins(int i, int j) const;

    /* Renvoie wait_time */
    int get_wait_time() const { return wait_time; }

private:
    // grille de cellule
    Grille grille;
    // cree une grille temporaire pour stocker les changements pour eviter de recree un vector a chaque fois et c'est donc plus rapide
    vector<vector<bool>> tmp;
    // temps d'attente entre chaque generation
    int wait_time;
};