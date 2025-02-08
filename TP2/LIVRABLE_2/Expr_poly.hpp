#ifndef __EXPR_POLY__
#define __EXPR_POLY__

#include <iostream>
using namespace std;


/* Pour que ExprArith connaise le nom */
class Cst;

/* Classe ExprArith */
#pragma region ExprArith
/*******************************************************************************************/
/*******************************************************************************************/
/*
* C'est une classe abstraite dont vont hérité nos classes d'expression 
*/
class ExprArith{
public:
    /* la fonction affiche() virtuelle pure pour afficher une expression */
    virtual void affiche() const = 0; 
    
    /* la fonction clone() virtuelle pure pour la copie profonde */
    virtual ExprArith* clone() const = 0;  
    
    /* la fonction simplifie virtuelle pur simplifie une expression */
    virtual Cst simplifie() = 0;

    virtual ~ExprArith() {};
};
#pragma endregion ExprArith

/* Classe Cst */
#pragma region Cst
/*******************************************************************************************/
/*******************************************************************************************/
/*
* C'est une classe dérivé de ExprArith qui represente une constante rationnel
* Elle possède deux attributs :
*   - int num et denum qui représente resppectivement le numérateur et le dénominateur d'un rationnel
*/
class Cst : public ExprArith {

private:
    /* Represente le numérateur et le dénominateur */
    int num, denum;

public:
    /* construcetur par défaut : cree le rationnel 0/1 */
    Cst() : num(0), denum(1) {}
    /* Crée le rationnel n/d */
    Cst(int n, int d);
    /* Cree le rationnel n/1 */
    Cst(int n) : num(n), denum(1) {}

    /* Methode pour afficher un rationnel */
    void affiche() const override; 

    /* Accesseurs */
    int get_num() const { return num; }
    int get_denum() const { return denum; }

    /* Méthode de simplification */
    Cst simplifie() override;

    /* Méthode pour renvoyer le clone de l'objet courant */
    ExprArith* clone() const override { return new Cst(this->num, this->denum); }

};
#pragma endregion Cst

/* Classe Add */
#pragma region Add
/*******************************************************************************************/
/*******************************************************************************************/
/*
* C'est une classe dérivé de ExprArith qui represente une addition
* Elle posède deux attributs :
*   - ExprArith * gauche et droit qui sont des pointeurs vers d'autres expression arithmétiques
*/
class Add : public ExprArith {
private:
    ExprArith* gauche;
    ExprArith* droite;

public:
    /* Constructeur qui initialise l'addition g + d (cree une copie profonde de g et d)*/
    Add(const ExprArith& g, const ExprArith& d);

    /* Destructeur */
    ~Add() { delete gauche; delete droite;  }

    /* Methode pour afficher un Add */
    void affiche() const override; 

    /* Méthode de simplification */
    Cst simplifie() override;

    /* Méthode pour renvoyer le clone de l'objet courant */
    ExprArith* clone() const override { return new Add(*gauche, *droite); }

};
#pragma endregion Add

/* Classe Mul */
#pragma region Mul
/*******************************************************************************************/
/*******************************************************************************************/
/*
* C'est une classe dérivé de ExprArith qui represente une multiplication
* Elle posède deux attributs :
*   - ExprArith * gauche et droit qui sont des pointeurs vers d'autres expression arithmétiques
*/
class Mul : public ExprArith {
private:
    ExprArith* gauche;
    ExprArith* droite;

public:
    /* Constructeur qui initialise l'operation g * d (cree une copie profonde de g et d)*/
    Mul(const ExprArith& g, const ExprArith& d);

    /* Destructeur */
    ~Mul() { delete gauche; delete droite;  }

    /* Methode pour afficher un Mul */
    void affiche() const override;

    /* Méthode de simplification */
    Cst simplifie() override;

    /* Méthode pour renvoyer le clone de l'objet courant */
    ExprArith* clone() const override { return new Mul(*gauche, *droite); }

};
#pragma endregion Mul

/* Classe Div */
#pragma region Div
/*******************************************************************************************/
/*******************************************************************************************/
/*
* C'est une classe dérivé de ExprArith qui represente une division
* Elle posède deux attributs :
*   - ExprArith * gauche et droit qui sont des pointeurs vers d'autres expression arithmétiques
*/
class Div : public ExprArith {
private:
    ExprArith* gauche;
    ExprArith* droite;

public:
    /* Constructeur qui initialise l'operation g * d (cree une copie profonde de g et d)*/
    Div(const ExprArith& g, const ExprArith& d);

    /* Destructeur */
    ~Div() { delete gauche; delete droite;  }

    /* Methode pour afficher un Div */
    void affiche() const override;

    /* Méthode de simplification */
    Cst simplifie() override;

    /* Méthode pour renvoyer le clone de l'objet courant */
    ExprArith* clone() const override { return new Div(*gauche, *droite); }

};
#pragma endregion Div

/* Classe Sub */
#pragma region Sub
/*******************************************************************************************/
/*******************************************************************************************/
/*
* C'est une classe dérivé de ExprArith qui represente une soustraction
* Elle posède deux attributs :
*   - ExprArith * gauche et droit qui sont des pointeurs vers d'autres expression arithmétiques
*/
class Sub : public ExprArith {
private:
    ExprArith* gauche;
    ExprArith* droite;

public:
    /* Constructeur qui initialise l'operation g * d (cree une copie profonde de g et d)*/
    Sub(const ExprArith& g, const ExprArith& d);

    /* Destructeur */
    ~Sub() { delete gauche; delete droite;  }

    /* Methode pour afficher un Sub */
    void affiche() const override;

    /* Méthode de simplification */
    Cst simplifie() override;

    /* Méthode pour renvoyer le clone de l'objet courant */
    ExprArith* clone() const override { return new Sub(*gauche, *droite); }

};
#pragma endregion Sub

/* Classe Neg */
#pragma region Neg
/*******************************************************************************************/
/*******************************************************************************************/
/*
* C'est une classe dérivé de ExprArith qui represente une negative
* Elle posède deux attributs :
*   - ExprArith * gauche qui est des pointeurs vers d'autres expression arithmétiques
*/
class Neg : public ExprArith {
private:
    ExprArith* gauche;

public:
    /* Constructeur qui initialise l'operation g (cree une copie profonde de g) */
    Neg(const ExprArith& g);

    /* Destructeur */
    ~Neg() { delete gauche; }

    /* Methode pour afficher un Neg */
    void affiche() const override;

    /* Méthode de simplification */
    Cst simplifie() override;

    /* Méthode pour renvoyer le clone de l'objet courant */
    ExprArith* clone() const override { return new Neg(*gauche); }

};
#pragma endregion Neg

#endif