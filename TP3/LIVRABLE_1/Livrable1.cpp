#include <iostream>
#include <chrono>
#include <thread>
#include "Grille.hpp"
#include "Jeu.hpp"

using namespace std;


Jeu barre(int wait_time){
    Jeu jeu(5, 5, wait_time);
    jeu.AjouteCellule(1, 1);
    jeu.AjouteCellule(1, 2);
    jeu.AjouteCellule(1, 3);
    return jeu;
}

Jeu gilder(int wait_time){
    Jeu jeu(10, 10, wait_time);
    jeu.AjouteCellule(1, 2);
    jeu.AjouteCellule(2, 3);
    jeu.AjouteCellule(3, 1);
    jeu.AjouteCellule(3, 2);
    jeu.AjouteCellule(3, 3);
    return jeu;
}

Jeu bloc(int wait_time){
    Jeu jeu(5, 5, wait_time);
    jeu.AjouteCellule(1, 1);
    jeu.AjouteCellule(1, 2);
    jeu.AjouteCellule(2, 1);
    jeu.AjouteCellule(2, 2);
    return jeu;
}

Jeu configurationUtilisateur() {
    int choix;
    cout << "Entrez la configuration que vous voulez entre :" << endl;
    cout << "\t1. Barre (periodique) (1)" << endl;
    cout << "\t2. Gilder (2)" << endl;
    cout << "\t3. Bloc (inerte) (3)" << endl;
    cin >> choix;

    cout << "Choisir en rapide(1), moyen(2) ou lent(3) pour le temps d'attente en chaque generation : ";
    int wait_time;
    cin >> wait_time;
    switch (wait_time) {
        case 1:
            wait_time = 250;
            break;
        case 2:
            wait_time = 500;
            break;
        default:
            wait_time = 1000;
            break;
        }

    switch (choix) {
        case 1:
            return barre(wait_time);
        case 2:
            return gilder(wait_time);
        case 3:
            return bloc(wait_time);
        default:
            cout << "Choix invalide : Veuillez choisir 1, 2 ou 3" << endl;
            return configurationUtilisateur();
    }

}

int main(){
    Jeu jeu = configurationUtilisateur();
    int i = 0;
    while(i <= 25){
        cout << "\033[2J\033[1;1H" << "Generation " << i++ << endl;
        jeu.Affiche();
        jeu.Avance();
        this_thread::sleep_for(chrono::milliseconds(jeu.get_wait_time()));
    }
    return 0;
}