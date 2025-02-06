#ifndef UNIT_TEST
#define UNIT_TEST

/* test le constructeur par défaut */
void test_constructeur_par_defaut();

/* test le constructeur d'entier */
void test_constructeur_cst_int();

/* test le constructeur de symbole */
void test_constructeur_cst_symb();

/* test le constructeur de variable */
void test_constructeur_variable();

/* test le constructeur d'opération unaire */
void test_constructeur_unaire();

/* test le constructeur d'opération binaire */
void test_constructeur_binaire();

/* Test le construvteur de copie (profonde) */
void test_constructeur_copie();

/* Teste l'égalité entre deux expressions */
void test_egalite();

// Fonction de test pour l'affectation
void test_affectation();

/* test la simplification d'opérateur unaire */
void test_operateur_unaire();

/* test la simplification d'opérateur binaire */
void test_operateur_binaire();

/* test du sujet */
void test_simplifie();

/* Test de la dérivation pour des expressions simples */
void test_derive_simple();

/* Test de la dérivation pour des opérateurs unaires */
void test_derive_unary();

/* Test de la dérivation pour des opérateurs binaires */
void test_derive_binary();
#endif