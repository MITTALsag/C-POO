#ifndef Grille_Panel_HPP
#define Grille_Panel_HPP

#include <wx/wx.h>
#include "Jeu.hpp"

class Grille_Panel : public wxPanel {
public:
    Grille_Panel(wxPanel *parent, int id );

    /* Fonction qui change la taille de la grille */
    void setSize(int size);

    /* Fonction qui fait avancer le jeu d'une generation */
    void toggleRun();

    /* Fonction qui fait avancer le jeu d'une generation */
    void randomGrid();

    /* Fonction qui remet le jeu a zero */
    void resetGame();

    /* Fonction qui fait avancer le jeu d'une generation */
    void runStep();

    /* Fonction qui change le temps d'attente entre chaque génération */
    void setWaitTime(int w);

    /* Fonction qui sauvegarde la grille */
    void save(string filename);

    /* Fonction qui charge une grille */
    int load(string filename);

    // Fonction qui gere la pause du jeu
    void pause();

private:
    Jeu jeu;
    wxTimer* timer;

    /* Fonction qui dessine la grille */
    void OnPaintRectangle(wxPaintEvent &event);

    /* Fonction qui dessine la grille */
    void OnPaintCircle(wxPaintEvent &event);

    /* Fonction qui fait avancer le jeu */
    void OnTimer(wxTimerEvent &event);

    /* Fonction qui gere le click de la souris */
    void OnMouseClick(wxMouseEvent &event);

    /* Fonction qui gere le redimensionnement de la fenetre */
    void OnResize(wxSizeEvent &event);
};

#endif