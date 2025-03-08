#include "Fenetre.hpp"
#include <wx/wx.h>

using namespace std;


Fenetre::Fenetre(const wxString& title) : wxFrame(NULL, wxID_ANY, title) {
    // Créer un menu déroulant 
    wxMenu* menu = new wxMenu();

    // Ajouter des éléments au menu 
    menu->Append(1, wxT("&Save"));
    menu->Append(2, wxT("&Load"));
    menu->AppendSeparator();  // Séparateur
    menu->Append(3, wxT("&Exit"));

    // Créer la barre de menu
    wxMenuBar* menuBar = new wxMenuBar();
    menuBar->Append(menu, wxT("&File"));

    // Associer la barre de menu à la fenêtre
    SetMenuBar(menuBar);

    // Associer les événements aux éléments du menu
    Bind(wxEVT_MENU, &Fenetre::onSave, this, 1);
    Bind(wxEVT_MENU, &Fenetre::onLoad, this, 2);
    Bind(wxEVT_MENU, &Fenetre::OnExit, this, 3);

    // panel
    wxPanel *panel = new wxPanel(this, -1);

    // sizer vertical
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    // sizer horizontal
    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

    // grille
    grille_panel_ = new Grille_Panel(panel, -1);
    //grille_panel_->SetBackgroundColour(wxColour(50, 50, 50));

    // boutons
    wxStaticText *txtLbl_grid = new wxStaticText(panel, wxID_ANY, wxT("Grid size:"));
    spinner_ = new wxSpinCtrl(panel, wxID_ANY, wxT("30"));
    spinner_->SetRange(10, 1000);
    wxButton* runBtn = new wxButton(panel, wxID_ANY, wxT("Run/Pause"));
    wxButton* stepBtn = new wxButton(panel, wxID_ANY, wxT("Step"));
    wxButton* rndBtn = new wxButton(panel, wxID_ANY, wxT("Random"));
    wxButton* rstBtn = new wxButton(panel, wxID_ANY, wxT("Reset"));
    txtwait = new wxStaticText(panel, wxID_ANY, wxString::Format(wxT("Wait time: 250 ms")));
    slider_ = new wxSlider(panel, wxID_ANY, 250, 1, 1000, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL);

    // bind des evenements
    spinner_->Bind(wxEVT_SPINCTRL, &Fenetre::onSpinnerChange, this);
    runBtn->Bind(wxEVT_BUTTON, &Fenetre::onToggleRun, this);
    stepBtn->Bind(wxEVT_BUTTON, &Fenetre::onStep, this);
    rndBtn->Bind(wxEVT_BUTTON, &Fenetre::onRandom, this);
    rstBtn->Bind(wxEVT_BUTTON, &Fenetre::onReset, this);
    slider_->Bind(wxEVT_SLIDER, &Fenetre::onWaitTimeChange, this);

    //Ajout des elements dans la fenetre
    hbox->Add(txtLbl_grid, 0, wxALIGN_CENTER_VERTICAL);
    hbox->AddSpacer(10);  // Espacement de 10px
    hbox->Add(spinner_, 0, wxALIGN_CENTER_VERTICAL);
    hbox->AddSpacer(10);  // Espacement de 10px
    hbox->Add(txtwait, 0, wxALIGN_CENTER_VERTICAL);
    hbox->AddSpacer(10);  // Espacement de 10px
    hbox->Add(slider_, 0, wxALIGN_CENTER_VERTICAL);
    hbox->AddSpacer(20);  // Espacement de 10px
    hbox->Add(runBtn, 0, wxALIGN_CENTER_VERTICAL);
    hbox->AddSpacer(10);  // Espacement de 10px
    hbox->Add(stepBtn, 0, wxALIGN_CENTER_VERTICAL);
    hbox->AddSpacer(10);  // Espacement de 10px
    hbox->Add(rndBtn, 0, wxALIGN_CENTER_VERTICAL);
    hbox->AddSpacer(10);  // Espacement de 10px
    hbox->Add(rstBtn, 0, wxALIGN_CENTER_VERTICAL);


    //Ajout des elements dans la fenetre
    vbox->Add(hbox, 0, wxALIGN_CENTER | wxALL, 5);
    vbox->Add(grille_panel_, 1, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 5);
    panel->SetSizer(vbox);

    this->SetClientSize(1000, 700);
    Centre();
}


