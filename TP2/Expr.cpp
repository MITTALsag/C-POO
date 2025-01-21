#include <iostream>
#include <string>
#include <cassert>
#include "Expr.hpp"

/*================================================================================================================#*/
/***************************/
/****** Constructeurs ******/
/***************************/

// Constructeur par défaut
Expr::Expr() : nature(Null), nb_fils(0), gauche(nullptr), droite(nullptr), value(nullptr) {}

// Constructeur de constante entière
Expr::Expr(const int n) : nature(CstInt), nb_fils(0), gauche(nullptr), droite(nullptr), value(n) {}

// Constructeur de constante symbolique
Expr::Expr(const string symb) : nature(CstSymb), nb_fils(0), gauche(nullptr), droite(nullptr), value(symb) {}

// Constructeur de variable come x,a,y... (représenté par un caractère)
Expr::Expr(const char c) : nature(Var), nb_fils(0), gauche(nullptr), droite(nullptr), value(c) {}

// Constructeur pour les opérateur unaire
Expr::Expr(Unary_op_t op, Expr& fils_gauche) : nature(Unary_op), nb_fils(1), droite(nullptr), value(op)
{
    gauche = &fils_gauche;
}

// Constructeur pour les opérateur binaire
Expr::Expr(Binary_op_t op, Expr& fils_gauche, Expr& fils_droit) : nature(Binary_op), nb_fils(2), value(op)
{
    gauche = &fils_gauche;
    droite = &fils_droit;
}


/*================================================================================================================#*/
/********************************/
/****** Méthodes publiques ******/
/********************************/


//méthode qui affiche l'expression (tête de la méthode récursive)
void Expr::affiche() const
{
    cout << "(";
    affiche_rec();
    cout << ")";
}


/*================================================================================================================#*/
/**************************************/
/* Méthodes privées de la classe Expr */
/**************************************/

Nature_t Expr::get_Nature() const
{
    return nature;
}

int Expr::get_nb_fils() const
{
    return nb_fils;
}

// Fonction qui affiche les opérateurs unaires et binaires
void Expr::affiche_unary_op(Unary_op_t op) const 
{
    switch (op)
    {
    case Sqrt:
        cout << "sqrt";
        break;
    case Sin:
        cout << "sin";
        break;
    case Cos:
        cout << "cos";
        break;
    case Tan:
        cout << "tan";
        break;
    case Log:
        cout << "log";
        break;
    case Exp:
        cout << "exp";
        break;
    default:
        break;
    }
}

// Fonction qui affiche les opérateurs binaires
void Expr::affiche_binary_op(Binary_op_t op) const
{
    switch (op)
    {
    case Add:
        cout << "+";
        break;
    case Sub:
        cout << "-";
        break;
    case Mul:
        cout << "*";
        break;
    case Div:
        cout << "/";
        break;
    case Pow:
        cout << "^";
        break;
    default:
        break;
    }
}

//méthode qui affiche l'expression (corps de la méthode récursive)
void Expr::affiche_rec() const
{   assert(nature != Null);
    
    switch (nature)
    {
    case CstInt:
        cout << std::get<int>(value);  // Récupère la valeur entière
        break;
    case CstSymb:
        cout << std::get<string>(value);  // Récupère la valeur symbolique
        break;
    case Var:
        cout << std::get<char>(value);  // Récupère la valeur de la variable
        break;
    case Unary_op:
        {
            Unary_op_t op = std::get<Unary_op_t>(value);
            // Affiche l'opérateur, ici vous pouvez définir les opérateurs unaires sous forme de chaînes de caractères
            affiche_unary_op(op);
            cout << "(";
            gauche->affiche_rec();  // Affiche l'expression gauche
            cout << ")";
            break;
        }
    case Binary_op:
        {
            Binary_op_t op = std::get<Binary_op_t>(value);
            // Affiche l'opérateur, ici vous pouvez définir les opérateurs binaires sous forme de chaînes de caractères

            gauche->affiche_rec();  // Affiche l'expression gauche
            cout << " ";
            affiche_binary_op(op);
            cout << " ";
            droite->affiche_rec();  // Affiche l'expression droite
            break;
        }
    default:
        break;
    }
}