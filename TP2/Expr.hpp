#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include <string>
using namespace std;


/*
* C'est une classe qui représente les opérations mathématiques unaires.
* Ici, on a 3 types d'opérations unaires :
    - Neg  : changement de signe
    - Sqrt : racine carrée
    - Ln   : logarithme népérien
*/
typedef enum Unary_op_t { Neg , Sqrt , Ln }Unary_op_t;

/*
* C'est une classe qui représente les opérations mathématiques binaires.
* Ici, on a 4 types d'opérations binaires :
    - Add : addition
    - Sub : soustraction
    - Mul : multiplication
    - Div : division (l'argument de gauche est le numérateur et l'argument de droite est le dénominateur)
    - Pow : puissance (l'argument de gauche est la base et l'argument de droite est l'exposant)
*/
typedef enum Binary_op_t { Add , Sub , Mul , Div , Pow}Binary_op_t;


/*
* C'est une classe qui représente les constantes symboliques.
* Ici, on a 3 types de constantes symboliques :
    - Pi : nombre pi
    - E  : nombre e
    - I  : nombre i
*/
typedef enum CstSymb_t { pi , e , i }CstSymb_t;


/*
* C'est une classe qui représente la nature d'une partie d'expression mathématique.
* Ici, on a 6 types de nature :
    - CstInt      : représentant tout nombre rationnel (sera représenter par un int)
    - CstSymb     : représentant tout nombre symbolique comme pi, e, i... (sera représenter par un CstSymb_t)
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
* Il y a 3 types d'expressions mathématiques :
    - Constante : une constante entière ou symbolique
    - Variable  : une variable
    - Opération : une opération unaire ou binaire

* Il y a 5 attributs pour cette classe :
    - nature : la nature de l'expression (voir Nature_t)
    - nb_fils : le nombre de fils de l'expression
    - gauche : pointeur vers le fils gauche de l'expression
    - droite : pointeur vers le fils droit de l'expression
    - value : un union de soit un int (pour CstInt), un char pour(Var), un CstSymb , un Unary_op_t, un Binary_op_t ou le booléen qui est vrais si pas de valeur
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


/************************/
/****** Opérateurs ******/
/************************/

    // Opérateur d'affectation
    Expr& operator=(const Expr& other);

    //opérateur de comparaison d'égalité
    bool operator==(Expr& droite) const;

/********************************/
/****** Méthodes publiques ******/
/********************************/

    //méthode qui affiche l'expression
    void affiche() const;

    //méthode qui simplifie l'expression
    void simplifie();

/**********************************/
/*********** Accesseurs ***********/
/**********************************/

    //Méthode qui retourne la nature de l'expression
    Nature_t get_nature() const { return nature; }

    // Méthode qui retourne la valeur entière de l'expression
    int get_int_value() const { return value.intValue; }

    // Méthode qui retourne la valeur de la variable
    char get_char_value() const { return value.charValue; }

    // Méthode qui retourne la valeur de la constante symbolique
    CstSymb_t get_cst_value() const { return value.cstValue; }

    // Méthode qui retourne l'opérateur unaire
    Unary_op_t get_unary_op_value() const { return value.unaryOpValue; }

    // Méthode qui retourne l'opérateur binaire
    Binary_op_t get_binary_op_value() const { return value.binaryOpValue; }

private:
/***************************/
/******** Attributs ********/
/***************************/
        Nature_t nature;
        int nb_fils;
        Expr* gauche;
        Expr* droite;
        
        //soit un int, un char, un CstSymb, un Unary_op_t, un Binary_op_t ou un bool null
        union Value {
        int intValue;
        char charValue;
        CstSymb_t cstValue;
        Unary_op_t unaryOpValue;
        Binary_op_t binaryOpValue;
        bool nullValue;
    } value;
    
/**************************************/
/* Méthodes privées de la classe Expr */
/**************************************/


    
    // Méthode qui retourne la constante symbolique en string
    string get_cst_symb_str() const;

    // Méthode qui retourne l'opérateur unaire en string
    string get_unary_op_str() const;

    // Méthode qui retourne l'opérateur binaire en string
    string get_binary_op_str() const;

    // Méthode qui vérifie l'égalité entre deux noeud de l'arbre
    bool verif_egalite(const Expr* e1, const Expr* e2) const;

    // Méthode qui simplifie un expression unaire
    void simplifie_unary();

    // Méthode qui simplifie un expression binaire
    void simplifie_binary();
};

#endif