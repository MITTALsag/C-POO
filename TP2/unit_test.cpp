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
    if (expr.get_nature() != CstInt || expr.get_value().intValue != 42) {
        cout << "Échec: test_constructeur_cst_int" << endl;
        return;
    } 

    Expr expr2(-12);
    if (expr2.get_nature() != CstInt || expr2.get_value().intValue != -12) {
        cout << "Échec: test_constructeur_cst_int" << endl;
        return;
    }

    cout << "Réussi: test_constructeur_cst_int" << endl;
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
            if (expr.get_value().cstValue != test.expected_value) {
                cout << "Échec pour l'entrée : " << test.input 
                     << " (attendu : " << test.expected_value 
                     << ", obtenu : " << expr.get_value().cstValue << ")" << endl;
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
    if (expr.get_nature() != Var || expr.get_value().charValue != 'x') {
        cout << "Échec: test_constructeur_variable" << endl;
    } else {
        cout << "Réussi: test_constructeur_variable" << endl;
    }
}

void test_constructeur_unaire() {
    struct Test {
        Unary_op_t op;
        Expr gauche;  // Utilisation d'Expr pour le fils gauche
        Unary_op_t expected_op;
        int expected_value;
    };

    Test tests[] = {
        {Neg, Expr(42), Neg, 42},
        {Sqrt, Expr(16), Sqrt, 16},
        {Ln, Expr(10), Ln, 10},
    };

    bool all_passed = true;

    for (const auto& test : tests) {
        try {
            Expr expr(test.op, test.gauche);  // Construction de l'expr unaire
            if (expr.get_nature() != Unary_op || expr.get_value().unaryOpValue != test.expected_op 
                || expr.get_value_left_child().intValue != test.expected_value) 
            {
                cout << "Échec pour l'opération unaire : " << test.expected_op 
                     << " avec valeur : " << test.gauche.get_value().intValue << endl;
                all_passed = false;
            }
        } catch (const exception& e) {
            cout << "Exception pour l'opération unaire : " << test.expected_op 
                 << " (" << e.what() << ")" << endl;
            all_passed = false;
        }
    }

    //Verification que le constructeur fais une copie profonde
    Expr gauche(2);
    Expr expr(Ln, gauche);

    // Modification de l'enfant
    gauche = Expr(4);
    if (expr.get_value_left_child().intValue == 4) {
        cout << "Échec: test_constructeur_unaire (copie profonde)" << endl;
        all_passed = false;
    }

    if (all_passed) {
        cout << "Réussi: test_constructeur_unaire" << endl;
    } else {
        cout << "Échec: test_constructeur_unaire" << endl;
    }
}

void test_constructeur_binaire() {
    struct Test {
        Binary_op_t op;
        int left_value;
        int right_value;
        Binary_op_t expected_op;
        int expected_left_value;
        int expected_right_value;
    };

    Test tests[] = {
        {Add, 2, 3, Add, 2, 3},
        {Sub, 5, 3, Sub, 5, 3},
        {Mul, 4, 6, Mul, 4, 6},
        {Div, 10, 2, Div, 10, 2},
        {Pow, 2, 8, Pow, 2, 8},
    };

    bool all_passed = true;

    for (const auto& test : tests) {
        try {
            Expr expr(test.op, Expr(test.left_value), Expr(test.right_value));
            if (expr.get_nature() != Binary_op || expr.get_value().binaryOpValue != test.expected_op
                || expr.get_value_left_child().intValue != test.expected_left_value)
            {
                cout << "Échec pour l'opération binaire : " << test.expected_op 
                     << " avec enfants : (" << test.left_value << ", " << test.right_value << ")" << endl;
                all_passed = false;
            }
        } catch (const exception& e) {
            cout << "Exception pour l'opération binaire : " << test.expected_op 
                 << " (" << e.what() << ")" << endl;
            all_passed = false;
        }
    }

    //Verification que le constructeur fais une copie profonde
    Expr gauche(2);
    Expr droite(3);
    Expr expr(Add, gauche, droite);

    // Modification de l'enfant
    gauche = Expr(4);
    droite = Expr(5);
    if (expr.get_value_left_child().intValue == 4 || expr.get_value_right_child().intValue == 5) {
        cout << "Échec: test_constructeur_binaire (copie profonde)" << endl;
        all_passed = false;
    }


    if (all_passed) {
        cout << "Réussi: test_constructeur_binaire" << endl;
    } else {
        cout << "Échec: test_constructeur_binaire" << endl;
    }
}

