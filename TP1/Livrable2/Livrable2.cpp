#include <iostream>
#include "test_Livrable2.hpp"
#include "Rationnel.hpp"

using namespace std;

int main(void)
{
    cout << "Pour les doubles :\nU42 = " << suite_Un(42, false) << " et avec a = 2, V42 = " << suite_Vn(42,2,false) << "\n\n\n" << endl;

    //converge bien vers 2000
    cout << "##############################" << endl;
    cout << "Un avec des doubles : " << endl;
    suite_Un(15, true);
    cout << "##############################\n" << endl;

    //converge bien vers 2
    cout << "##############################" << endl;
    cout << "Un avec des Rationnels : " << endl;
    suite_Un_Rationnel(15, true);
    cout << "##############################\n" << endl;

    //converge bien vers  1.4142
    cout << "##############################" << endl;
    cout << "Vn avec des doubles : " << endl;
    suite_Vn(15, 2., true);
    cout << "##############################\n" << endl;

    //cesse de fonctionner correctement (overflow) quand n > 4
    cout << "##############################" << endl;
    cout << "Vn avec des Rationnels : " << endl;
    suite_Vn_Rationnel(15, 2., true);
    cout << "##############################\n" << endl;

    #include <iostream>

    std::cout << "u_n (en double) converge bien vers 2000 (algo en O(n)).\n"
              << "u_n (en rationnel) converge bien vers 2.\n"
              << "v_n (en double) converge bien vers 1.4142 (algo en O(n)).\n"
              << "v_n (en rationnel) cesse bien de fonctionner correctement (overflow) quand n > 4.\n"
              << "Vers quelles valeurs converge v_n pour a = 2, 4, 9, 25 ?\n"
              << "Réponse : v_n converge bien vers sqrt(2) = 1.4142, sqrt(4) = 2, sqrt(9) = 3, sqrt(25) = 5.\n"
              << "Il suffit de résoudre l'équation L = L/2 + a/(2L) où L est la limite. "
              << "En résolvant cette équation, on a L = sqrt(a).\n";

    return 0;
}
