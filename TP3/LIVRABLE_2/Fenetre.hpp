#ifndef Fenetre_HPP
#define Fenetre_HPP

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "Grille_Panel.hpp"


class Fenetre : public wxFrame {
public:
    Fenetre(const wxString& title);

private:
    wxSpinCtrl* spinner_;
    wxSlider* slider_;
    Grille_Panel* grille_panel_;
    wxStaticText *txtwait;

    // Fonction qui gere le changement de la taille de la grille
    void onSpinnerChange(wxSpinEvent& event);

    // Fonction qui gere le click sur le bouton Run/Pause
    void onToggleRun(wxCommandEvent& event);
    
    // Fonction qui gere la pause du jeu
    void Onpause();
    
    // Fonction qui gere le click sur le bouton Step
    void onStep(wxCommandEvent& event);

    // Fonction qui gere le click sur le bouton Random
    void onRandom(wxCommandEvent& event);

    // Fonction qui gere le click sur le bouton Reset
    void onReset(wxCommandEvent& event);

    // Fonction qui gere le changement du temps d'attente entre chaque generation
    void onWaitTimeChange(wxCommandEvent& event);

    // Fonction qui gere la fermeture de la fenetre
    void OnExit(wxCommandEvent& event);

    // Fonction qui gere la sauvegarde de la grille
    void onSave(wxCommandEvent& event);

    // Fonction qui gere le chargement de la grille depuis un fichier
    void onLoad(wxCommandEvent& event);

};

#endif