void test_constructeur_copie() {
    // Création d'expressions initiales
    Expr gauche(42); // Constante entière
    Expr droit('x'); // Variable
    Expr original(Add, gauche, droit); // Opération binaire

    // Construction de la copie
    Expr copie(original);

    // Vérification que la copie est égale à l'original initialement
    if (copie != original) {
        cout << "Échec: test_constructeur_copie (copie initiale incorrecte)" << endl;
        return;
    }

    // Modification des expressions originales
    gauche = Expr(100); // Changer la constante
    droit = Expr('y');  // Changer la variable

    // Vérification que la copie n'a pas été affectée par les modifications de l'original
    if (copie.get_value_left_child().intValue == 100 || copie.get_value_right_child().charValue == 'y'
        || original.get_value_left_child().intValue == 100 || original.get_value_right_child().charValue == 'y') 
    {
        cout << "Échec: test_constructeur_copie (copie non indépendante)" << endl;
    } else {
        cout << "Réussi: test_constructeur_copie" << endl;
    }
}

// Fonction de test pour l'affectation
void test_affectation() {

    // Définition des tests
    Expr tests[] = {
        {Expr(42)},  // Affectation simple d'un entier
        {Expr(10)},  // Affectation d'un autre entier
        {Expr("pi")},  // Affectation d'une constante symbolique
        {Expr('x')},  // Affectation d'une variable
        {Expr(Add, 2, 3)},  // Affectation d'une opération binaire
        {Expr(Neg, 5)},  // Affectation d'une opération unaire
        {Expr(Add, Expr(Add, 2, 3), 4)},  // Affectation d'une expression
    };

    bool all_passed = true;

    // Exécution des tests
    for (auto& test : tests) {
        try {
            Expr expr(0);  // Création d'une nouvelle expression (initialisée à 0)
            expr = test;  // Test de l'affectation

            // Vérification si la valeur après affectation est correcte
            if (expr != test) {
                cout << "Échec pour l'affectation, valeur attendue : "; test.affiche();
                cout << " valeur obtenue : "; expr.affiche();
                all_passed = false;
            }
        } catch (const exception& e) {
            cout << "Exception pour l'affectation : " << e.what() << endl;
            all_passed = false;
        }
    }

    // Vérification de la copie profonde des fils lors de l'affectation
    Expr gauche(2);
    Expr droite(3);
    Expr expr(Add, gauche, droite);

    // Modification des enfants
    gauche = Expr(4);
    droite = Expr(5);

    if (expr == Expr(Add, 4, 5)) {
        cout << "Échec: test_affectation (copie profonde)"  << endl;
        all_passed = false;
    }

    if (all_passed) {
        cout << "Réussi: test_affectation" << endl;
    } else {
        cout << "Échec: test_affectation" << endl;
    }
}


