#include <iostream>
#include <string>
#include <cassert>
#include <numeric>
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
        value.cstValue = pi;
    else if (symb == "e" || symb == "E")
        value.cstValue = e;
    else if (symb == "i" || symb == "I")
        value.cstValue = i;
    else
    {
        throw invalid_argument("Erreur (Expr(const string) : La constante symbolique n'est pas reconnue");
    }
}

// Constructeur de variable come x,a,y... (représenté par un caractère)
Expr::Expr(const char c) : nature(Var), nb_fils(0), gauche(nullptr), droite(nullptr)
{
    // On affecte la valeur de la variable à la valeur de l'expression
    value.charValue = c;
}

// Constructeur pour les opérateur unaire
Expr::Expr(Unary_op_t op, const Expr& fils_gauche) : nature(Unary_op), nb_fils(1), droite(nullptr)
{
    // On affecte l'opérateur unaire à la valeur de l'expression
    value.unaryOpValue = op;
    // On copie l'expression gauche à l'expression
    gauche = new Expr(fils_gauche);
}

// Constructeur pour les opérateur binaire
Expr::Expr(Binary_op_t op, const Expr& fils_gauche, const Expr& fils_droit) : nature(Binary_op), nb_fils(2)
{
    // On affecte l'opérateur binaire à la valeur de l'expression
    value.binaryOpValue = op;
    // On copie l'expression gauche à l'expression
    gauche = new Expr(fils_gauche);
    // On copie l'expression droite à l'expression
    droite = new Expr(fils_droit);
}

// Constructeur par copie recursive
Expr::Expr(const Expr& other)
{
    //Copie des attributs simples
    nature = other.nature;
    nb_fils = other.nb_fils;

    //Copie de l'union
    switch (nature)
    {
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
    case Null:
        value.nullValue = other.value.nullValue;
        break;
    default:
        throw invalid_argument("Erreur (constructeur par copie) : L'expression n'est pas reconnue");
        break;
    }

    //Copie profonde des pointeurs 
    if (other.gauche != nullptr)
        gauche = new Expr(*(other.gauche));
    else
        gauche = nullptr;
    
    if (other.droite != nullptr)
        droite = new Expr(*(other.droite));
    else
        droite = nullptr;

}

/*================================================================================================================#*/
/************************/
/****** Opérateurs ******/
/************************/

//Opérateur d'affectation recursive
Expr& Expr::operator=(const Expr& other) {
    if (this != &other) { // Eviter l'auto-assignation

        // Copie des attributs simples
        nature = other.nature;
        nb_fils = other.nb_fils;

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
            case Null:
                value.nullValue = other.value.nullValue;
                break;
            default:
                throw invalid_argument("Erreur (operator=) : L'expression n'est pas reconnue");
                break;
        }

        // Copie profonde des pointeurs si ils ne sont pas nuls
        // dans des variable temporaire
        Expr* tmp_gauche = nullptr;
        Expr* tmp_droite = nullptr;
        if (other.gauche != nullptr)
            tmp_gauche = new Expr(*(other.gauche));

        if (other.droite != nullptr)
            tmp_droite = new Expr(*(other.droite));


        // Libération de la mémoire des pointeurs gauche et droite
        delete this->gauche;
        delete this->droite;

        // mise des nouveau fils dans gauche et droite 
        gauche = tmp_gauche;
        droite = tmp_droite;

    }
        
    return *this; // Retourne l'objet courant pour permettre les chaines d'affectation
}

