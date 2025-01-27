#include <iostream>
#include <stdexcept>
#include "Expr.hpp"

using namespace std;

void test_constructeur_par_defaut() {
    Expr expr;
    if (expr.get_nature() != Null) {
        cout << "Échec: test_constructeur_par_defaut" << endl;
    } else {
        cout << "Réussi: test_constructeur_par_defaut" << endl;
    }
}

void test_constructeur_cst_int() {
    Expr expr(42);
    if (expr.get_nature() != CstInt || expr.get_int_value() != 42) {
        cout << "Échec: test_constructeur_cst_int" << endl;
    } else {
        cout << "Réussi: test_constructeur_cst_int" << endl;
    }
}

void test_constructeur_cst_symb() {
    struct Test {
        string input;
        CstSymb_t expected_value;
    };

    Test tests[] = {
        {"pi", pi}, {"PI", pi}, {"Pi", pi},
        {"e", e}, {"E", e},
        {"i", i}, {"I", i},
        //{"erreur", i}
    };

    bool all_passed = true;

    for (const auto& test : tests) {
        try {
            Expr expr(test.input);
            if (expr.get_cst_value() != test.expected_value) {
                cout << "Échec pour l'entrée : " << test.input 
                     << " (attendu : " << test.expected_value 
                     << ", obtenu : " << expr.get_cst_value() << ")" << endl;
                all_passed = false;
            }
        } catch (const exception& e) {
            cout << "Exception pour l'entrée : " << test.input 
                 << " (" << e.what() << ")" << endl;
            all_passed = false;
        }
    }

    if (all_passed) {
        cout << "Réussi: test_constructeur_cst_symb" << endl;
    } else {
        cout << "Échec: test_constructeur_cst_symb" << endl;
    }
}


void test_constructeur_variable() {
    Expr expr('x');
    if (expr.get_nature() != Var || expr.get_char_value() != 'x') {
        cout << "Échec: test_constructeur_variable" << endl;
    } else {
        cout << "Réussi: test_constructeur_variable" << endl;
    }
}

void test_operateur_unaire() {
    struct Test {
        Unary_op_t op;                // Opérateur unaire
        Nature_t nature;              // Nature attendue de l'expression
        int operand_value;            // Stocke une valeur entière comme opérande si nature == CstInt
        bool expect_simplified;       // Indique si l'expression devrait être simplifiée
        int simplified_value;         // Valeur attendue après simplification (si applicable)
    };

    Test tests[] = {
        {Neg, CstInt, 5, true, -5},  // Test Neg avec un entier positif
        {Neg, CstInt, 0, true, 0},   // Test Neg avec 0
        {Neg, CstInt, -7, true, 7},  // Test Neg avec un entier négatif
        {Sqrt, CstInt, 16, true, 4}, // Test Sqrt avec un carré parfait
        {Sqrt, CstInt, 0, true, 0},  // Test Sqrt avec 0
        {Ln, CstInt, 1, true, 0},    // Test Ln avec 1
        {Ln, CstSymb, e, true, 1},    // Test Ln avec e
    };

    bool all_passed = true;

    for (const auto& test : tests) {
        try {
            Expr operand(test.operand_value);
            if (test.nature == CstSymb) 
            {
                operand = Expr("e");
            }

            // Crée l'expression unaire
            Expr expr(test.op, operand);
            
            // Vérifie que la nature et l'opérateur sont corrects
            if (expr.get_nature() != Unary_op || expr.get_unary_op_value() != test.op) {
                cout << "Échec (nature ou opérateur) pour l'opérateur : " << test.op << endl;
                all_passed = false;
                continue;
            }

            // Simplification si attendue
            if (test.expect_simplified) {
                expr.simplifie();
                if (expr.get_nature() != CstInt || expr.get_int_value() != test.simplified_value) {
                    cout << "Échec (simplification) pour l'opérateur : " << test.op 
                         << " avec l'opérande : " << test.operand_value << endl;
                    cout << "Résultat obtenu : " << expr.get_int_value() << endl;
                    all_passed = false;
                }
            }
        } catch (const exception& e) {
            cout << "Exception pour l'opérateur : " << test.op
                 << " avec l'opérande : " << test.operand_value
                 << " (" << e.what() << ")" << endl;
            all_passed = false;
        }
    }

    if (all_passed) {
        cout << "Réussi: test_operateur_unaire" << endl;
    } else {
        cout << "Échec: test_operateur_unaire" << endl;
    }
}


