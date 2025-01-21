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
    //a. simplifie () ;
    a.affiche() ;
    cout << endl ;

    return 0;
}