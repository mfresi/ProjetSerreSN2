#include <iostream>
#include <string>

using namespace std;

/* Convert char to...

atoi(chaine) fournit un résultat de type int ;
atol(chaine) fournit un résultat de type long ;
atof(chaine) fournit un résultat de type float.
atod(chaine) fournit un résultat de type double.

*/

void verifEtatNiveauEau(int numberOfCapteur, int value)
{
    if (value == 1)
    {
        cout << "le capteur de niveau d'eau " << numberOfCapteur << " est à l'état haut" << endl;
    }
    else
    {
        cout << "le capteur de niveau d'eau est à l'état bas" << endl;
    }
}

int main()
{
    char bufferTemp[512] = "22.5";
    char bufferNiv1[512] = "0";
    char bufferNiv2[512] = "1";
    char bufferNiv3[512] = "1";

    float temperature =  atof(bufferTemp);
    int niveauEau1 = atoi(bufferNiv1);
    int niveauEau2 = atoi(bufferNiv2);
    int niveauEau3 = atoi(bufferNiv3);

    cout << "Chaine envoyée " << bufferTemp << endl;
    cout << "Chaine envoyée " << bufferNiv1 << endl;
    cout << "Chaine envoyée " << bufferNiv2 << endl;
    cout << "Chaine envoyée " << bufferNiv3 << endl << endl;

    cout << "Temperature après conversion " << temperature << endl;
    verifEtatNiveauEau(1, niveauEau1);
    verifEtatNiveauEau(2, niveauEau2);
    verifEtatNiveauEau(3, niveauEau3);

    return 0;
}