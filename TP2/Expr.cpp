#include <iostream>
#include <string>
#include <cassert>
#include "Expr.hpp"

/*================================================================================================================#*/
/***************************/
/****** Constructeurs ******/
/***************************/

// Constructeur par défaut
Expr::Expr() : nature(Null), nb_fils(0), gauche(nullptr), droite(nullptr) 
{
    // On affecte la valeur null à l'expression
    value.nullValue = true;
}

// Constructeur de constante entière
Expr::Expr(const int n) : nature(CstInt), nb_fils(0), gauche(nullptr), droite(nullptr)
{   
    // On affecte la valeur de l'entier à la valeur de l'expression
    value.intValue = n;
}

// Constructeur de constante symbolique
Expr::Expr(const string symb) : nature(CstSymb), nb_fils(0), gauche(nullptr), droite(nullptr)
{
    // On affecte la valeur de la constante symbolique à la valeur de l'expression
    if (symb == "pi" || symb == "PI" || symb == "Pi")
        value.cstValue = Pi;
    else if (symb == "e" || symb == "E")
        value.cstValue = E;
    else if (symb == "i" || symb == "I")
        value.cstValue = I;
    else
    {
        throw invalid_argument("La constante symbolique n'est pas reconnue");
    }
}

// Constructeur de variable come x,a,y... (représenté par un caractère)
Expr::Expr(const char c) : nature(Var), nb_fils(0), gauche(nullptr), droite(nullptr)
{
    // On affecte la valeur de la variable à la valeur de l'expression
    value.charValue = c;
}

// Constructeur pour les opérateur unaire
Expr::Expr(Unary_op_t op, Expr& fils_gauche) : nature(Unary_op), nb_fils(1), droite(nullptr)
{
    // On affecte l'opérateur unaire à la valeur de l'expression
    value.unaryOpValue = op;
    // On affecte l'expression gauche à l'expression
    gauche = &fils_gauche;
}

// Constructeur pour les opérateur binaire
Expr::Expr(Binary_op_t op, Expr& fils_gauche, Expr& fils_droit) : nature(Binary_op), nb_fils(2)
{
    // On affecte l'opérateur binaire à la valeur de l'expression
    value.binaryOpValue = op;
    // On affecte l'expression gauche et droite à l'expression
    gauche = &fils_gauche;
    // On affecte l'expression droite à l'expression
    droite = &fils_droit;
}

/*================================================================================================================#*/
/************************/
/****** Opérateurs ******/
/************************/


Expr& Expr::operator=(const Expr& other) {
    if (this != &other) { // Eviter l'auto-assignation

        // Copie des attributs simples
        nature = other.nature;
        nb_fils = other.nb_fils;
        
        // Copie des pointeurs

        gauche = other.gauche; // Si l'expression `other` a un fils gauche, on le copie

        
        droite = other.droite; // Même logique pour droite

        // Copie du `union`
        switch (nature) {
            case CstInt:
                value.intValue = other.value.intValue;
                break;
            case CstSymb:
                value.cstValue = other.value.cstValue;
                break;
            case Var:
                value.charValue = other.value.charValue;
                break;
            case Unary_op:
                value.unaryOpValue = other.value.unaryOpValue;
                break;
            case Binary_op:
                value.binaryOpValue = other.value.binaryOpValue;
                break;
            default:
                break;
        }
    }
    return *this; // Retourne l'objet courant pour permettre les chaines d'affectation
}


/*================================================================================================================#*/
/********************************/
/****** Méthodes publiques ******/
/********************************/


//méthode qui affiche l'expression
void Expr::affiche() const
{   assert(nature != Null);
    
    switch (nature)
    {
    case CstInt:
        cout << value.intValue;  // Récupère la valeur entière
        break;
    case CstSymb:
        cout << get_cst_symb_str();  // Récupère la valeur de la constante symbolique
        break;
    case Var:
        cout << value.charValue;  // Récupère la valeur de la variable
        break;
    case Unary_op:
        {
            // Affiche l'opérateur unaire est l'expression gauche entre parenthèses
            cout << get_unary_op_str() 
                 << "(";
            gauche->affiche();  // Affiche l'expression gauche entre parenthèses
            cout << ")";
            break;
        }
    case Binary_op:
        {
            // Affiche l'expression binaire 
            //si l'expression gauche est une expression binaire, on l'entoure de parenthèses

            if (gauche->nature == Binary_op)
                cout << "(";
            gauche->affiche();  // Affiche l'expression gauche
            if (gauche->nature == Binary_op)
                cout << ")";

            cout << " "
                 << get_binary_op_str()  // Affiche l'opérateur binaire
                 << " ";

            //si l'expression droite est une expression binaire, on l'entoure de parenthèses
            if (droite->nature == Binary_op)
                cout << "(";
            droite->affiche();  // Affiche l'expression droite
            if (droite->nature == Binary_op)
                cout << ")";
            break;
        }
    default:
        break;
    }
}


