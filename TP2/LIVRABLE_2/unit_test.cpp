#include "Expr_poly.hpp"
#include <iostream>
#include <cassert>
#include <sstream>
#include <vector>

using namespace std;

/* test de l'affichage */
void test_affiche() {
    struct Test {
        ExprArith* exp;                 // La constante
        const char* expected_output;  // La sortie attendue
    };

    Test tests[] = {

        // Tests pour Cst
        {new Cst(5, 3), "5/3"},  // Test avec une constante simple
        {new Cst(2, 7), "2/7"},  // Test avec une autre constante
        {new Cst(10, 1), "10"}, // Test avec une autre constante

        // Tests pour Add
        {new Add(Cst(5, 3), Cst(7, 1)), "(5/3 + 7)"},
        {new Add(Cst(6, 1), Cst(2, 3)), "(6 + 2/3)"},
        
        // Tests pour Mul
        {new Mul(Cst(2, 3), Cst(4, 5)), "(2/3 * 4/5)"},
        {new Mul(Cst(6, 1), Cst(3, 2)), "(6 * 3/2)"},
        
        // Tests pour Sub
        {new Sub(Cst(5, 3), Cst(2, 3)), "(5/3 - 2/3)"},
        {new Sub(Cst(7, 1), Cst(4, 1)), "(7 - 4)"},
        
        // Tests pour Div
        {new Div(Cst(6, 1), Cst(3, 2)), "( (6) / (3/2) )"},
        {new Div(Cst(4, 5), Cst(2, 3)), "( (4/5) / (2/3) )"},

        // Tests pour expressions imbriquées complexes
        {new Add(Mul(Cst(1, 2), Cst(3, 4)), Sub(Cst(5, 6), Cst(7, 8))),
         "((1/2 * 3/4) + (5/6 - 7/8))"},  // (1/2 * 3/4) + (5/6 - 7/8)
        
        {new Mul(Add(Cst(3, 4), Cst(1, 2)), Cst(5, 6)),
         "((3/4 + 1/2) * 5/6)"},  // ((3/4 + 1/2) * 5/6)

    };

    bool all_passed = true;

    for (const auto& test : tests) {
        stringstream ss;
        streambuf* old = cout.rdbuf(ss.rdbuf());
        test.exp->affiche();
        cout.rdbuf(old);

        if (ss.str() != test.expected_output) {
            cout << "Échec (affichage) pour Cst("; test.exp->affiche(); cout << endl;
            cout << "Sortie obtenue : " << ss.str() << ", sortie attendue : " << test.expected_output << endl;
            all_passed = false;
        }
    }

    if (all_passed) {
        cout << "Réussi: test_affiche" << endl;
    } else {
        cout << "Échec: test_affiche" << endl;
    }
}

void test_simplifie_Cst() {
    struct Test {
        ExprArith* exp;                    // Constante à tester (pas const ici)
        Cst simplified_value;       // Valeur attendue après simplification
    };

    Test tests[] = {
        {new Cst(6, 9), Cst(2, 3)},     // Test avec un rationnel simplifiable (6/9 -> 2/3)
        {new Cst(15, 5), Cst(3, 1)},    // Test avec un rationnel simplifiable (15/5 -> 3/1)
        {new Cst(10, 2), Cst(5, 1)},    // Test avec un rationnel simplifiable (10/2 -> 5/1)
        {new Cst(7, 1), Cst(7, 1)},     // Test avec un rationnel déjà simplifié (7/1 reste 7/1)
        {new Cst(8, 12), Cst(2, 3)},    // Test avec un rationnel simplifiable (8/12 -> 2/3)

        // Tests pour Add
        {new Add(Cst(5, 3), Cst(7, 1)), Cst(26, 3)},
        {new Add(Cst(6, 1), Cst(2, 3)), Cst(20, 3)},
        
        // Tests pour Mul
        {new Mul(Cst(2, 3), Cst(4, 5)), Cst(8, 15)},
        {new Mul(Cst(6, 1), Cst(3, 2)), Cst(9)},
        
        // Tests pour Sub
        {new Sub(Cst(5, 3), Cst(2, 3)), Cst(1)},
        {new Sub(Cst(7, 1), Cst(4, 1)), Cst(3)},
        
        // Tests pour Div
        {new Div(Cst(6, 1), Cst(3, 2)), Cst(4)},
        {new Div(Cst(4, 5), Cst(2, 3)), Cst(6, 5)},

        // Tests pour expressions imbriquées complexes
        {new Add(Mul(Cst(1, 2), Cst(3, 4)), Sub(Cst(5, 6), Cst(7, 8))),
         Cst(1,3)},  // (1/2 * 3/4) + (5/6 - 7/8)
        
        {new Mul(Add(Cst(3, 4), Cst(1, 2)), Cst(5, 6)),
         Cst(25, 24)},  // ((3/4 + 1/2) * 5/6)

        };

    bool all_passed = true;

    for (auto& test : tests) {
        try {
            Cst result = test.exp->simplifie();  // On peut appeler simplifie() ici

            if (result.get_num() != test.simplified_value.get_num() || 
                result.get_denum() != test.simplified_value.get_denum()) {
                cout << "Échec (simplification) pour le rationnel : ";
                test.exp->affiche();
                cout << endl << "Résultat obtenu : ";
                result.affiche();
                cout << endl << "Résultat attendu : ";
                test.simplified_value.affiche();
                all_passed = false;
            }
        } catch (const exception& e) {
            cout << "Exception pour le rationnel : "; 
            test.exp->affiche();
            cout << " (" << e.what() << ")" << endl;
            all_passed = false;
        }
    }

    if (all_passed) {
        cout << "Réussi: test_simplifie" << endl;
    } else {
        cout << "Échec: test_simplifie" << endl;
    }
}


void test_sujet()
{
    Cst un(1), trois(3), cinq(5);
    Mul s(trois, cinq ); Add a(un, s) ;
    a.affiche(); cout << " = "; a.simplifie().affiche(); cout << endl;
    Cst usix (1, 6) , udemi (1, 2);
    Add b = Add(usix, udemi);
    b.affiche(); cout << " = "; b.simplifie().affiche(); cout << endl;
}
