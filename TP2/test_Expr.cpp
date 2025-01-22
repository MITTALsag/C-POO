#include <iostream>
#include "Expr.hpp"


int main(void)
{

    Expr x ('x') ;
    Expr deux (2) ;
    Expr neuf (9) ;
    Expr sqneuf (Sqrt , neuf ) ;
    Expr m (Mul , deux , sqneuf ) ;
    Expr a (Add , x, m) ;
    a.affiche() ;
    cout << " = ";
    a.simplifie () ;
    a.affiche() ;
    cout << endl ;

    a = Expr(2);              // 2
    Expr b(3);              // 3
    Expr c(Div, a, b);      // 2 / 3
    Expr d(Mul, c, b);      // (2 / 3) * 3

    d.simplifie();          // Résultat attendu : 2
    d.affiche();            // Doit afficher 2

    return 0;
}