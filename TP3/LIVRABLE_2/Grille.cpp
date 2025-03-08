#include <iostream>
#include <vector>
#include <stdexcept>
#include <random>
#include "Grille.hpp"

using namespace std;


/* Constructeur */
Grille::Grille(int l, int c) : ligne(l), colonne(c) {
    vector<bool> tmp(c, false); 

    for (int i = 0 ; i<l ; i++){
        grille.push_back(tmp);
    }
}

/* Affcihe la grille avec 'O' si la case est vide (false) et '#' si elle est plaine (true) */
void Grille::Affiche() const{

    /* Parcours de toutes les case ligne par lignes */
    for (int i=0; i<ligne; i++){
        for (int j=0; j < colonne; j++){
            /* Si la case est à true (remplie) on affiche '#' */
            if (grille[i][j])
                cout << "#" << " ";
            /* Sinon on affiche 'O' */
            else
                cout << "O" << " ";
        }
        cout << endl;
    }
    cout << endl;
}


/* Ajoute une cellule a la case (i,j) en passant la case de la grille correspondante a true */
void Grille::AjouteCellule(int i, int j) {
    if (i < ligne && j < colonne)
        grille[i][j] = true;
    else
        throw out_of_range("Erreur : la case n'existe pas");
}

/* Supprime une cellule a la case (i,j) en passant la case de la grille correspondante a false */
void Grille::SupprimeCellule(int i, int j){
    if (i < ligne && j < colonne)
        grille[i][j] = false;
    else
        throw out_of_range("Erreur : la case n'existe pas");
}

/* Renvoie true si la case (i,j) est occupé (est à true) */
bool Grille::EstOccupee(int i, int j) const {
    if (i < ligne && j < colonne)
        return grille[i][j];
    else
        throw out_of_range("Erreur : la case n'existe pas");
}

/* Renvoie le nombre de voisin de la case (i,j) (sur les 8 case a coté de (i,j)) */
int Grille::NbVoisins(int i, int j) const {
    if (i >= ligne || j >= colonne)
        throw out_of_range("Erreur : la case n'existe pas");

    int nbVoisins = 0;
    for (int x = i-1; x <= i+1; x++){
        for (int y = j-1; y <= j+1; y++){
            if (x >= 0 && x < ligne && y >= 0 && y < colonne && (x != i || y != j)){
                if (grille[x][y])
                    nbVoisins++;
            }
        }
    }
    return nbVoisins;
}


/* Cree une grille aleatoire */
void Grille::randomize() {
    // Initialisation du générateur de nombres aléatoires
    random_device rd;
    mt19937 gen(rd());  // Générateur basé sur rd()
    uniform_int_distribution<> distrib(0, 1);  // Distribution pour obtenir 0 ou 1

    for (int i = 0; i < ligne; i++) {
        for (int j = 0; j < colonne; j++) {
            // Générer un nombre aléatoire (0 ou 1) et assigner true ou false
            grille[i][j] = (distrib(gen) == 1);  // true si 1, false si 0
        }
    }
}

/* operateur d'affecation */
Grille& Grille::operator=(const Grille& g) {
    ligne = g.ligne;
    colonne = g.colonne;
    grille = g.grille;
    return *this;
}