void Expr::simplifie()
{
    // Parcours en pronfondeur suffixe de l'arbre d'expression
    if (gauche != nullptr)
        gauche->simplifie();
    if (droite != nullptr)
        droite->simplifie();
    switch (nature)
    {
    case Unary_op:
        simplifie_unary();
        break;
    case Binary_op:
        //simplifie_binary();
        break;
    default:
        break;
    }
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
string Expr::get_cst_symb_str() const
{
    CstSymb_t cst = value.cstValue;
    switch (cst)
    {
    case Pi:
        return "pi";
        break;
    case E:
        return "e";
        break;
    case I:
        return "i";
        break;
    default:
        break;
    }
}



string Expr::get_unary_op_str() const 
{
    Unary_op_t op = value.unaryOpValue;
    switch (op)
    {
    case Sqrt:
        return "sqrt";
        break;
    case Neg:
        return "-";
        break;
    case Ln:
        return "ln";
        break;
    default:
        break;
    }
}

// Fonction qui affiche les opérateurs binaires
string Expr::get_binary_op_str() const
{
    Binary_op_t op = value.binaryOpValue;
    switch (op)
    {
    case Add:
        return "+";
        break;
    case Sub:
        return "-";
        break;
    case Mul:
        return "*";
        break;
    case Div:
        return "/";
        break;
    default:
        break;
    }
}

// Méthode qui simplifie un expression unaire
void Expr::simplifie_unary()
{
    Unary_op_t op = value.unaryOpValue;
    switch (op)
    {
    // Simplification de l'opération Neg (négatif)
    case Neg:
        //si l'expression gauche est une constante symbolique
        if (gauche->nature == CstInt )
        {
            //si l'expression gauche est une constante entière non nulle
            if (gauche->value.intValue != 0)
            {
                //on remplace l'expression par son opposé
                *this = Expr(-gauche->value.intValue);
            }
            //si l'expression gauche est une constante entière nulle
            else if (gauche->value.intValue == 0)
            {
                //on remplace l'expression par 0
                *this = Expr(0);
            }
        }
        break;

    // Simplification de l'opération Sqrt (racine carrée)
    case Sqrt:
        //si l'expression gauche est une constante entière
        if (gauche->nature == CstInt)
        {
            //si l'expression gauche est un carre < 0
            if (gauche->value.intValue < 0)
            {
                    //Erreur : la racine carrée d'un nombre négatif n'est pas définie
                    throw invalid_argument("La racine carrée d'un nombre négatif n'est pas définie");
            }
            //si l'expression gauche est une constante entière nulle
            else if (gauche->value.intValue == 0)
            {
                //on remplace l'expression par 0
                *this = Expr(0);
            }
            //si l'expression gauche est un carre parfait (la racine carrée est un entier)
            else if (pow(floor(sqrt(gauche->value.intValue)), 2) == gauche->value.intValue)
            {
                //on remplace l'expression par la racine carrée de la constante entière
                *this = Expr(static_cast<int> (sqrt(gauche->value.intValue)));
            }
        }
        break;

    // Simplification de l'opération Ln (logarithme népérien)
    case Ln:
        //si l'expression gauche est une constante entière
        if (gauche->nature == CstInt)
        {
            //si l'expression gauche est un égal à 1
            if (gauche->value.intValue == 1)
            {
                //on remplace l'expression par 0
                *this = Expr(0);
            }
            //si l'expression gauche est une constante entière nulle
            else if (gauche->value.intValue <= 0)
            {
                    //Erreur : la racine carrée d'un nombre négatif n'est pas définie
                    throw invalid_argument("Le logarithme d'un nombre négatif n'est pas définie");
            }
        }
        //si l'expression gauche est une constante symbolique
        else if (gauche->nature == CstSymb)
        {
            //si l'expression gauche est un égal à e
            if (gauche->value.cstValue == E)
            {
                //on remplace l'expression par 1
                *this = Expr(1);
            }
        }
        break;

    }
}
/*
void Expr::simplifie_binary()
{
    Binary_op_t op = std::get<Binary_op_t>(value);
    switch (op)
    {
        case Add:
            if (gauche->nature == CstInt && std::get<int>(gauche->value) == 0)
            {
                *this = *droite;
            }
            else if (droite->nature == CstInt && std::get<int>(droite->value) == 0)
            {
                *this = *gauche;
            }
            break;
    }
}
*/