/* Fonction qui gere le changement de la taille de la grille */
void Fenetre::onSpinnerChange(wxSpinEvent& event) {
    int gridSize = event.GetValue();  // Récupère la nouvelle taille de la grille
    grille_panel_->setSize(gridSize);  // Change la taille de la grille
}

// Fonction qui gere le click sur le bouton Run/Pause
void Fenetre::onToggleRun(wxCommandEvent& event) {
    (void) event;
    grille_panel_->toggleRun();

}

// Fonction qui gere la pause du jeu
void Fenetre::Onpause() {
    grille_panel_->pause();
}

// Fonction qui gere le click sur le bouton Step
void Fenetre::onStep(wxCommandEvent& event) {
    (void) event;
    grille_panel_->runStep();

}

// Fonction qui gere le click sur le bouton Random
void Fenetre::onRandom(wxCommandEvent& event) {
    (void) event;
    grille_panel_->randomGrid();

}

// Fonction qui gere le click sur le bouton Reset
void Fenetre::onReset(wxCommandEvent& event) {
    (void) event;
    grille_panel_->resetGame();

}

// Fonction qui gere le changement du temps d'attente entre chaque generation
void Fenetre::onWaitTimeChange(wxCommandEvent& event){
    (void) event;
    int new_wait_time = slider_->GetValue();
    txtwait->SetLabel(wxString::Format(wxT("Wait time: %d ms"), new_wait_time));
    grille_panel_->setWaitTime(new_wait_time);

}

// Fonction qui gere la fermeture de la fenetre
void Fenetre::OnExit(wxCommandEvent& event)
{
    (void) event;
    Close(true);  // Fermer la fenêtre
}


// Fonction qui gere la sauvegarde de la grille
void Fenetre::onSave(wxCommandEvent& event) {
    (void) event;
    Onpause();
    // Sauvegarde la grille dans un fichier texte

    // Ouvre une boîte de dialogue pour choisir le fichier de sauvegarde : 
    //  - titre (de la boite de dialogue): "Enregistrer sous"
    //  - répertoire initial: "./configuration_initiale"
    //  - filtre: "Fichiers texte (*.txt)|*.txt"
    //  - mode: wxFD_SAVE (pour sauvegarder) et wxFD_OVERWRITE_PROMPT (pour demander confirmation si le fichier existe déjà)
    wxFileDialog saveFileDialog(this, "Enregistrer sous", "./configuration_initiale", "",
                                "Fichiers texte (*.txt)|*.txt",
                                wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return; // L'utilisateur a annulé

    // Récupère le chemin du fichier choisi
    wxString filePath = saveFileDialog.GetPath();


    try {
        // Sauvegarde la grille dans le fichier 
        grille_panel_->save(filePath.ToStdString());
    } catch (const invalid_argument& e) {
        // Affiche une boîte de dialogue d'erreur
        wxMessageDialog errorDialog(this, e.what(), "Erreur", wxOK | wxICON_ERROR);
        errorDialog.ShowModal();
    }
}

// Fonction qui gere le chargement de la grille depuis un fichier
void Fenetre::onLoad(wxCommandEvent& event) {
    (void) event;
    Onpause();
    // Load la grille

    // Ouvre une boîte de dialogue pour choisir le fichier a load : 
    //  - titre (de la boite de dialogue): "Ouvrir un fichier"
    //  - répertoire initial: "./configuration_initiale"
    //  - filtre: "Fichiers texte (*.txt)|*.txt"
    //  - mode: wxFD_OPEN (pour ouvrir) et wxFD_FILE_MUST_EXIST (pour que le fichier existe deja)
    wxFileDialog openFileDialog(this, "Ouvrir un fichier", "./configuration_initiale", "",
                                "Fichiers texte (*.txt)|*.txt",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // L'utilisateur a annulé

    // Récupère le chemin du fichier choisi
    wxString filePath = openFileDialog.GetPath();

    int taille;
    try {
        // Sauvegarde la grille dans le fichier 
        // taille est la nouvelle taille de la grille
        taille = grille_panel_->load(filePath.ToStdString());
    } catch (const invalid_argument& e) {
        // Affiche une boîte de dialogue d'erreur
        wxMessageDialog errorDialog(this, e.what(), "Erreur", wxOK | wxICON_ERROR);
        errorDialog.ShowModal();
    }

    spinner_->SetValue(taille);
    slider_->SetValue(250);
    int new_wait_time = slider_->GetValue();
    txtwait->SetLabel(wxString::Format(wxT("Wait time: %d ms"), new_wait_time));
}


