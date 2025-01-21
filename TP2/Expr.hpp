#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include <string>
#include <variant>
using namespace std;


/*
* C'est une classe qui représente les opérations mathématiques unaires.
* Ici, on a 3 types d'opérations unaires :
    - Neg  : changement de signe
    - Sqrt : racine carrée
    - Ln   : logarithme népérien
*/
typedef enum Unary_op_t { Neg , Sqrt , Ln, Sin, Cos, Tan, Log, Exp }Unary_op_t;

/*
* C'est une classe qui représente les opérations mathématiques binaires.
* Ici, on a 4 types d'opérations binaires :
    - Add : addition
    - Sub : soustraction
    - Mul : multiplication
    - Div : division
*/
typedef enum Binary_op_t { Add , Sub , Mul , Div, Pow }Binary_op_t;


/*
* C'est une classe qui représente la nature d'une partie d'expression mathématique.
* Ici, on a 6 types de nature :
    - CstInt      : représentant tout nombre rationnel (sera représenter par un int)
    - CstSymb     : représentant tout nombre symbolique comme pi, e, i... (sera représenter par un string)
    - Var         : représentant une variable (sera représenter par un char)
    - Unary_op_t  : représentant une opération unaire (sera représenter par un Unary_op_t)
    - Binary_op_t : représentant une opération binaire (sera représenter par un Binary_op_t)
    - Null        : represente la non valeur

* Remarque : 
    - CstInt, CstSymb, Null et Var sont des feuilles de l'arbre d'expression.
    - Unary_op_t aura un seul fils dans l'arbre qui sera à gauche.
    - Binary_op_t aura deux fils dans l'arbre.

*/
typedef enum Nature_t { CstInt , CstSymb , Var , Unary_op, Binary_op, Null }Nature_t;



/*
* C'est une classe qui représente une expression mathématique.
* Une expression sera représentaer par un arbre, où chaque noeud est une expression qui pourra avoir 0, 1 ou 2 fils.
* Une expression sera construite dans le tas via des new et des delete. 
* Il y a 3 types d'expressions mathématiques :
    - Constante : une constante entière ou symbolique
    - Variable  : une variable
    - Opération : une opération unaire ou binaire

* Il y a 5 attributs pour cette classe :
    - nature : la nature de l'expression (voir Nature_t)
    - nb_fils : le nombre de fils de l'expression
    - gauche : pointeur vers le fils gauche de l'expression
    - droite : pointeur vers le fils droit de l'expression
    - value : une union qui contient la valeur de soit un int, un char, un string*, un Unary_op_t*, un Binary_op_t* ou le pointeur null
*/
class Expr {
public:

/***************************/
/****** Constructeurs ******/
/***************************/

    // Constructeur par défaut
    Expr();

    // Constructeur de constante entière
    Expr(const int n);

    // Constructeur de constante symbolique
    Expr(const string symb);

    // Constructeur de variable come x,a,y... (représenté par un caractère)
    Expr(const char Var);

    // Constructeur pour les opérateur unaire
    Expr(Unary_op_t op, Expr& gauche);

    // Constructeur pour les opérateur binaire
    Expr(Binary_op_t op, Expr& gauche, Expr& droit);



/********************************/
/****** Méthodes publiques ******/
/********************************/

    //méthode qui affiche l'expression
    void affiche() const;



private:
/***************************/
/******** Attributs ********/
/***************************/
        Nature_t nature;
        const int nb_fils;
        Expr* gauche;
        Expr* droite;
        
        //soit un int, un char, un string, un Unary_op_t, un Binary_op_t le pointeur null
        variant<int, char, std::string, Unary_op_t, Binary_op_t, void*> value;

    
/**************************************/
/* Méthodes privées de la classe Expr */
/**************************************/
    
    // Méthode qui retourne la nature de l'expression
    Nature_t get_Nature() const;

    // Méthode qui retourne le nombre de fils de l'expression
    int get_nb_fils() const;

    // Fonction qui affiche les opérateurs unaires et binaires
    void affiche_unary_op(Unary_op_t op) const;

    // Fonction qui affiche les opérateurs binaires
    void affiche_binary_op(Binary_op_t op) const;

    //méthode qui affiche l'expression (corps de la méthode récursive)
    void affiche_rec() const;

};

#endif