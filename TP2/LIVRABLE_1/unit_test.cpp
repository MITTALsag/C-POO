#include <iostream>
#include <stdexcept>
#include <math.h>
#include "Expr.hpp"

using namespace std;




/* test le constructeur par défaut */
void test_constructeur_par_defaut() {
    Expr expr;
    if (expr != Expr(0)) {
        cout << "Échec: test_constructeur_par_defaut" << endl;
    } else {
        cout << "Réussi: test_constructeur_par_defaut" << endl;
    }
}

/* test le constructeur d'entier */
void test_constructeur_cst_int() {
    Expr expr(42);
    if (expr != Expr(42)) {
        cout << "Échec: test_constructeur_cst_int" << endl;
        return;
    } 

    Expr expr2(-12);
    if (expr2 != Expr(-12)) {
        cout << "Échec: test_constructeur_cst_int" << endl;
        return;
    }

    cout << "Réussi: test_constructeur_cst_int" << endl;
}

/* test le constructeur de symbole */
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
            if (expr != Expr(test.input)) {
                cout << "Échec pour l'entrée : " << test.input 
                     << " (attendu : " << test.expected_value 
                     << ", obtenu : ";
                     expr.affiche();
                     cout << ")" << endl;
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


/* test le constructeur de variable */
void test_constructeur_variable() {
    Expr expr('x');
    if (expr != Expr('x')) {
        cout << "Échec: test_constructeur_variable" << endl;
    } else {
        cout << "Réussi: test_constructeur_variable" << endl;
    }
}

/* test le constructeur d'opération unaire */
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
            if (expr != Expr(test.op, test.gauche)) 
            {
                cout << "Échec pour l'opération unaire : " << test.expected_op 
                     << " avec valeur : ";
                     test.gauche.affiche();
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
    if (expr == Expr(Ln, Expr(4))) {
        cout << "Échec: test_constructeur_unaire (copie profonde)" << endl;
        all_passed = false;
    }

    if (all_passed) {
        cout << "Réussi: test_constructeur_unaire" << endl;
    } else {
        cout << "Échec: test_constructeur_unaire" << endl;
    }
}

/* test le constructeur d'opération binaire */
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
            if (expr != Expr(test.op, Expr(test.left_value), Expr(test.right_value)))
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
    if (expr == Expr(Add, Expr(4), Expr(5))) {
        cout << "Échec: test_constructeur_binaire (copie profonde)" << endl;
        all_passed = false;
    }


    if (all_passed) {
        cout << "Réussi: test_constructeur_binaire" << endl;
    } else {
        cout << "Échec: test_constructeur_binaire" << endl;
    }
}

/* Test le construvteur de copie (profonde) */
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
    if (copie == Expr(Add, gauche, droit)) 
    {
        cout << "Échec: test_constructeur_copie (copie non indépendante)" << endl;
    } else {
        cout << "Réussi: test_constructeur_copie" << endl;
    }
}

