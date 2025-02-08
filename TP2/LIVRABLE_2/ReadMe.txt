Classe ExprArith

Organisation : 
    - Les fichiers "Expr_poly.cpp et Expr_poly.hpp" contiennent les classes dérivées de `ExprArith` du sujet.
    - Le fichier "unit_test.cpp" contient les tests unitaires pour les classes dérivées de `ExprArith`. Pour chaque méthode de ces classes, un test spécifique est défini.

Principe de Fonctionnement des Tests

Les tests sont organisés de manière à valider chaque fonctionnalité des classes dérivées de `ExprArith` à l'aide de tests automatisés. 
Le principe est le suivant :

1. Création de la structure Test
   Une structure Test est définie pour regrouper les informations nécessaires à l'exécution des tests. 
   Les champs de cette structure peuvent varier en fonction du type de test, 
   mais en général incluent l’expression à tester, la variable, l’expression de remplacement, et le résultat attendu.

Exemple de structure d’un test unitaire

struct Test {
    ExprArith* exp;                 // Expression arithmétique de départ
    Cst resultat_attendu;           // Résultat attendu après l'exécution de la méthode
};


2. Initialisation de la structure Test
   Une instance de cette structure est créée pour chaque type de test. 
   À l’intérieur de cette instance, une série de tests spécifiques est définie. 
   Chaque test contient :
        - L’expression d’entrée
        - Le résultat attendu

Exemple de test avec test_simplifie_Cst :

Test tests[] = {
    {new Cst(6, 9), Cst(2, 3)},     // Test avec un rationnel simplifiable (6/9 -> 2/3)
    {new Cst(15, 5), Cst(3, 1)},    // Test avec un rationnel simplifiable (15/5 -> 3/1)
};


3. Itération et Vérification des Tests
   Une boucle itère sur chaque test de l’instance de Test. 
   Pour chaque test, on vérifie si l'exécution de la méthode sur l’expression donnée donne bien le résultat attendu. 
   Si le test échoue, un message d’erreur est affiché avec les détails du test ayant échoué.

Exemple de boucle pour itérer sur les tests :

for (const auto& test : tests) {
    // Vérification des résultats
}


4. Résultats des Tests
   - Si tous les tests passent, un message "Réussi..." est affiché pour signaler que tous les tests sont concluants.
   - Si un ou plusieurs tests échouent, un message détaillant les erreurs est affiché pour aider à identifier la cause du problème.

Exemple de ce qu'affiche un test qui a échoué :
    - Échec : [Détails du test]


Conclusion

Une fois les tests effectués, un résumé est affiché :
- Réussi : Tous les tests (de la fonction) ont été validés avec succès.
- Échec : Un ou plusieurs tests ont échoué, avec un message détaillant les erreurs.