/*
* opérateur de comparaison d'égalité
* test si deux expressions sont égales
*  Elles sont égale si l'arbre dont this qui est la racine de l'expression gauche et other qui est la racine de l'expression droite sont égaux
* C'est une fonction récursive qui tests l'égalité des deux arbre gauche et droite
*/
bool Expr::operator==(const Expr& droite) const
{
    // on verifie les attributs du neud courant et si ils sont différents alors les expressions sont différentes
    if (!verif_egalite(this, &droite))
        return false;

    // on verifie les fils gauche
    bool res1 = false;
    // si les deux fils gauche sont non nuls
    if (this->gauche && droite.gauche) {
        // on teste l'égalité des deux fils gauche avec un appel récursif
        res1 = *(this->gauche) == *(droite.gauche);
    } 
    // si les deux fils gauche sont nuls alors ils sont égaux
    else if (!this->gauche && !droite.gauche) {
        // si les deux fils gauche sont nuls alors ils sont égaux
        res1 = true;
    }

    // on verifie les fils droit
    bool res2 = false;
    // si les deux fils droit sont non nuls
    if (this->droite && droite.droite) {
        // on teste l'égalité des deux fils droit avec un appel récursif
        res2 = *(this->droite) == *(droite.droite);
    } 
    // si les deux fils droit sont nuls alors ils sont égaux
    else if (!this->droite && !droite.droite) {
        res2 = true;
    }

    return res1 && res2;
}


/*================================================================================================================#*/
/**********************************/
/*********** Accesseurs ***********/
/**********************************/

//Méthode qui retourne la valeur du noeud courant
Value Expr::get_value() const {
    return value;
}

//Méthode qui retourne la valeur de l'expression du noeud gauche
Value Expr::get_value_left_child() const {
    if (gauche != nullptr)
        return gauche->get_value();
    else
        throw invalid_argument("Erreur (get_value_left_child) : L'expression gauche est nulle");
}

//Méthode qui retourne la valeur de l'expression du noeud droit
Value Expr::get_value_right_child() const {
    if (droite != nullptr)
        return droite->get_value();
    else
        throw invalid_argument("Erreur (get_value_right_child) : L'expression droite est nulle");
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
        cout << value.intValue;  // Affiche la valeur entière
        break;
    case Var:
        cout << value.charValue;  // Affiche la valeur de la variable
        break;
    case CstSymb:
        cout << get_cst_symb_str();  // Affiche la valeur de la constante symbolique
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
        throw invalid_argument("Erreur (affiche) : L'expression n'est pas reconnue");
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
        simplifie_binary();
        break;
    case CstInt:
    case CstSymb:
    case Var:
        break;
    default:
        throw invalid_argument("Erreur (simplifie) : L'expression n'est pas reconnue");
        break;
    }
}


//méthode qui dérive selon une variable représenter par v.
void Expr::derive(const Expr v)
{
    /* Vérification que v est une variable */
    if (v.nature != Var)
    {
        throw invalid_argument("Erreur (derive) : l'argument n'est pas une variable");
    }

    /* On parcours l'expression a deriver */
    switch(nature)
    {
    /* Si c'est une constante entière ou une constante symbolique, la dérivé est 0 */
    case CstInt:
    case CstSymb:
        *this = Expr(0);
        break;
    /* Si c'est une variable, la dérivé est 1 si c'est la variable de dérivation et 0 sinon */
    case Var:
        if (value.charValue == v.value.charValue)
            *this = Expr(1);
        else
            *this = Expr(0);
        break;
    /* Si c'est une opération unaire on applique les formule de dérivation */
    case Unary_op:
        this->derive_unary(v);
        break;
    /* Si c'est une opération bianire on applique les formule de dérivation */
    case Binary_op:
        this->derive_binary(v);
        break;
    default:
        throw invalid_argument("Erreur (derive) : L'expression n'est pas reconnue");
        break;
    }

}

/*================================================================================================================#*/
/**************************************/
/* Méthodes privées de la classe Expr */
/**************************************/


// Fonction qui affiche les constantes symboliques
string Expr::get_cst_symb_str() const
{
    CstSymb_t cst = value.cstValue;
    switch (cst)
    {
    case pi:
        return "pi";
        break;
    case e:
        return "e";
        break;
    case i:
        return "i";
        break;
    default:
        throw invalid_argument("Erreur (get_cst_symb_str) : La constante symbolique n'est pas reconnue");
        break;
    }
}


