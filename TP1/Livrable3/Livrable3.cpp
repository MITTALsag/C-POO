#include <iostream>
#include <string>
#include "Entier.hpp"
#include "test_Livrable3.hpp"


int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        std::cout << "Usage : \n"
                  << "./Livrable3 runTests : lance le test \"runTests\".\n"
                  << "./Livrable3 factorial_Entier lance la test de la factoriel avec la classe Entier.\n"
                  << "./Livrable3 factorial_int lance la test de la factoriel avec les entier classique.\n"
                  << "./Livrable3 Un lance la test de la suite Un.\n"
                  << "./Livrable3 Vn lance la test de la suite Vn.\n"
                  << std::endl;
        return 1;
    }
    if (std::string(argv[1]) == "runTests")
        runTests();
    else if (std::string(argv[1]) == "factorial_Entier")
    {
        Entier ent = (1234);
        Entier E = factorial(ent);
        std::cout << ent << "! = " << E << std::endl;
        std::cout << "\n\n\nle résultat semble correct :\nVous pouvez retrouver ce résultat à l'addresse suivante : https://thefractioncalculator.com/Factorial/What-is-the-factorial-of-1234.html" << std::endl;
        std::cout << "Le résultat tirer d'internet se trouve dans le fichier theorique.txt et celui obtenu dans le fichier resultat.txt.\nJe vous invite a faire la commande \"diff resultat.txt theorique.txt\"" << std::endl;
    }
    else if (std::string(argv[1]) == "factorial_int")
    {
        for (int i = 0; i < 11 ; i++)
        {
            std::cout << i << "! = " << factorial(i) << std::endl;
        }
        std::cout << "La fonction factorial pour les entier classique semble correct.\n"
                  << "Mais si on fais : factorial(1234) on a : 1234! = " << factorial(1234) << " ce qui est impossible.\n"
                  << "Ce qui montre que pour des grand nombre les entier classique (même les uint64_t) ne sont pas adapté." << std::endl;
    }
    else if (std::string(argv[1]) == "Un")
    {
        Rationnel R = suite_Un_Rationnel(20, true);
        std::cout << "La suite converge bien vers 2.\n"
                  << "Mais c'est très lent, donc pas optimiser.\n"
                  << "Pour la suite il faudrait optimiser les algos d'opération de la classe Entier.\n"
                  << "On pourrai aussi modifier la classe Entier pour changer la base de stockage. Par exemple stocker en base 10^9.\n"
                  << std::endl;
    }
    else if (std::string(argv[1]) == "Vn")
    {
        Rationnel R = suite_Vn_Rationnel(20, 2, true);
        std::cout << "La suite converge bien vers 2.\n"
            << "Mais c'est très lent, donc pas optimiser.\n"
            << "Pour la suite il faudrait optimiser les algos d'opération de la classe Entier.\n"
            << "On pourrai aussi modifier la classe Entier pour changer la base de stockage. Par exemple stocker en base 10^9.\n"
            << std::endl;
    }

}