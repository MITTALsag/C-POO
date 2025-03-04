#ifndef GRILLE_H
#define GRILLE_H

#include <iostream>
#include <vector>

using namespace std;

/*
* Classe Grille :
    - représente une grille de m lignes et n colonnes.
    - la grille elle même est un vector de vector de booléen
    - une case vide est à false et une case remplie est à true
*/
class Grille {
public:

    /* Constructeur */
    Grille(int l, int c);

    /* Affcihe la grille avec 'O' si la case est vide (false) et '#' si elle est plaine (true)*/
    void Affiche() const;

    /* Ajoute une cellule a la case (i,j) en passant la case de la grille correspondante a true */
    void AjouteCellule(int i, int j);
    
    /* Supprime une cellule a la case (i,j) en passant la case de la grille correspondante a false */
    void SupprimeCellule(int i, int j);

    /* Renvoie true si la case (i,j) est occupé (est à true) */
    bool EstOccupee(int i, int j) const;

    /* Renvoie le nombre de voisin de la case (i,j) (sur les 8 case a coté de (i,j)) */
    int NbVoisins(int i, int j) const;

    /* Copie le vector passer en paramètre dans la grille */
    void CopieGrille(vector<vector<bool>> g) { grille = g;}

    /* renvoie ligne */
    int get_ligne() const { return ligne; }

    /* renvoie colonne */
    int get_colonne() const { return colonne; }

private:
    const int ligne;
    const int colonne;
    vector<vector<bool>> grille;
};



#endif