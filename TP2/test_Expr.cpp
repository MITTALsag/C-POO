#include <iostream>
#include "Expr.hpp"
void test_operateur_binaire() {
    struct Test {
        Binary_op_t op;
        Expr left_value;
        Expr right_value;
        bool expect_simplified;
        Expr simplified_value;
    };

    Test tests[] = {
        {Add, Expr(2), Expr(3), true, Expr(5)},

    };

    bool all_passed = true;

    for (const auto& test : tests) {
        try {
            // Crée les opérandes sous forme de constantes entières
            Expr left(test.left_value);
            Expr right(test.right_value);

            // Crée l'expression binaire
            Expr expr(test.op, left, right);


            // Vérifie que la nature et l'opérateur sont corrects
            if (expr.get_nature() != Binary_op || expr.get_binary_op_value() != test.op) {
                cout << "Échec (nature ou opérateur) pour l'opérateur : " << test.op << endl;
                all_passed = false;
                continue;
            }

            // Simplification si attendue
            if (test.expect_simplified) {
                expr.simplifie();
                if (expr.get_nature() != CstInt || expr.get_cst_value() != test.simplified_value) {
                    cout << "Échec (simplification) pour l'opérateur : " << test.op
                         << " avec les opérandes : " << test.left_value << " et " << test.right_value << endl;
                    cout << "Résultat obtenu : " << expr.get_int_value() << endl;
                    all_passed = false;
                }
            }
        } catch (const exception& e) {
            // Si une exception est attendue (division par zéro par exemple)
            if (test.expect_simplified == false) {
                cout << "Exception attendue pour l'opérateur : " << test.op
                     << " avec les opérandes : " << test.left_value << " et " << test.right_value
                     << " (" << e.what() << ")" << endl;
            } else {
                cout << "Exception inattendue pour l'opérateur : " << test.op
                     << " avec les opérandes : " << test.left_value << " et " << test.right_value
                     << " (" << e.what() << ")" << endl;
                all_passed = false;
            }
        }
    }

    if (all_passed) {
        cout << "Réussi: test_operateur_binaire" << endl;
    } else {
        cout << "Échec: test_operateur_binaire" << endl;
    }
}


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

    return 0;
}