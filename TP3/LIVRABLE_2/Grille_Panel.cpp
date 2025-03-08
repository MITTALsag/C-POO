#include <wx/wx.h>
#include <fstream>
#include "Grille_Panel.hpp"


/* Constructeur */
Grille_Panel::Grille_Panel(wxPanel *parent, int id) : wxPanel(parent, id, wxDefaultPosition), jeu(30,30) {

    // timer pour faire avancer le jeu
    timer = new wxTimer(this);

    // bind des evenements
    this->Bind(wxEVT_PAINT, &Grille_Panel::OnPaint, this);
    this->Bind(wxEVT_TIMER, &Grille_Panel::OnTimer, this);
    this->Bind(wxEVT_LEFT_DOWN, &Grille_Panel::OnMouseClick, this);
    this->Bind(wxEVT_SIZE, &Grille_Panel::OnResize, this);

}

/* Fonction qui dessine la grille */
void Grille_Panel::OnPaint(wxPaintEvent &event) {
    wxPaintDC dc(this);
    (void) event; // évite le warning unused parameter

    // Taille du panel
    wxSize size = GetClientSize();
    int width = size.GetWidth();
    int height = size.GetHeight();

    int cols = jeu.get_colonne();
    int rows = jeu.get_ligne();

    // Taille ajustée pour éviter les bordures
    int cell_width = width / cols;
    int cell_height = height / rows;

    int grid_width = cell_width * cols;   // Largeur ajustée
    int grid_height = cell_height * rows; // Hauteur ajustée

    int offset_x = (width - grid_width) / 2;   // Centrer horizontalement
    int offset_y = (height - grid_height) / 2; // Centrer verticalement

    // Dessine les cellules sous forme de rectangles
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            if (jeu.EstOccupee(i, j)) {
                dc.SetBrush(*wxBLACK_BRUSH); // Cellule occupée en noir
            } else {
                dc.SetBrush(*wxWHITE_BRUSH); // Cellule vide en blanc
            }

            // Coordonnées pour centrer le rectangle dans la cellule
            int x = offset_x + i * cell_width;
            int y = offset_y + j * cell_height;

            dc.DrawRectangle(x, y, cell_width, cell_height);
        }
    }
}
/* Fonction qui fait avancer le jeu */
void Grille_Panel::OnTimer(wxTimerEvent &event) {
    jeu.Avance();
    (void) event;
    Refresh();
}

/* Fonction qui gere le click de la souris */
void Grille_Panel::OnMouseClick(wxMouseEvent &event) {
    // taille de la fenetre
    wxSize size = GetClientSize();
    int width = size.GetWidth();
    int height = size.GetHeight();

    // taille des cellules
    int cell_width = width / jeu.get_colonne();
    int cell_height = height / jeu.get_ligne();

    // position de la souris
    int x = event.GetX() / cell_width;
    int y = event.GetY() / cell_height;

    // si la case est occupé on la supprime sinon on l'ajoute
    if(jeu.EstOccupee(x, y)) {
        jeu.SupprimeCellule(x, y);
    } else {
        jeu.AjouteCellule(x, y);
    }

    Refresh();
}

/* Fonction qui gere le redimensionnement de la fenetre */
void Grille_Panel::OnResize(wxSizeEvent &event) {
    (void) event;
    Refresh();
}


/* Fonction qui change la taille de la grille */
void Grille_Panel::setSize(int size) {

    jeu = Jeu(size, size, jeu.get_wait_time());
    resetGame();

}

/* Fonction qui fait avancer le jeu (pause/start) */
void Grille_Panel::toggleRun() {
    // si le timer est en marche on l'arrete
    if (timer->IsRunning()) {
        timer->Stop();
    } else {
        timer->Start(jeu.get_wait_time());
    }
}

// Fonction qui gere la pause du jeu
void Grille_Panel::pause() {
    if (timer->IsRunning()) {
        timer->Stop();
    }
}

/* Fonction qui fait avancer le jeu d'une generation */
void Grille_Panel::randomGrid() {
    // si le timer est en marche on l'arrete
    if (timer->IsRunning()) {
        timer->Stop();
    }
    // on cree une nouvelle grille aleatoire
    jeu.randomize();
    Refresh();
}

/* Fonction qui remet le jeu a zero */
void Grille_Panel::resetGame() {
    if (timer->IsRunning()) {
        timer->Stop();
    }
    jeu.reset();
    Refresh();
}

/* Fonction qui fait avancer le jeu d'une generation */
void Grille_Panel::runStep() {
    jeu.Avance();
    Refresh();
}


/* Fonction qui change le temps d'attente entre chaque génération */
void Grille_Panel::setWaitTime(int w) {
    jeu.set_wait_time(w);
    
    if (timer->IsRunning()) {
        timer->Start(w);
    }
}


/* Fonction qui sauvegarde la grille */
void Grille_Panel::save(string filename) {

    // ouverture du fichier en ecriture et troncature (ecrase le fichier si il existe)
    ofstream file(filename, ios::out | ios::trunc);

    if(!file.is_open()) {
        throw invalid_argument("Erreur : impossible d'ouvrir le fichier");
    }

    // ecriture de la taille de la grille
    file << jeu.get_ligne() << " " << jeu.get_colonne() << endl;
    for(int i = 0; i < jeu.get_ligne(); i++) {
        for(int j = 0; j < jeu.get_colonne(); j++) {
            // ecriture de la case (i,j)
            if (jeu.EstOccupee(i, j))
                file << "1";
            else
                file << "0";
        }
        file << endl;
    }

    file.close();
    
}

/* Fonction qui charge une grille */
int Grille_Panel::load(string filename) {

    // ouverture du fichier en lecture
    ifstream file(filename, ios::in);

    if(!file.is_open()) {
        throw invalid_argument("Erreur : impossible d'ouvrir le fichier");
    }

    // lecture de la taille de la grille 
    int ligne, colonne;
    file >> ligne >> colonne;
    
    // changement de la taille de la grille
    jeu = Jeu(ligne, colonne);
    char c;
    
    // lecture de la grille
    for(int i = 0; i < jeu.get_ligne(); i++) {
        for(int j = 0; j < jeu.get_colonne(); j++) {
            file >> c;
            if (c == '1')
                jeu.AjouteCellule(i, j);
        }
    }
    file.close();

    Refresh();
    return ligne;
}