void test_operateur_binaire() {
    struct Test {
        Binary_op_t op;
        int left_value;         // Valeur du côté gauche
        int right_value;        // Valeur du côté droit
        bool expect_simplified; // Indique si l'expression doit être simplifiée
        int simplified_value;   // Résultat attendu après simplification
    };

    Test tests[] = {
        {Add, 6, 7, true, 13},       // Test addition
        {Add, 0, 0, true, 0},        // Test addition avec zéro
        {Add, 0, 5, true, 5},        // Test addition avec zéro
        {Add, 5, 0, true, 5},        // Test addition avec zéro
        {Add, 5, -5, true, 0},       // Test addition avec un négatif

        {Sub, 10, 5, true, 5},       // Test soustraction
        {Sub, 0, 0, true, 0},        // Test soustraction avec zéro
        {Sub, 0, 5, true, -5},       // Test soustraction avec zéro
        {Sub, 5, 0, true, 5},        // Test soustraction avec zéro
        {Sub, 5, 5, true, 0},        // Test soustraction avec lui meme (résultat attendu 0)
        {Sub, 5, -5, true, 10},      // Test soustraction avec un négatif

        {Mul, 3, 4, true, 12},       // Test multiplication
        {Mul, 0, 7, true, 0},        // Test multiplication avec zéro (résultat attendu 0)
        {Mul, 7, 0, true, 0},        // Test multiplication avec zéro (résultat attendu 0)
        {Mul, 5, 1, true, 5},        // Test multiplication avec un (résultat attendu 5)
        {Mul, 1, 5, true, 5},        // Test multiplication avec un (résultat attendu 5)
        {Mul, 0, 0, true, 0},        // Test multiplication avec zéro (résultat attendu 0)
        {Mul, 1, 1, true, 1},        // Test multiplication avec 1
        {Mul, 1, 0, true, 0},        // Test multiplication avec 0

        {Div, 8, 2, true, 4},        // Test division
        {Div, 0, 1, true, 0},        // Test division avec zéro en numérateur
        {Div, 0, -1, true, 0},       // Test division par zéro (attend une exception)
        {Div, 8, 4, true, 2},        // Test division simple
        {Div, -8, 4, true, -2},      // Test division avec un négatif
        {Div, 8, -4, true, -2},      // Test division avec un négatif
        {Div, -8, -4, true, 2},      // Test division avec un négatif
        {Div, 1, 1, true, 1},        // Test division 1/1 (résultat attendu 1)
        {Div, 7, 0, false, 0},       // Test division par zéro (attend une exception)
        {Div, 10, 10, true, 1},      // Test division même nombre en haut et en bas (résultat attendu 1)

        {Pow, 2, 3, true, 8},        // Test puissance (2^3)
        {Pow, 3, 2, true, 9},        // Test puissance (3^2)
        {Pow, 5, 0, true, 1},        // Test puissance avec exposant zéro (résultat attendu 1)
        {Pow, 0, 5, true, 0},        // Test puissance avec base zéro (résultat attendu 0)
        {Pow, -2, 3, true, -8},      // Test puissance avec base négative et exposant impair
        {Pow, -2, 2, true, 4},       // Test puissance avec base négative et exposant pair
        {Pow, 1, 100, true, 1},      // Test puissance avec base égale à 1 (résultat attendu 1)
        {Pow, 0, 0, false, 0},       // Test puissance 0^0 (attend une exception)

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


void test_simplifie() {
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
}

int main() {
    test_constructeur_par_defaut();
    test_constructeur_cst_int();
    test_constructeur_cst_symb();
    test_constructeur_variable();
    test_operateur_unaire();
    test_operateur_binaire();
    test_simplifie();

    return 0;
}
