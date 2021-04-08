// ConsoleApplication2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <iostream>
#include <cstdlib>
#include <time.h> 
#include <SystemData.h>
#include <Actionneurs.h>
#include <ModBusTCPClient.h>
	int main()
	{	
		SystemData Capteurs; //On récupere les informations dans le cache de SystemData
		ModBusTCPClient CapteursTCP;
		Actionneurs Test(10);
		
		CapteursTCP.WriteBit(3, true);
		Test.SetValue(true);


		int temp;
		temp = Capteurs.Temperature;
		//temp = rand() % 10;
		//cuve du bas
		bool WaterLevel1;
		WaterLevel1 = Capteurs.NiveauEau1;
		//cuve du haut niveau haut
		bool WaterLevel3;
		WaterLevel3 = Capteurs.NiveauEau3; 

		std::cout << temp;
		std::cout << " Degres" << std::endl;
		std::cout << "Niveau de la cuve du bas : ";
		std::cout << WaterLevel1 << std::endl;
		std::cout << "Niveau de la cuve du haut : ";
		std::cout << WaterLevel3 << std::endl;

		//On active la pompe en fonction de la temperature, du niveau d'eau des cuves

		if (temp < 2)
		{ //On verifie la temperature pour eviter que l'eau soit gelé (temp > 1 au minimum)
			std::cout << "La température est trop basse \n";
			CapteursTCP.WriteWord(3, true);
		}
		else if (WaterLevel1 == 0)
		{    //On verifie si la cuve de pluie(bas) est déja remplie (0 = Vide, 1 = remplie)
			CapteursTCP.WriteBit(6, false);
			std::cout << "Le niveau d'eau de pluie (cuve bas) est trop bas \n";
		}
		else if (WaterLevel3 == 0)
		{    //On verifie si la cuve de pluie(haut) est déja remplie ou non(0 = Vide, 1 = remplie)
			CapteursTCP.WriteBit(5, false);
			std::cout << "Pas assez d'eau dans la cuve de pluie (haut) \n";
			std::cout << "On verifie la pompe \n";

			if (temp < 2)
			{ //On verifie la temperature pour eviter que l'eau soit gelé (temp > 1 au minimum)
				std::cout << "La temperature est trop basse pour utiliser la pompe donc on utilise l'eau courante \n";
				CapteursTCP.WriteWord(3, true);
			}
			else if (WaterLevel1 == 0)
			{    //On verifie si la cuve de pluie(bas) est remplie (0 = Vide, 1 = remplie)
				std::cout << "Impossible d'utiliser la pompe car niveau de pluie trop bas (cuve bas) \n";
				CapteursTCP.WriteBit(6, false);
			}

			else if (WaterLevel3 == 1)
			{    //On verifie si la cuve de pluie(haut) est déja remplie (0 = Vide, 1 = remplie)
				std::cout << "La cuve du haut est déja remplie, ne pas remplir \n";
				CapteursTCP.WriteBit(5, true);
			}

			else if (temp >= 2 && WaterLevel1 == 1 && WaterLevel3 == 0)
			{
				CapteursTCP.WriteWord(3, false);
				CapteursTCP.WriteBit(6, true);
				CapteursTCP.WriteBit(5, false);

				std::cout << " On peut activer la pompe \n";

				if(WaterLevel3 == 0) {
					//On laisse la pompe active tant que le niveau d'eau n'est pas suffisant
					//On l'arrete au moment ou le Waterlvl3 arrive a 1
					std::cout << "on laisse la pompe active \n";
					WaterLevel3 = 1;
					CapteursTCP.WriteBit(3,true);
				}
			 if (WaterLevel3 == 1) {
					std::cout << "Le niveau d'eau max a ete atteinds \n";
					std::cout << "on eteinds la pompe \n";
					CapteursTCP.WriteBit(5, true);
				}
				
			}
		}
		if (temp >= 2 && WaterLevel1 == 1 && WaterLevel3 == 1)
		{    //On verifie si la cuve de pluie(haut) est déja remplie (0 = Vide, 1 = remplie)
			CapteursTCP.WriteWord(3, false);
			CapteursTCP.WriteBit(6, true);
			CapteursTCP.WriteBit(5, true);
			std::cout << "On peut utiliser l'eau de pluie \n";
		}
		else {
			CapteursTCP.WriteWord(3 /*La temperature */, false);
			CapteursTCP.WriteBit(6 /*Le capteur cuve du bas */, false);
			CapteursTCP.WriteBit(5 /*Le capteur haut cuve du haut */, false);
		}

	}
