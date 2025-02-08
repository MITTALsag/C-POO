Classe Expr

Oragnisation : 
    - Les fichiers "Expr.cpp et Expr.hpp" contienne la classe Expr du sujet.
    - Le fichier "unit_test.cpp" contient les tests unitaires pour la classe `Expr`. Pour chaque méthode de cette classe, un test spécifique est défini.

Principe de Fonctionnement des Tests

Les tests sont organisés de manière à valider chaque fonctionnalité de la classe Expr à l'aide de tests automatisés. 
Le principe est le suivant :

1. Création de la structure Test
   Une structure Test est définie pour regrouper les informations nécessaires à l'exécution des tests. 
   Les champs de cette structure peuvent varier en fonction du type de test, 
   maisen général incluent l’expression à tester, la variable, l’expression de remplacement, et le résultat attendu.

Exemple de structure d’un test unitaire

struct Test {
    Expr expr;           // Expression de départ
    Expr var;            // Variable à remplacer (si applicable)
    Expr remplacement;   // Expression de remplacement (si applicable)
    Expr resultat_attendu; // Résultat attendu après l'exécution de la méthode
};


2. Initialisation de la structure Test
   Une instance de cette structure est créée pour chaque type de test. 
   À l’intérieur de cette instance, une série de tests spécifiques est définie. 
   Chaque test contient :
        - L’expression d’entrée
        - La variable à remplacer (si applicable)
        - L’expression de remplacement (si applicable)
        - Le résultat attendu

Exemple de test avec test_subs :

Test tests[] = {
    {Expr('x'), Expr('x'), Expr(42), Expr(42)}, // Substitution d'une variable seule
    {Expr('x'), Expr('y'), Expr(42), Expr('x')}, // Substitution sans effet
};


3. Itération et Vérification des Tests
   Une boucle itère sur chaque test de l’instance de Test. 
   Pour chaque test, on vérifie si l'exécution de la méthode sur l’expression donnée donne bien le résultat attendu. 
   Si le test échoue, un message d’erreur est affiché avec les détails du test ayant échoué.

Exemple de boucle pour iterer sur les tests :

for (const auto& test : tests) {
    // Vérification des résultats
}


4. Résultats des Tests
   - Si tous les tests passent, un message "Réussi..." est affiché pour signaler que tous les tests sont concluants.
   - Si un ou plusieurs tests échouent, un message détaillant les erreurs est affiché pour aider à identifier la cause du problème.

Exemple de ce q'affiche une test qui a échoué :
    - Échec : [Détails du test]


Test de Précision

Lors de certains tests, notamment ceux concernant des calculs flottants, une tolérance de précision peut être appliquée. 
Par exemple, pour les résultats attendus avec des expressions mathématiques, une tolérance de `1e-12` peut être définie pour valider que les résultats sont proches de la valeur attendue.

Exemple d’utilisation de la tolérance :

if (fabs(result - test.resultat_attendu) > tolerance) {
    // Affichage de l'erreur si la différence est trop grande
}


Conclusion

Une fois les tests effectués, un résumé est affiché :
- Réussi : Tous les tests (de la fonction) ont été validés avec succès.
- Échec : Un ou plusieurs tests ont échoué, avec un message détaillant les erreurs.