/* Teste l'égalité entre deux expressions */
void test_egalite() 
{
    struct Test {
        Expr expr1;               // Première expression à tester
        Expr expr2;               // Deuxième expression à tester
        bool sont_egales;        // Résultat attendu : vrai si égales, faux sinon
    };

    Test tests[] = {
        {Expr(42), Expr(42), true},            // Test de deux constantes égales
        {Expr(42), Expr(43), false},           // Test de deux constantes différentes
        {Expr('x'), Expr('x'), true},          // Test de deux variables égales
        {Expr('x'), Expr('y'), false},         // Test de deux variables différentes
        {Expr(Add, Expr(2), Expr(3)), Expr(Add, Expr(2), Expr(3)), true},  // Test de deux opérations binaires égales
        {Expr(Add, Expr(2), Expr(3)), Expr(Add, Expr(3), Expr(2)), true}, // Test de deux opérations binaires egal (commutatif)
        {Expr(Mul, Expr(2), Expr(3)), Expr(Mul, Expr(3), Expr(2)), true},  // Test de multiplication commutative
        {Expr(Div, Expr(2), Expr(3)), Expr(Div, Expr(3), Expr(2)), false},  // Test de multiplication non commutative
        {Expr(Sub, Expr(2), Expr(3)), Expr(Sub, Expr(3), Expr(2)), false},  // Test de multiplication non commutative
    };

    bool all_passed = true;

    for (const auto& test : tests) {
        try {
            // Test de l'égalité
            if (test.expr1 == test.expr2 && !test.sont_egales) {
                cout << "Échec : les expressions ";
                test.expr1.affiche();
                cout << " et ";
                test.expr2.affiche();
                cout << " sont égales, mais elles ne devraient pas l'être." << endl;
                all_passed = false;
            } else if (!(test.expr1 == test.expr2) && test.sont_egales) {
                cout << "Échec : les expressions ";
                test.expr1.affiche();
                cout << " et ";
                test.expr2.affiche();
                cout << " ne sont pas égales, mais elles devraient l'être." << endl;
                all_passed = false;
            }
        } catch (const exception& e) {
            cout << "Exception pour la comparaison entre ";
            test.expr1.affiche();
            cout << " et ";
            test.expr2.affiche();
            cout << " : " << e.what() << endl;
            all_passed = false;
        }
    }

    if (all_passed) {
        cout << "Réussi : test_egalite" << endl;
    } else {
        cout << "Échec : test_egalite" << endl;
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

    Expr expr(0);  // Création d'une nouvelle expression (initialisée à 0)

    // Exécution des tests
    for (auto& test : tests) {
        try {
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
    expr = Expr(Add, gauche, droite);

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

/* test la simplification d'opérateur unaire */
void test_operateur_unaire() {
    struct Test {
        Unary_op_t op;                // Opérateur unaire
        Nature_t nature;              // Nature attendue de l'expression
        Expr operand_value;            // Stocke une valeur entière comme opérande si nature == CstInt
        bool expect_simplified;       // Indique si l'expression devrait être simplifiée
        Expr simplified_value;         // Valeur attendue après simplification (si applicable)
    };

    Test tests[] = {
        {Neg, CstInt, Expr(5), true, Expr(-5)},  // Test Neg avec un entier positif
        {Neg, CstInt, Expr(0), true, Expr(0)},   // Test Neg avec 0
        {Neg, CstInt, Expr(-7), true, Expr(7)},  // Test Neg avec un entier négatif
        {Neg, CstInt, Expr(Neg, 1), true, Expr(1)},  // Test Neg avec Neg(1) (doit être simplifié en 1)

        {Sqrt, CstInt, Expr(16), true, Expr(4)}, // Test Sqrt avec un carré parfait
        {Sqrt, CstInt, Expr(0), true, Expr(0)},  // Test Sqrt avec 0
        {Sqrt, CstInt, Expr(1), true, Expr(1)},  // Test Sqrt avec 1
        {Sqrt, CstInt, Expr(-1), false, Expr(0)}, // Test Sqrt avec un négatif (attend une exception)
        
        {Ln, CstInt, Expr(1), true, Expr(0)},                 // Test Ln avec 1
        {Ln, CstSymb, Expr("e"), true, Expr(1)},                // Test Ln avec e
        {Ln, Unary_op, Expr(Exp, Expr(4)), true, Expr(4)},    // Test Ln avec Exp(4)

        {Exp, CstInt, Expr(0), true, 1},                //Test Exp avec 0
        {Exp, Unary_op, Expr(Ln, Expr(2)), true, Expr(2)},    //Test Exp avec Ln(2)

        {Cos, CstInt, Expr(0), true, Expr(1)},    // Test Cos avec 0
        {Cos, CstSymb, Expr("pi"), true, Expr(-1)},    // Test Cos avec pi

        {Sin, CstInt, Expr(0), true, Expr(0)},    // Test Sin avec 0
        {Sin, CstSymb, Expr("pi"), true, Expr(0)},    // Test Sin avec pi
    };

    bool all_passed = true;

    for (const auto& test : tests) {
        try {
            Expr operand = test.operand_value;
            // Crée l'expression unaire
            Expr expr(test.op, operand);
            
            // Vérifie que la nature et l'opérateur sont corrects
            if (expr != Expr(test.op, test.operand_value)) {
                cout << "Échec (nature ou opérateur) pour l'opérateur : " << test.op << endl;
                all_passed = false;
                continue;
            }

            // Simplification si attendue
            if (test.expect_simplified) {
                expr.simplifie();
                if (expr != test.simplified_value) {
                    cout << "Échec (simplification) pour l'opérateur : " << test.op 
                         << " avec l'opérande : " ;
                         test.operand_value.affiche();
                    cout << "Résultat obtenu : ";
                    expr.affiche();
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


/* test la simplification d'opérateur binaire */
void test_operateur_binaire() {
    struct Test {
        Binary_op_t op;
        Expr left_value;         // Valeur du côté gauche
        Expr right_value;        // Valeur du côté droit
        bool expect_simplified; // Indique si l'expression doit être simplifiée
        Expr simplified_value;   // Résultat attendu après simplification
    };

    Test tests[] = {
        {Add, Expr(6), Expr(7), true, Expr(13)},       // Test addition
        {Add, Expr(0), Expr(0), true, Expr(0)},        // Test addition avec zéro
        {Add, Expr(0), Expr(5), true, Expr(5)},        // Test addition avec zéro
        {Add, Expr(5), Expr(0), true, Expr(5)},        // Test addition avec zéro
        {Add, Expr(5), Expr(-5), true, Expr(0)},       // Test addition avec un négatif
        {Add, Expr('x'), Expr(0), true, Expr('x')},

        {Sub, Expr(10), Expr(5), true, Expr(5)},       // Test soustraction
        {Sub, Expr(0), Expr(0), true, Expr(0)},        // Test soustraction avec zéro
        {Sub, Expr(0), Expr(5), true, Expr(-5)},       // Test soustraction avec zéro
        {Sub, Expr(5), Expr(0), true, Expr(5)},        // Test soustraction avec zéro
        {Sub, Expr(5), Expr(5), true, Expr(0)},        // Test soustraction avec lui-même
        {Sub, Expr(5), Expr(-5), true, Expr(10)},      // Test soustraction avec un négatif

        {Mul, Expr(3), Expr(4), true, Expr(12)},       // Test multiplication
        {Mul, Expr(0), Expr(7), true, Expr(0)},        // Test multiplication avec zéro
        {Mul, Expr(7), Expr(0), true, Expr(0)},        // Test multiplication avec zéro
        {Mul, Expr(5), Expr(1), true, Expr(5)},        // Test multiplication avec un
        {Mul, Expr(1), Expr(5), true, Expr(5)},        // Test multiplication avec un
        {Mul, Expr(0), Expr(0), true, Expr(0)},        // Test multiplication avec zéro
        {Mul, Expr(1), Expr(1), true, Expr(1)},        // Test multiplication avec 1
        {Mul, Expr(1), Expr(0), true, Expr(0)},        // Test multiplication avec 0

        {Div, Expr(8), Expr(2), true, Expr(4)},        // Test division
        {Div, Expr(0), Expr(1), true, Expr(0)},        // Test division avec zéro en numérateur
        {Div, Expr(0), Expr(-1), true, Expr(0)},       // Test division par zéro (attend une exception)
        {Div, Expr(8), Expr(4), true, Expr(2)},        // Test division simple
        {Div, Expr(-8), Expr(4), true, Expr(-2)},      // Test division avec un négatif
        {Div, Expr(8), Expr(-4), true, Expr(-2)},      // Test division avec un négatif
        {Div, Expr(-8), Expr(-4), true, Expr(2)},      // Test division avec un négatif
        {Div, Expr(1), Expr(1), true, Expr(1)},        // Test division 1/1
        {Div, Expr(7), Expr(0), false, Expr(0)},       // Test division par zéro (attend une exception)
        {Div, Expr(10), Expr(10), true, Expr(1)},      // Test division même nombre en haut et en bas

        {Pow, Expr(2), Expr(3), true, Expr(8)},        // Test puissance (2^3)
        {Pow, Expr(3), Expr(2), true, Expr(9)},        // Test puissance (3^2)
        {Pow, Expr(5), Expr(0), true, Expr(1)},        // Test puissance avec exposant zéro
        {Pow, Expr(0), Expr(5), true, Expr(0)},        // Test puissance avec base zéro
        {Pow, Expr(-2), Expr(3), true, Expr(-8)},      // Test puissance avec base négative et exposant impair
        {Pow, Expr(-2), Expr(2), true, Expr(4)},       // Test puissance avec base négative et exposant pair
        {Pow, Expr(1), Expr(100), true, Expr(1)},      // Test puissance avec base égale à 1
        {Pow, Expr(0), Expr(0), false, Expr(0)},       // Test puissance 0^0 (attend une exception)
    };

    bool all_passed = true;

    for (const auto& test : tests) {
        try {
            // Crée les opérandes sous forme de constantes entières
            Expr left = test.left_value;
            Expr right = test.right_value;

            // Crée l'expression binaire
            Expr expr(test.op, left, right);


            // Vérifie que la nature et l'opérateur sont corrects
            if (expr != Expr(test.op, test.left_value, test.right_value)) {
                cout << "Échec (nature ou opérateur) pour l'opérateur : " << test.op << endl;
                all_passed = false;
                continue;
            }

            // Simplification si attendue
            if (test.expect_simplified) {
                expr.simplifie();
                if (expr != test.simplified_value) {
                    cout << "Échec (simplification) pour l'opérateur : " << test.op << endl;
                    cout << "Résultat obtenu : ";
                    expr.affiche(); 
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

/* test du sujet */
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


/* Test de la dérivation pour des expressions simples */
void test_derive_simple() 
{
    struct Test {
        Expr expr;                // Expression à dériver
        Expr expected_derivative; // Dérivée attendue
    };

    Test tests[] = {
        {Expr(42), Expr(0)},              // Dérivée d'une constante
        {Expr('x'), Expr(1)},             // Dérivée de la variable x
        {Expr(2), Expr(0)},               // Dérivée d'une constante
        {Expr('y'), Expr(0)},             // Dérivée d'une variable autre que x
    };

    bool all_passed = true;

    for (auto& test : tests) {
        try {
            test.expr.derive(Expr('x'));
            Expr derivative(test.expr);
            derivative.simplifie();
            if (derivative != test.expected_derivative) {
                cout << "Échec pour l'expression : "; test.expr.affiche();
                cout << " Résultat attendu : "; test.expected_derivative.affiche();
                cout << " Résultat obtenu : "; derivative.affiche();
                all_passed = false;
            }
        } catch (const exception& e) {
            cout << "Exception pour l'expression : "; test.expr.affiche();
            cout << " (" << e.what() << ")" << endl;
            all_passed = false;
        }
    }

    if (all_passed) {
        cout << "Réussi: test_derive_simple" << endl;
    } else {
        cout << "Échec: test_derive_simple" << endl;
    }
}

/* Test de la dérivation pour des opérateurs unaires */
void test_derive_unary() 
{
    struct Test {
        Unary_op_t op;                // Opérateur unaire
        Expr operand_value;            // Opérande de l'opération unaire
        Expr expected_derivative;      // Dérivée attendue
    };

    Test tests[] = {
        {Neg, Expr('x'), Expr(-1)},              // Dérivée de -x
        {Sqrt, Expr('x'), Expr(Div, Expr(1), Expr(Mul, Expr(2), Expr(Sqrt, Expr('x'))))}, // Dérivée de sqrt(x)
        {Ln, Expr('x'), Expr(Div, Expr(1), Expr('x'))},      // Dérivée de ln(x)
    };

    bool all_passed = true;

    for (const auto& test : tests) {
        try {
            Expr operand = test.operand_value;
            Expr expr(test.op, operand);
            expr.derive(Expr('x'));
            Expr derivative = expr;
            derivative.simplifie();
            if (derivative != test.expected_derivative) {
                cout << "Échec pour l'opération unaire : " << test.op << endl;
                cout << " Résultat attendu : "; test.expected_derivative.affiche();
                cout << " Résultat obtenu : "; derivative.affiche();
                all_passed = false;
            }
        } catch (const exception& e) {
            cout << "Exception pour l'opération unaire : " << test.op << endl;
            cout << " (" << e.what() << ")" << endl;
            all_passed = false;
        }
    }

    if (all_passed) {
        cout << "Réussi: test_derive_unary" << endl;
    } else {
        cout << "Échec: test_derive_unary" << endl;
    }
}

/* Test de la dérivation pour des opérateurs binaires */
void test_derive_binary() 
{
    struct Test {
        Binary_op_t op;              // Opérateur binaire
        Expr left_value;             // Valeur du côté gauche
        Expr right_value;            // Valeur du côté droit
        Expr expected_derivative;    // Dérivée attendue
    };

    Test tests[] = {
        {Add, Expr('x'), Expr(5), Expr(1)},       // Dérivée de x + 5
        {Sub, Expr('x'), Expr(5), Expr(1)},       // Dérivée de x - 5
        {Mul, Expr('x'), Expr(5), Expr(5)},       // Dérivée de x * 5
        {Div, Expr('x'), Expr(5), Expr(Div, Expr(1), Expr(5))}, // Dérivée de x / 5
        {Pow, Expr('x'), Expr(2), Expr(Mul, Expr(2), Expr('x'))}, // Dérivée de x^2
    };

    bool all_passed = true;

    for (const auto& test : tests) {
        try {
            Expr left = test.left_value;
            Expr right = test.right_value;
            Expr expr(test.op, left, right);
            expr.derive(Expr('x'));
            Expr derivative = expr;
            derivative.simplifie();
            if (derivative != test.expected_derivative) {
                cout << "Échec pour l'opération binaire : " << test.op << endl;
                cout << " Résultat attendu : "; test.expected_derivative.affiche();
                cout << " Résultat obtenu : "; derivative.affiche();
                all_passed = false;
            }
        } catch (const exception& e) {
            cout << "Exception pour l'opération binaire : " << test.op << endl;
            cout << " (" << e.what() << ")" << endl;
            all_passed = false;
        }
    }

    if (all_passed) {
        cout << "Réussi: test_derive_binary" << endl;
    } else {
        cout << "Échec: test_derive_binary" << endl;
    }
}


/* Teste la fonction de substitution */
void test_subs() 
{
    struct Test {
        Expr expr;          // Expression de départ
        Expr var;           // Variable à remplacer
        Expr remplacement;  // Expression de remplacement
        Expr resultat_attendu; // Résultat attendu après substitution
    };

    Test tests[] = {
        {Expr('x'), Expr('x'), Expr(42), Expr(42)},  // Substitution d'une variable seule
        {Expr('x'), Expr('y'), Expr(42), Expr('x')}, // Substitution sans effet (var ≠ expr)
        {Expr(Add, Expr('x'), Expr(2)), Expr('x'), Expr(42), Expr(Add, Expr(42), Expr(2))}, // Substitution dans une addition
        {Expr(Mul, Expr('x'), Expr('y')), Expr('x'), Expr(3), Expr(Mul, Expr(3), Expr('y'))}, // Substitution dans une multiplication
        {Expr(Add, Expr('x'), Expr('x')), Expr('x'), Expr(1), Expr(Add, Expr(1), Expr(1))}, // Substitution multiple
        {Expr(Add, Expr('x'), Expr('y')), Expr('y'), Expr(Mul, Expr(2), Expr('x')), Expr(Add, Expr('x'), Expr(Mul, Expr(2), Expr('x')))} // Substitution avec une expression plus complexe
    };

    bool all_passed = true;

    for (const auto& test : tests) {
        try {
            Expr expr_modifie = test.expr;
            expr_modifie.subs(&test.var, &test.remplacement);

            if (expr_modifie != test.resultat_attendu) {
                cout << "Échec : Substitution de ";
                test.var.affiche();
                cout << " par ";
                test.remplacement.affiche();
                    cout << " dans ";
                    test.expr.affiche();
                    cout << " donne ";
                    expr_modifie.affiche();
                    cout << " au lieu de ";
                    test.resultat_attendu.affiche();
                    cout << endl;
                all_passed = false;
            }
        } catch (const exception& e) {
            cout << "Exception lors de la substitution dans ";
            test.expr.affiche();
                cout << " : " << e.what() << endl;
            all_passed = false;
        }
    }

    if (all_passed) {
        cout << "Réussi : test_subs" << endl;
    } else {
        cout << "Échec : test_subs" << endl;
    }
}


/* Teste la fonction d'évaluation (eval) */
void test_eval() 
{
    struct Test {
        Expr expr;             // Expression de départ
        double resultat_attendu; // Résultat attendu après évaluation
    };

    Test tests[] = {
        {Expr(5), 5.0},                            // Constante simple
        {Expr(Add, Expr(3), Expr(2)), 5.0},        // Addition simple (3 + 2)
        {Expr(Mul, Expr(3), Expr(2)), 6.0},        // Multiplication simple (3 * 2)
        {Expr(Add, Expr(1), Expr(Mul, Expr(3), Expr(2))), 7.0},  // (1 + (3 * 2)) => 7
        {Expr(Add, Expr(2), Expr(Mul, Expr(2), Expr(3))), 8.0},  // (2 + (2 * 3)) => 8
        {Expr(Mul, Expr(Add, Expr(2), Expr(3)), Expr(4)), 20.0},  // ((2 + 3) * 4) => 20

        // Tests avec sqrt
        {Expr(Sqrt, Expr(9)), 3.0},                // sqrt(9) => 3
        {Expr(Sqrt, Expr(25)), 5.0},               // sqrt(25) => 5
        {Expr(Sqrt, Expr(2)), sqrt(2)},        // sqrt(2) 

        // Tests avec ln (logarithme népérien)
        {Expr(Ln, Expr("e")), 1.0},                // ln(e) => 1
        {Expr(Ln, Expr(1)), 0.0},                  // ln(1) => 0
        {Expr(Ln, Expr(10)), log(10)},   // ln(10)

        // Tests avec exp (exponentielle)
        {Expr(Exp, Expr(1)), exp(1)},   // exp(1) => e
        {Expr(Exp, Expr(0)), 1.0},                 // exp(0) => 1
        {Expr(Exp, Expr(2)), exp(2)},  // exp(2) => approx 7.3890560989306495

        // Tests avec cos
        {Expr(Cos, Expr(0)), 1.0},                 // cos(0) => 1
        {Expr(Cos, Expr(Div, Expr("pi"), 2)), 0.0},               // cos(π/2) => 0
        {Expr(Cos, Expr("pi")), -1.0},             // cos(π) => -1

        // Tests avec sin
        {Expr(Sin, Expr(0)), 0.0},                 // sin(0) => 0
        {Expr(Sin, Expr(Div, Expr("pi"), 2)), 1.0},          // sin(π/2) => 1
        {Expr(Sin, Expr("pi")), 0.0},              // sin(π) => 0

        // Tests avec π
        {Expr(Mul, Expr("pi"), Expr(2)), 2*M_PI},  // π * 2 => 2π
        {Expr(Add, Expr("pi"), Expr(1)), M_PI + 1},  // π + 1 => π + 1
        {Expr(Sub, Expr("pi"), Expr(1)), M_PI - 1},  // π - 1 => π - 1

        // Tests avec e
        {Expr(Mul, Expr("e"), Expr(2)), M_E * 2},    // e * 2 => 2e
        {Expr(Add, Expr("e"), Expr(1)), M_E + 1},    // e + 1 => e + 1
        {Expr(Sub, Expr("e"), Expr(1)), M_E - 1},    // e - 1 => e - 1
    };

    bool all_passed = true;
    const double tolerance = 1e-12;  // Tolérance de comparaison (1e-12)

    for (const auto& test : tests) {
        try {
            double result = test.expr.eval();  // Évaluation de l'expression

            // Comparaison avec une tolérance
            if (fabs(result - test.resultat_attendu) > tolerance) {
                cout << "Échec : L'évaluation de ";
                test.expr.affiche();
                    cout << " donne " << result
                     << " au lieu de " << test.resultat_attendu << endl;
                all_passed = false;
            }
        } catch (const exception& e) {
            cout << "Exception lors de l'évaluation de ";
            test.expr.affiche();
                 cout << " : " << e.what() << endl;
            all_passed = false;
        }
    }

    if (all_passed) {
        cout << "Réussi : test_eval" << endl;
    } else {
        cout << "Échec : test_eval" << endl;
    }
}


// fonction pour afficher les détaille d'une expression
//(val_subs doit etre une expression qui ne contient pas de var)
void afficher_details(const Expr& exp, const Expr* var, const Expr& val_subs)
{
    Expr exp_simplifie = exp;
    exp_simplifie.simplifie();

    Expr exp_derive = exp;
    exp_derive.derive(*var);

    cout << endl;
    cout << "L'expression : ";
    exp.affiche();
    cout << " est égal à : ";
    exp_simplifie.affiche();
    cout << " Après simplification." << endl;

    cout << "Voici l'expression après substitution de ";
    var->affiche();
    cout << " par ";
    val_subs.affiche();
    cout << " : ";
    exp_simplifie.subs(var, &val_subs);
    exp_simplifie.affiche();
    cout << endl;
    
    cout << "Son évaluation est : " << exp_simplifie.eval() << endl;
    cout << "Et la dérivée de ";
    exp.affiche();
    cout << " par rapport à ";
    var->affiche();
    cout << " est : ";
    exp_derive.affiche();
    cout << endl;
}

// Pour afficher des résultat
void tester_expressions() 
{
    Expr var_x('x');  // La variable x

    // Test 1 : x + 3
    Expr expr1(Add, var_x, Expr(3));
    afficher_details(expr1, &var_x, Expr(2));

    // Test 2 : x² + 2x + 1
    Expr expr2(Add, Expr(Pow, var_x, Expr(2)), Expr(Add, Expr(Mul, Expr(2), var_x), Expr(1)));
    afficher_details(expr2, &var_x, Expr(2));

    // Test 3 : sin(x) + cos(x)
    Expr expr3(Add, Expr(Sin, var_x), Expr(Cos, var_x));
    afficher_details(expr3, &var_x, Expr(Div, Expr("pi"), Expr(4))); // π/4 pour un résultat exact

    // Test 4 : e^x + ln(x)
    Expr expr4(Add, Expr(Exp, var_x), Expr(Ln, var_x));
    afficher_details(expr4, &var_x, Expr(1)); // ln(1) = 0 et e^1 = e

    // Test 5 : sqrt(x) + x^3 - 5x
    Expr expr5(Add, Expr(Sqrt, var_x), Expr(Sub, Expr(Pow, Expr(var_x), Expr(3)), Expr(Mul, Expr(5), var_x)));
    afficher_details(expr5, &var_x, Expr(4)); // sqrt(4) = 2

    // Test 6 : (sin(x) * cos(x)) / x^2
    Expr expr6(Div, Expr(Mul, Expr(Sin, var_x), Expr(Cos, var_x)), Expr(Pow, var_x, Expr(2)));
    afficher_details(expr6, &var_x, Expr(Div, Expr("pi"), Expr(6))); // π/6 pour voir une simplification trigonométrique
}