void test_operateur_unaire() {
    struct Test {
        Unary_op_t op;                // Opérateur unaire
        Nature_t nature;              // Nature attendue de l'expression
        Expr operand_value;            // Stocke une valeur entière comme opérande si nature == CstInt
        bool expect_simplified;       // Indique si l'expression devrait être simplifiée
        int simplified_value;         // Valeur attendue après simplification (si applicable)
    };

    Test tests[] = {
        {Neg, CstInt, Expr(5), true, -5},  // Test Neg avec un entier positif
        {Neg, CstInt, Expr(0), true, 0},   // Test Neg avec 0
        {Neg, CstInt, Expr(-7), true, 7},  // Test Neg avec un entier négatif
        {Neg, CstInt, Expr(Neg, 1), true, 1},  // Test Neg avec Neg(1) (doit être simplifié en 1)

        {Sqrt, CstInt, Expr(16), true, 4}, // Test Sqrt avec un carré parfait
        {Sqrt, CstInt, Expr(0), true, 0},  // Test Sqrt avec 0
        {Sqrt, CstInt, Expr(1), true, 1},  // Test Sqrt avec 1
        {Sqrt, CstInt, Expr(-1), false, 0}, // Test Sqrt avec un négatif (attend une exception)
        

        {Ln, CstInt, Expr(1), true, 0},    // Test Ln avec 1
        {Ln, CstSymb, Expr(e), true, 1},    // Test Ln avec e
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
            if (expr.get_nature() != Unary_op || expr.get_value().unaryOpValue != test.op) {
                cout << "Échec (nature ou opérateur) pour l'opérateur : " << test.op << endl;
                all_passed = false;
                continue;
            }

            // Simplification si attendue
            if (test.expect_simplified) {
                expr.simplifie();
                if (expr.get_nature() != CstInt || expr.get_value().intValue != test.simplified_value) {
                    cout << "Échec (simplification) pour l'opérateur : " << test.op 
                         << " avec l'opérande : " ;
                         test.operand_value.affiche();
                    cout << "Résultat obtenu : " << expr.get_value().intValue << endl;
                    all_passed = false;
                }
            }
        } catch (const exception& e) {
            cout << "Exception pour l'opérateur : " << test.op
                 << " avec l'opérande : "; 
                 test.operand_value.affiche();
            cout << " (" << e.what() << ")" << endl;
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
        Expr left_value;         // Valeur du côté gauche
        Expr right_value;        // Valeur du côté droit
        bool expect_simplified; // Indique si l'expression doit être simplifiée
        int simplified_value;   // Résultat attendu après simplification
    };

    Test tests[] = {
        {Add, Expr(6), Expr(7), true, 13},       // Test addition
        {Add, Expr(0), Expr(0), true, 0},        // Test addition avec zéro
        {Add, Expr(0), Expr(5), true, 5},        // Test addition avec zéro
        {Add, Expr(5), Expr(0), true, 5},        // Test addition avec zéro
        {Add, Expr(5), Expr(-5), true, 0},       // Test addition avec un négatif

        {Sub, Expr(10), Expr(5), true, 5},       // Test soustraction
        {Sub, Expr(0), Expr(0), true, 0},        // Test soustraction avec zéro
        {Sub, Expr(0), Expr(5), true, -5},       // Test soustraction avec zéro
        {Sub, Expr(5), Expr(0), true, 5},        // Test soustraction avec zéro
        {Sub, Expr(5), Expr(5), true, 0},        // Test soustraction avec lui-même
        {Sub, Expr(5), Expr(-5), true, 10},      // Test soustraction avec un négatif

        {Mul, Expr(3), Expr(4), true, 12},       // Test multiplication
        {Mul, Expr(0), Expr(7), true, 0},        // Test multiplication avec zéro
        {Mul, Expr(7), Expr(0), true, 0},        // Test multiplication avec zéro
        {Mul, Expr(5), Expr(1), true, 5},        // Test multiplication avec un
        {Mul, Expr(1), Expr(5), true, 5},        // Test multiplication avec un
        {Mul, Expr(0), Expr(0), true, 0},        // Test multiplication avec zéro
        {Mul, Expr(1), Expr(1), true, 1},        // Test multiplication avec 1
        {Mul, Expr(1), Expr(0), true, 0},        // Test multiplication avec 0

        {Div, Expr(8), Expr(2), true, 4},        // Test division
        {Div, Expr(0), Expr(1), true, 0},        // Test division avec zéro en numérateur
        {Div, Expr(0), Expr(-1), true, 0},       // Test division par zéro (attend une exception)
        {Div, Expr(8), Expr(4), true, 2},        // Test division simple
        {Div, Expr(-8), Expr(4), true, -2},      // Test division avec un négatif
        {Div, Expr(8), Expr(-4), true, -2},      // Test division avec un négatif
        {Div, Expr(-8), Expr(-4), true, 2},      // Test division avec un négatif
        {Div, Expr(1), Expr(1), true, 1},        // Test division 1/1
        {Div, Expr(7), Expr(0), false, 0},       // Test division par zéro (attend une exception)
        {Div, Expr(10), Expr(10), true, 1},      // Test division même nombre en haut et en bas

        {Pow, Expr(2), Expr(3), true, 8},        // Test puissance (2^3)
        {Pow, Expr(3), Expr(2), true, 9},        // Test puissance (3^2)
        {Pow, Expr(5), Expr(0), true, 1},        // Test puissance avec exposant zéro
        {Pow, Expr(0), Expr(5), true, 0},        // Test puissance avec base zéro
        {Pow, Expr(-2), Expr(3), true, -8},      // Test puissance avec base négative et exposant impair
        {Pow, Expr(-2), Expr(2), true, 4},       // Test puissance avec base négative et exposant pair
        {Pow, Expr(1), Expr(100), true, 1},      // Test puissance avec base égale à 1
        {Pow, Expr(0), Expr(0), false, 0},       // Test puissance 0^0 (attend une exception)
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
            if (expr.get_nature() != Binary_op || expr.get_value().binaryOpValue != test.op) {
                cout << "Échec (nature ou opérateur) pour l'opérateur : " << test.op << endl;
                all_passed = false;
                continue;
            }

            // Simplification si attendue
            if (test.expect_simplified) {
                expr.simplifie();
                if (expr.get_nature() != CstInt || expr.get_value().cstValue != test.simplified_value) {
                    cout << "Échec (simplification) pour l'opérateur : " << test.op << endl;
                    cout << "Résultat obtenu : " << expr.get_value().intValue << endl;
                    all_passed = false;
                }
            }
        } catch (const exception& e) {
            // Si une exception est attendue (division par zéro par exemple)
            if (test.expect_simplified == false) {
                cout << "Exception attendue pour l'opérateur : " << test.op << " (" << e.what() << ")" << endl;
            } else {
                cout << "Exception inattendue pour l'opérateur : " << test.op << " (" << e.what() << ")" << endl;
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
    test_constructeur_unaire();
    test_constructeur_binaire();
    test_constructeur_copie();
    test_affectation();
    test_operateur_unaire();
    test_operateur_binaire();
    test_simplifie();

    return 0;
}
