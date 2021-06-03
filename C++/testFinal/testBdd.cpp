// Programme de test pour la classe BDD.
// Deb by Mattei Fresi

// Commande pour compiler -> g++ testBdd.cpp ../class/BDD.cpp ../class/Capteurs.cpp -o output $(mysql_config --cflags) $(mysql_config --libs) && ./output

// include de la classe BDD.
#include "../class/BDD.h"
#include "../class/Capteurs.h"
#include <string>
#include <ctime>
using namespace std;

int main()
{
    //Initialisation des variables pour la connexion à la base de données et la requete.
    // date / heure actuelle basée sur le système actuel 
    Capteurs capteur("192.168.65.120", 502);
    time_t actuel = time(0);
    tm *ltm = localtime(&actuel);
    // afficher divers member de la structure tm.
    int annee = 1900 + ltm->tm_year;
    int mois = 1 + ltm->tm_mon;
    int jour = ltm->tm_mday;
    int heures = ltm->tm_hour;
    int minutes = ltm->tm_min;
    int consoEauCourante;
    int consoEauPluie;
    int ElectricalConso = rand() % 30;
    int waterConso = capteur.getWaterconsommation();
    const char *host = "192.168.65.54";
    const char *login = "root";
    const char *password = "root";
    const char *bdd = "Serre";
    char DATE[10];
    char archiveDate[10];
    snprintf(DATE, 11, "%d-0%d-%d\n", annee, mois, jour);
    string waterconso;
    string electricalConso;
    string date = DATE;
    string heure;
    electricalConso = to_string(ElectricalConso);
    waterconso = to_string(waterConso);
    heure = to_string(heures);
    string request = "INSERT INTO `consommation`(`eau_pluie`, `eau_courante`, `electrique`, `date`, `heure`) VALUES (" + waterconso + " , " + waterconso + ", " + electricalConso + ", '" + date + "', '" + heure + "');";
    string requestToArchive = "INSERT INTO `archives`(`eau_pluie`, `eau_courante`, `electrique`, `date`, `heure`) SELECT `eau_pluie`, `eau_courante`, `electrique`, `date`, `heure` FROM `consommation`;";
    string purgeRequest = "TRUNCATE TABLE `consommation`;";
    bool resultInitialize;
    bool resultConnexion;
    bool resultQuery;
    bool resultQueryArchivage;
    bool resultPurge;
    BDD Bdd;
    
    //Allouage de la mémoire pour l'objet MYSQL.
    //Retourne true en cas de succès et false en cas d'echec.
    resultInitialize = Bdd.initializeBdd();

    if (resultInitialize == true)
    {
        resultConnexion = Bdd.connectBdd(host, login, password, bdd);

        if (resultConnexion == true)
        {
            cout << "Connexion à la BDD OK !" << endl;
            // Méthode query pour envoyer nos requêtes.
            resultQuery = Bdd.query(request.c_str());
            if (resultQuery == true)
            {
                cout << "Insertion en base OK" << endl;

                if (heures == 16)
                {
                    resultQueryArchivage = Bdd.query(requestToArchive.c_str());

                    if (resultQueryArchivage == true)
                    {
                        cout << "Archivage OK" << endl;
                        resultPurge = Bdd.query(purgeRequest.c_str());
                        Bdd.closeBdd();

                        if (resultPurge == true)
                        {
                            cout << "Table purge" << endl;
                        }
                        else
                        {
                            cout << "Pas réussi à purger" << endl;
                        }
                    }
                    else
                    {
                        cout << "Pas réussi à archiver" << endl;
                    }
                }
                else
                {
                    cout << "Pas la bonne heure pour archiver" << endl;
                }
            }
            else
            {
                cout << "Pas réussi à connecter à la BDD" << endl;
            }
        }
        else
        {
            cout << "Pas réussi à insert en base" << endl;
        }
    }
    else
    {
        cout << "Pas réussi à connecter à la BDD" << endl;
    }
/* 
    Méthode connectBDD qui prend en paramètre :
        const char *host, 
        const char *user, 
        const char *passwd, 
        const char *db, 
    */
//Permet la connexion à la base de données.

//Méthode query qui permet de faire une requête en BDD.
//Prend en paramètre : const char * request.
}