// Fonction qui affiche les opérateurs unaires
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
    case Exp:
        return "exp";
        break;
    case Cos:
        return "cos";
        break;
    case Sin:
        return "sin";
        break;
    default:
        throw invalid_argument("Erreur (get_unary_op_str) : L'opérateur unaire n'est pas reconnu");
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
    case Pow:
        return "^";
        break;
    default:
        throw invalid_argument("Erreur (get_binary_op_str) : L'opérateur binaire n'est pas reconnu");
        break;
    }
}

// Méthode qui vérifie l'égalité entre deux noeud de l'arbre
bool Expr::verif_egalite(const Expr* e1, const Expr* e2) const {
    if (!e1 && !e2) return true;  // Les deux pointeurs sont nuls
    if (!e1 || !e2) return false; // Un seul pointeur est nul

    if (e1->nature != e2->nature || e1->nb_fils != e2->nb_fils)
        return false;

    switch (e1->nature) {
    case CstInt:
        return e1->value.intValue == e2->value.intValue;
    case CstSymb:
        return e1->value.cstValue == e2->value.cstValue;
    case Var:
        return e1->value.charValue == e2->value.charValue;
    case Unary_op:
        return e1->value.unaryOpValue == e2->value.unaryOpValue;
    case Binary_op:
        return e1->value.binaryOpValue == e2->value.binaryOpValue;
    default:
        throw invalid_argument("Erreur (verif_egalite) : L'expression n'est pas reconnue");
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
        //si l'expression gauche est une constante entiere
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
        //si l'expression de gauche est une opertion unaire
        else if (gauche->nature == Unary_op)
        {
            //si l'expression de gauche est une opération Neg
            if (gauche->value.unaryOpValue == Neg)
            {
                //on remplace l'expression par l'expression de gauche
                *this = *(gauche->gauche);
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
                    throw invalid_argument("Erreur (simplifie_unary) : La racine carrée d'un nombre négatif n'est pas définie");
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
            //si l'expression gauche est une constante entière nulle ou négative
            if (gauche->value.intValue <= 0)
            {
                    //Erreur : la racine carrée d'un nombre négatif n'est pas définie
                    throw invalid_argument("Erreur (simplifie_unary) : Le logarithme d'un nombre négatif n'est pas définie");
            }
            //si l'expression gauche est un égal à 1
            else if (gauche->value.intValue == 1)
            {
                //on remplace l'expression par 0
                *this = Expr(0);
            }

        }
        //si l'expression gauche est une constante symbolique
        else if (gauche->nature == CstSymb)
        {
            //si l'expression gauche est un égal à e
            if (gauche->value.cstValue == e)
            {
                //on remplace l'expression par 1
                *this = Expr(1);
            }
        }
        //si l'expression gauche est un operateur unaire
        else if (gauche->nature == Unary_op)
        {
            //si l'expression gauche est un Exp
            if (gauche->value.unaryOpValue == Exp)
            {
                //on remplace l'expression par le fils gauche du Ln
                *this = *(this->gauche->gauche);
            }
        }
        break;
    // Simplification de l'opération Exp (exponentielle)
    case Exp:
        //si l'expression gauche est une constante entière
        if (gauche->nature == CstInt)
        {
            //si l'expression gauche est une constante entière nulle
            if (gauche->value.intValue == 0)
            {
                //on remplace l'expression par 1
                *this = Expr(1);

            }
        }
        //si l'expression gauche est un operateur unaire
        else if (gauche->nature == Unary_op)
        {
            //si l'expression gauche est un Ln
            if (gauche->value.unaryOpValue == Ln)
            {
                //on remplace l'expression par le fils gauche du Ln
                *this = *(this->gauche->gauche);
            }
        }
        break;
        // Simplification de l'opération Cos (cosinus)
        case Cos:
        //si l'expression gauche est une constante entière
        if (gauche->nature == CstInt)
        {
            //si l'expression gauche est une constante entière nulle
            if (gauche->value.intValue == 0)
            {
                //on remplace l'expression par 1
                *this = Expr(1);

            }
        }
        //si l'expression gauche est une constante symbolique
        else if (gauche->nature == CstSymb)
        {
            //si l'expression gauche est un égal à pi
            if (gauche->value.cstValue == pi)
            {
                //on remplace l'expression par -1
                *this = Expr(-1);
            }
        }
        break;
        // Simplification de l'opération Sin (sinus)
        case Sin:
        //si l'expression gauche est une constante entière
        if (gauche->nature == CstInt)
        {
            //si l'expression gauche est une constante entière nulle
            if (gauche->value.intValue == 0)
            {
                //on remplace l'expression par 0
                *this = Expr(0);

            }
        }
        //si l'expression gauche est une constante symbolique
        else if (gauche->nature == CstSymb)
        {
            //si l'expression gauche est un égal à pi
            if (gauche->value.cstValue == pi)
            {
                //on remplace l'expression par 0
                *this = Expr(0);
            }
        }
        break;
    default:
        throw invalid_argument("Erreur (simplifie_unary) : L'opérateur unaire n'est pas reconnu");
        break;

    }
}

// Méthode qui simplifie un expression binaire
void Expr::simplifie_binary()
{
    Binary_op_t op = value.binaryOpValue;
    switch (op)
    {
    // Simplification de l'opération Add (addition)
    case Add:
        //si l'expression gauche et droite sont des constantes entières
        if (gauche->nature == CstInt && droite->nature == CstInt)
        {
            //on les additionne
            *this = Expr(gauche->value.intValue + droite->value.intValue);
        }
        // si gauche est egale a 0 (et que droite n'est pas une CstInt)
        else if (gauche->nature == CstInt && gauche->value.intValue == 0)
        {
            //on remplace l'expression par la droite
            *this = *droite;
        }
        //si droite est egal à 0 (et que droite n'est pas une CstInt)
        else if (droite->nature == CstInt && droite->value.intValue == 0)
        {
            //on remplace l'expression par la gauche
            *this = *gauche;
        }
        break;
    // Simplification de l'opération Sub (soustraction)
    case Sub:
        //si l'expression gauche et droite sont des constantes entières
        if (gauche->nature == CstInt && droite->nature == CstInt)
        {
            //on les soustrait
            *this = Expr(gauche->value.intValue - droite->value.intValue);
        }
        // si gauche est egale a 0 (et que droite n'est pas une CstInt)
        else if (gauche->nature == CstInt && gauche->value.intValue == 0)
        {
            //on remplace l'expression par Neg(droite)
            *this = Expr(Neg, *droite);
        }
        //si droite est egal à 0 (et que droite n'est pas une CstInt)
        else if (droite->nature == CstInt && droite->value.intValue == 0)
        {
            //on remplace l'expression par la gauche
            *this = *gauche;
        }
        break;
    // Simplification de l'opération Mul (multiplication)
    case Mul:
        // si une des deux opérandes est egale a 0 on remplace l'expression par 0
        if ((gauche->nature == CstInt && gauche->value.intValue == 0) || (droite->nature == CstInt && droite->value.intValue == 0))
        {
            //on remplace l'expression par 0
            *this = Expr(0);
        }
        // si gauche est egale a 1
        else if (gauche->nature == CstInt && gauche->value.intValue == 1)
        {
            //on remplace l'expression par la droite
            *this = *droite;
        }
        //si droite est egal à 1
        else if (droite->nature == CstInt && droite->value.intValue == 1)
        {
            //on remplace l'expression par la gauche
            *this = *gauche;
        }
        //si l'expression gauche et droite sont des constantes entières
        else if (gauche->nature == CstInt && droite->nature == CstInt)
        {
            //on les multiplie
            *this = Expr(gauche->value.intValue * droite->value.intValue);
        }
        break;

    // Simplification de l'opération Div (division)
    case Div:
        //si l'expression de droite est nulle on renvoie une erreur
        if (droite->nature == CstInt && droite->value.intValue == 0)
        {
            throw invalid_argument("Erreur (simplifie_binary) : Division par zéro");
        }
        //si l'expression gauche est une constante entière nulle
        else if (gauche->nature == CstInt && gauche->value.intValue == 0)
        {
            //on remplace l'expression par 0
            *this = Expr(0);
        }
        //si l'expression gauche et droite sont des constantes entières
        else if (gauche->nature == CstInt && droite->nature == CstInt)
        {   
            //si l'expression le denominateur est négatif on multiplie le numérateur et le dénominateur par -1
            if (droite->value.intValue < 0)
            {
                gauche->value.intValue *= -1;
                droite->value.intValue *= -1;
            }

            //on clacul le pgcd de l'expression gauche et droite pour simplifier l'expression si c'est possible
            int pgcd = gcd(gauche->value.intValue, droite->value.intValue);
            //on divise l'expression gauche et droite par le pgcd
            gauche->value.intValue /= pgcd;
            droite->value.intValue /= pgcd;

            //si l'expression au dénominateur est égale à 1
            if (droite->value.intValue == 1)
            {
                *this = *gauche;
            }
        }
        //si l'expression au numérateur est egale à l'expression au dénominateur
        else if(gauche == droite)
        {
            //on remplace l'expression par 1
            *this = Expr(1);
        }
        break;
    case Pow:
        //si l'expression gauche et droite sont des constantes entières
        if (gauche->nature == CstInt && droite->nature == CstInt)
        {
            //on calcule la puissance
            *this = Expr(static_cast<int> (pow(gauche->value.intValue, droite->value.intValue)));
        }
        //si la puissant est egal a 1 on remplace par la base 
        else if (droite->nature == CstInt && droite->value.intValue == 1)
        {
            //on remplace par la base 
            *this = *gauche;
        }
        //si la puissant est egal a 0 on remplace par 1
        else if (droite->nature == CstInt && droite->value.intValue == 0)
        {
            //on remplace par la base 
            *this = Expr(0);
        }
        break;
    default:
        throw invalid_argument("Erreur (simplifie_binary) : L'opérateur binaire n'est pas reconnu");
        break;

    }
}


// Méthode qui dérive une expression unaire
void Expr::derive_unary(const Expr v)
{
    /* verifaication que v est une variable et que *this est une expression unaire */
    if (v.nature != Var)
        throw invalid_argument("Erreur (derive_unary) : l'argument n'est pas une variable");
    if (this->nature != Unary_op)
        throw invalid_argument("Erreur (derive_unary) : this n'est pas une expression unaire");
    

    Expr f_prime;
    Expr sqrt_f;
    Expr f;
    Expr exp_f;
    Expr cos_f;
    Expr sin_f;
    Expr neg_sin_f;

    /* On regarde quelle expression unaire c'est */
    switch(value.unaryOpValue)
    {
    /* (-f)' = -(f') donc on dérive le fils gauche */
    case Neg:
        gauche->derive(v);
        break;

    /* (sqrt(f))' = f'/(2*sqrt(f)) */
    case Sqrt:
        // Copie (profonde) de f(x) appelle a operator=
        f_prime = *gauche;
        // Calcul de f'(x)
        f_prime.derive(v);  
        
        // Copie (profonde) de l'expression sqrt(f(x))
        sqrt_f = *this;    
        
        // Réalisation de la dérivée de sqrt(f(x)): f'(x) / (2 * sqrt(f(x)))
        *this = Expr(Div, f_prime, Expr(Mul, Expr(2), sqrt_f));
        break;

    /* (Ln(f))' = f'/f */
    case Ln:
        // Copie (profonde) de f(x) appelle a operator=
        f_prime = *gauche;
        // Calcul de f'(x)
        f_prime.derive(v);  
        
        // Copie (profonde) de l'expression f(x)
        f = *gauche;
        
        // Réalisation de la dérivée de ln(f(x)): f'(x) / f(x)
        *this = Expr(Div, f_prime, f);
        break;
    
    /* 'Exp(f))' = f' * Exp(f) */
    case Exp:
        // Copie (profonde) de f(x) appelle a operator=
        f_prime = *gauche;
        // Calcul de f'(x)
        f_prime.derive(v);  
        
        // Réalisation de la dérivée de exp(f(x)): exp(f(x)) * f'(x)
        exp_f = *this;  // Copie (profonde) de exp(f(x))
        *this = Expr(Mul, exp_f, f_prime);
        break;
    
    /* (sin(f))' = f' * cos(f) */
    case Sin:
        // Copie (profonde) de f(x) appelle a operator=
        f_prime = *gauche;
        // Calcul de f'(x)
        f_prime.derive(v);  
        
        // Réalisation de la dérivée de sin(f(x)): cos(f(x)) * f'(x)
        cos_f = Expr(Cos, *gauche);  // Crée cos(f(x))
        *this = Expr(Mul, cos_f, f_prime);
        break;

    /* (cos(f))' = -f' * sin(f) */
    case Cos:
        // Copie (profonde) de f(x) appelle a operator=
        f_prime = *gauche;
        // Calcul de f'(x)
        f_prime.derive(v);  
        
        // Réalisation de la dérivée de cos(f(x)): -sin(f(x)) * f'(x)
        sin_f = Expr(Sin, *gauche);  // Crée sin(f(x))
        neg_sin_f = Expr(Neg, sin_f); // Crée -sin(f(x))
        *this = Expr(Mul, neg_sin_f, f_prime);
        break;
    }
}

// Méthode qui dérive une expression binaire
void Expr::derive_binary(const Expr v)
{
    /* verifaication que v est une variable et que *this est une expression binaire */
    if (v.nature != Var)
        throw invalid_argument("Erreur (derive_unary) : l'argument n'est pas une variable");
    if (this->nature != Binary_op)
        throw invalid_argument("Erreur (derive_binary) : this n'est pas une expression binaire");
    

    Expr f_prime;
    Expr g_prime;
    Expr f;
    Expr g;

    /* On regarde quelle expression unaire c'est */
    switch(value.binaryOpValue)
    {
    /* (f + g)' = f' + g' donc on dérive les deux fils */
    case Add:
        gauche->derive(v);
        droite->derive(v);
        break;

    /* (f - g)' = f' - g' donc on dérive les deux fils */
    case Sub:
        gauche->derive(v);
        droite->derive(v);
        break;

    /* (f * g)' = f'*g + g'*f */
    case Mul:

        // Copie (profonde) de f et g appelle a operator=
        f = *gauche;
        g = *droite; 

        // Copie (profonde) de f et g (pour deriver apres) appelle a operator=
        f_prime = f;
        g_prime = g;

        // Derivation de f et g 
        f_prime.derive(v);
        g_prime.derive(v);

        *this = Expr(Add, Expr(Mul, f_prime, g), Expr(Mul, g_prime, f));
        break;
    
    /* (f/g)' = (f'*g - g'*f)/g^2 */
    case Div:
        // Copie (profonde) de f et g appelle a operator=
        f = *gauche;
        g = *droite; 

        // Copie (profonde) de f et g (pour deriver apres) appelle a operator=
        f_prime = f;
        g_prime = g;

        // Derivation de f et g 
        f_prime.derive(v);
        g_prime.derive(v);

        *this = Expr(Div, Expr(Sub, Expr(Mul, f_prime, g), Expr(Mul, g_prime, f)), Expr(Pow, g, Expr(2)));

        break;
    /* Le cas (f^n)' = n * f' * f^(n-1) ou n est un entier */
    case Pow:
        if (droite->nature == CstInt)
        {
            // Copie (profonde) de f appelle a operator=
            f = *gauche;
            int n = droite->value.intValue;

            // Copie (profonde) de f (pour deriver apres) appelle a operator=
            f_prime = f;

            // Derivation de f et g 
            f_prime.derive(v);

            *this = (Expr(Mul, Expr(n), Expr(Mul, f_prime, Expr(Pow, f, Expr(n-1)))));
        }
        break;
    }
}
