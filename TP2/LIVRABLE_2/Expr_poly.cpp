#include <iostream>
#include <numeric>

#include "Expr_poly.hpp"

using namespace std;

/* Classe Cst */
#pragma region Cst
/* Crée le rationnel n/d */
Cst::Cst(int n, int d) : num(n), denum(d) { 
    if (d == 0) 
        throw invalid_argument("Erreur (Cst constructor) : Dénominateur ne peut pas être zéro !"); 
    
    this->simplifie();

    /* Mettre le moin au numérateur */
    if (denum < 0)
        num = -num;

}

/* Affiche le rationnel sous forme num/denum */
void Cst::affiche() const{ 
    if (denum == 1)
        cout << num;
    else
        cout << num << "/" << denum;
}

/* Méthode de simplification (cette méthode modifie le Cst et renvoie le resultat aussi) */
Cst Cst::simplifie() {
    /* Calcule du pgcd entre le numérateur et le denominateur */
    int pgcd = gcd(num, denum);

    num /= pgcd;
    denum /= pgcd;

    // Simplification par le pgcg
    return *this;
}

#pragma endregion Cst

/* Classe Add */
#pragma region Add
/* Constructeur qui initialise l'addition g + d (cree une copie profonde de g et d)*/
Add::Add(const ExprArith& g, const ExprArith& d){
    gauche = g.clone();
    droite = d.clone();
}

/* Affiche un Add sous forme (gauche + droite) */
void Add::affiche() const {
    cout << "(";
    gauche->affiche();  // Affiche le côté gauche
    cout << " + ";
    droite->affiche();  // Affiche le côté droit
    cout << ")";
}

/* Méthode de simplification */
Cst Add::simplifie(){
    /* on simplifie a gauche et a droite */
    Cst gauche_cst = gauche->simplifie();
    Cst droite_cst = droite->simplifie();

    /* On calcul le resultat de l'opération */
    int res_num = (gauche_cst.get_num() * droite_cst.get_denum()) + (droite_cst.get_num() * gauche_cst.get_denum());
    int res_denum = droite_cst.get_denum() * gauche_cst.get_denum();
    
    /* On crée une instance d'un Cst qu'on simplifie */
    Cst res(res_num, res_denum);

    /* On renvoie ce resultat simplifier */
    return (res.simplifie());
}
#pragma endregion Add

/* Classe Mul */
#pragma region Mul
/* Constructeur qui initialise la multiplication g * d (cree une copie profonde de g et d)*/
Mul::Mul(const ExprArith& g, const ExprArith& d){
    gauche = g.clone();
    droite = d.clone();
}

/* Affiche un Mul sous forme (gauche * droite) */
void Mul::affiche() const {
    cout << "(";
    gauche->affiche();  // Affiche le côté gauche
    cout << " * ";
    droite->affiche();  // Affiche le côté droit
    cout << ")";
}

/* Méthode de simplification */
Cst Mul::simplifie(){
    /* on simplifie a gauche et a droite */
    Cst gauche_cst = gauche->simplifie();
    Cst droite_cst = droite->simplifie();

    /* On calcul le resultat de l'opération */
    int res_num = gauche_cst.get_num() * droite_cst.get_num();
    int res_denum = droite_cst.get_denum() * gauche_cst.get_denum();
    
    /* On crée une instance d'un Cst qu'on simplifie */
    Cst res(res_num, res_denum);

    /* On renvoie ce resultat simplifié */
    return (res.simplifie());
}
#pragma endregion Mul

/* Classe Div */
#pragma region Div
/* Constructeur qui initialise la division g * d (cree une copie profonde de g et d)*/
Div::Div(const ExprArith& g, const ExprArith& d){
    gauche = g.clone();
    droite = d.clone();
}

/* Affiche un Div sous forme (gauche * droite) */
void Div::affiche() const {
    cout << "( ";
    cout << "(";
    gauche->affiche();  // Affiche le côté gauche
    cout << ")";
    cout << " / ";
    cout << "(";
    droite->affiche();  // Affiche le côté droit
    cout << ")";
    cout << " )";
}

/* Méthode de simplification */
Cst Div::simplifie(){
    /* on simplifie a gauche et a droite */
    Cst gauche_cst = gauche->simplifie();
    Cst droite_cst = droite->simplifie();

    /* On calcul le resultat de l'opération */
    int res_num = gauche_cst.get_num() * droite_cst.get_denum();
    int res_denum = droite_cst.get_num() * gauche_cst.get_denum();
    
    /* On crée une instance d'un Cst qu'on simplifie */
    Cst res(res_num, res_denum);

    /* On renvoie ce resultat simplifié */
    return (res.simplifie());
}
#pragma endregion Div

/* Classe Sub */
#pragma region Sub
/* Constructeur qui initialise la soustraction g * d (cree une copie profonde de g et d)*/
Sub::Sub(const ExprArith& g, const ExprArith& d){
    gauche = g.clone();
    droite = d.clone();
}

/* Affiche un Sub sous forme (gauche * droite) */
void Sub::affiche() const {
    cout << "(";
    gauche->affiche();  // Affiche le côté gauche
    cout << " - ";
    droite->affiche();  // Affiche le côté droit
    cout << ")";
}

/* Méthode de simplification */
Cst Sub::simplifie(){
    /* on simplifie a gauche et a droite */
    Cst gauche_cst = gauche->simplifie();
    Cst droite_cst = droite->simplifie();

    /* On calcul le resultat de l'opération */
    int res_num = (gauche_cst.get_num() * droite_cst.get_denum()) - (droite_cst.get_num() * gauche_cst.get_denum());
    int res_denum = droite_cst.get_denum() * gauche_cst.get_denum();
    
    /* On crée une instance d'un Cst qu'on simplifie */
    Cst res(res_num, res_denum);

    /* On renvoie ce resultat simplifié */
    return (res.simplifie());
}
#pragma endregion Sub

/* Classe Neg */
#pragma region Neg
/* Constructeur qui initialise la negation g (cree une copie profonde de g) */
Neg::Neg(const ExprArith& g){
    gauche = g.clone();
}

/* Affiche un Sub sous forme (gauche * droite) */
void Neg::affiche() const {
    cout << " - ";
    cout << "(";
    gauche->affiche();  // Affiche le côté gauche
    cout << ")";
}

/* Méthode de simplification */
Cst Neg::simplifie(){
    /* on simplifie a gauche et a droite */
    Cst gauche_cst = gauche->simplifie();

    /* On crée une instance d'un Cst qu'on simplifie */
    Cst res(-gauche_cst.get_num(), gauche_cst.get_denum());

    /* On renvoie ce resultat simplifié */
    return (res.simplifie());
}
#pragma endregion Neg

