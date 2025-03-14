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
typedef enum Unary_op_t { Neg , Sqrt , Ln , Exp, Sin, Cos}Unary_op_t;

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

* Remarque : 
    - CstInt, CstSymb, Null et Var sont des feuilles de l'arbre d'expression.
    - Unary_op_t aura un seul fils dans l'arbre qui sera à gauche.
    - Binary_op_t aura deux fils dans l'arbre.

*/
typedef enum Nature_t { CstInt , CstSymb , Var , Unary_op, Binary_op }Nature_t;


/*
* C'est une union qui représente la valeur d'une partie d'expression mathématique.
* Elle est utilisée pour stocker la valeur d'une expression.
* Ici, on a 6 types de valeurs :
    - intValue    : valeur d'une constante entière
    - charValue   : valeur d'une variable
    - cstValue    : valeur d'une constante symbolique
    - unaryOpValue: valeur d'une opération unaire
    - binaryOpValue: valeur d'une opération binaire
    - nullValue   : valeur null
*/
union Value {
    int intValue;
    char charValue;
    CstSymb_t cstValue;
    Unary_op_t unaryOpValue;
    Binary_op_t binaryOpValue;
    bool nullValue;
    };



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
    - value : Value de soit un int (pour CstInt), un char pour(Var), un CstSymb , un Unary_op_t, un Binary_op_t ou le booléen qui est vrais si pas de valeur
*/
class Expr {
public:

/***************************/
/****** Constructeurs ******/
/***************************/

    // Constructeur par défaut cree une Expr(0)
    Expr();

    // Constructeur de constante entière
    Expr(const int n);

    // Constructeur de constante symbolique
    Expr(const string symb);

    // Constructeur de variable come x,a,y... (représenté par un caractère)
    Expr(const char Var);

    // Constructeur pour les opérateur unaire
    Expr(Unary_op_t op, const Expr& gauche);

    // Constructeur pour les opérateur binaire
    Expr(Binary_op_t op, const Expr& gauche, const Expr& droit);

    // Constructeur par copie
    Expr(const Expr& other);

/***************************/
/******* Destructeur *******/
/***************************/

    /*
    * Destructeur : libère la mémoire allouée pour les noeuds de l'arbre.
    * Et libère la mémoire allouée pour les pointeurs gauche et droite.
    */
    ~Expr() { delete gauche; delete droite; }

/************************/
/****** Opérateurs ******/
/************************/

    // Opérateur d'affectation
    Expr& operator=(const Expr& other);

    //opérateur de comparaison d'égalité
    bool operator==(const Expr& droite) const;

    //opérateur de comparaison d'égalité
    bool operator!=(const Expr& droite) const { return !(*this == droite); }

/********************************/
/****** Méthodes publiques ******/
/********************************/

    //méthode qui affiche l'expression
    void affiche() const;

    //méthode qui simplifie l'expression
    void simplifie();

    //méthode qui dérive selon une variable représenter par v.
    void derive(const Expr v);
    
    // modifie l’expression courante en rempla¸cant toutes les occurrences de la variable symbolique var par l’expression exp.
    void subs(const Expr* var, const Expr* exp);

    // Méthode qui evalue l'expression
    double eval() const;

private:
/***************************/
/******** Attributs ********/
/***************************/
        Nature_t nature;
        int nb_fils;
        Expr* gauche;
        Expr* droite;
        
        //soit un int, un char, un CstSymb, un Unary_op_t, un Binary_op_t ou un bool null
        Value value;
    
/**************************************/
/* Méthodes privées de la classe Expr */
/**************************************/


    
    // Méthode qui retourne la constante symbolique en string
    string get_cst_symb_str() const;

    // Méthode qui retourne l'opérateur unaire en string
    string get_unary_op_str() const;

    // Méthode qui retourne l'opérateur binaire en string
    string get_binary_op_str() const;

    // Méthode qui simplifie un expression unaire
    void simplifie_unary();

    // Méthode qui simplifie un expression binaire
    void simplifie_binary();

    // Méthode qui dérive une expression unaire
    void derive_unary(const Expr v);

    // Méthode qui dérive une expression binaire
    void derive_binary(const Expr v);

    // Méthode qui renvoie la valeur flottante d'une constante symbolique
    double eval_symb() const;

    // Méthode qui renvoie la valeur flottante d'une expression unaire
    double eval_unary() const;

    // Méthode qui renvoie la valeur flottante d'une expression binaire
    double eval_binary() const;

};

#endif