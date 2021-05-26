//Pour compiler : g++ -g ModuleTestActionneurs.cpp  ../class/Capteurs.cpp ../class/ModBusTCPClient.cpp -o TestActionneurs
#include <iostream>
#include "../class/SystemData.h"
#include "../class/Capteurs.h"
using namespace std;
int main()
{

    Capteurs Capteurs("192.168.65.120", 502); //On crée l'objet capteurs afin de récupérer les informations

    float temp;
    bool niveau1;
    bool niveau2;
    int CheckNiveauEau;

    temp = Capteurs.getTemperature();         //on récupère les informations du capteur de temperature
    CheckNiveauEau = Capteurs.getNiveauEau(); //On récupère les informations des capteurs de niveau d'eau

    //On attribue les valeurs en fonction de la trame recue
    if (CheckNiveauEau == 0)
    {
        niveau1 = 0;
        niveau2 = 0;
    }
    else if (CheckNiveauEau == 1)
    {
        niveau1 = 1;
        niveau2 = 0;
    }
    else if (CheckNiveauEau == 2)
    {
        niveau1 = 0;
        niveau2 = 1;
    }
    else if (CheckNiveauEau == 3)
    {
        niveau1 = 1;
        niveau2 = 1;
    }

    cout << "La Temperature est de : " << temp << endl;
    cout << "Le Niveau 1 est a l'état : " << niveau1 << endl;
    cout << "Le Niveau 2 est a l'état : " << niveau2 << endl;

    if (temp < 2)
    { //On verifie la temperature pour eviter que l'eau soit gelé (temp > 1 au minimum)
        std::cout << "La temperature est trop basse \n";
    }
    else if (niveau2 == 0)
    { //On verifie si la cuve de pluie(haut) est déja remplie ou non(0 = Vide, 1 = remplie)

        std::cout << "Pas assez d'eau dans la cuve de pluie (haut) \n";
        std::cout << "On verifie la pompe \n";

        if (temp < 2)
        { //On verifie la temperature pour eviter que l'eau soit gelé (temp > 1 au minimum)
            std::cout << "La temperature est trop basse pour utiliser la pompe donc on utilise l'eau courante \n";
        }
        else if (niveau1 == 0)
        { //On verifie si la cuve de pluie(bas) est remplie (0 = Vide, 1 = remplie)
            std::cout << "Impossible d'utiliser la pompe car niveau de pluie trop bas (cuve bas) \n";
        }

        else if (temp >= 2 && niveau1 == 1 && niveau2 == 0)
        {

            std::cout << " On peut activer la pompe \n";

            if (niveau2 == 0)
            {
                //On laisse la pompe active tant que le niveau d'eau n'est pas suffisant
                //On l'arrete au moment ou le Waterlvl3 arrive a 1
                std::cout << "on laisse la pompe active \n";
                niveau2 = 1;
            }
            else if (niveau2 == 1)
            {
                std::cout << "Le niveau d'eau max a ete atteinds \n";
                std::cout << "on eteinds la pompe \n";
            }
        }
    }

    if (temp >= 2 && niveau2 == 1)
    { //On verifie si la cuve de pluie(haut) est déja remplie (0 = Vide, 1 = remplie)
        std::cout << "On peut utiliser l'eau de pluie \n";
    }

    if (temp <= 1 || niveau2 == 0)
    {
        std::cout << "On peut utilise l'eau courante \n";
    }
}
