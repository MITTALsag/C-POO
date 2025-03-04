#include <iostream>
#include <vector>
#include <stdexcept>
#include "Grille.hpp"
#include "Jeu.hpp"

using namespace std;

/* Constructeur */
Jeu::Jeu(int l, int c, int w) : grille(l, c), tmp(l, vector<bool>(c, false)), wait_time(w) {}

/* Fait avancer le jeu d'une génération */
void Jeu::Avance() {
    /* Parcours de toutes les case */
    for (int i = 0; i < grille.get_ligne(); i++) {
        for (int j = 0; j < grille.get_colonne(); j++) {
            int nb_voisins = NbVoisins(i, j);
            /* si la case est occupé */
            if (grille.EstOccupee(i, j)) {
                /* si elle est en isolement ou ettoufement elle meurent */
                if (nb_voisins < 2 || nb_voisins > 3)
                    tmp[i][j] = false;
                /* sinon elle vit */
                else
                    tmp[i][j] = true;
            } 
            /* sinon la case est inocupé */
            else {
                /* si elle a exacteent 3 voisine elle vit */
                if (nb_voisins == 3)
                    tmp[i][j] = true;
                /* sinon elle meurt */
                else
                    tmp[i][j] = false;
            }
        }
    }
    /* on copie les changements dans la grille */
    grille.CopieGrille(tmp);
}

/* Affiche la grille */
void Jeu::Affiche() const {
    grille.Affiche();
}

/* Ajoute une cellule a la case (i,j) */
void Jeu::AjouteCellule(int i, int j) {
    grille.AjouteCellule(i, j);
}

/* Supprime une cellule a la case (i,j) */
void Jeu::SupprimeCellule(int i, int j) {
    grille.SupprimeCellule(i, j);
}

/* Renvoie true si la case (i,j) est occupé */
int Jeu::NbVoisins(int i, int j) const {
    return grille.NbVoisins(i, j);
}