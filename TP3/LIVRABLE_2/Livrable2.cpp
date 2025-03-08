#include "Livrable2.hpp"
#include "Fenetre.hpp"


bool MyApp::OnInit() {
    Fenetre *fenetre = new Fenetre
    (wxT("Jeu de la vie"));
    fenetre->Show(true);
    return true;
}


wxIMPLEMENT_APP(MyApp);