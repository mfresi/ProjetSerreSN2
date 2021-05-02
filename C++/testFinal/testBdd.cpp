// Programme de test pour la classe BDD.
// Deb by Mattei Fresi

// Commande pour compiler -> g++ testBdd.cpp ../class/BDD.cpp -o output -L/usr/include/mariadb/mysql -lmariadbclient && ./output

// include de la classe BDD.
#include "../class/BDD.h"

using namespace std;

int main()
{
    //Initialisation des variables pour la connexion à la base de données et la requete.
    const char * request = "INSERT INTO `consommation`(`eau_pluie`, `eau_courante`, `electrique`) VALUES (12, 45, 20);";
    const char *host = "mysql-projetu.alwaysdata.net";
    const char *login = "231030ei";
    const char *password = "37pgmh55";
    const char *bdd = "projet-serreau";
    bool resultInitialize;
    bool resultConnexion;
    bool resultQuery;
    BDD Bdd;

    //Allouage de la mémoire pour l'objet MYSQL.
    //Retourne true en cas de succès et false en cas d'echec.
    resultInitialize = Bdd.initializeBdd();

    if (resultInitialize == true)
    {
        cout << "Allouage de l'objet MYSQL OK" << endl;
    }
    else
    {
        cout << "Pas réussi à allouer l'objet MYSQL" << endl;
    }

    /* 
    Méthode connectBDD qui prend en paramètre :
        const char *host, 
        const char *user, 
        const char *passwd, 
        const char *db, 
    */
   //Permet la connexion à la base de données.
    resultConnexion = Bdd.connectBdd(host, login, password, bdd);

    if (resultConnexion == true)
    {
        cout << "Connexion à la BDD OK" << endl;
    }
    else
    {
        cout << "Pas réussi à connecter à la BDD" << endl;
    }

    //Méthode query qui permet de faire une requête en BDD.
    //Prend en paramètre : const char * request.
    resultQuery = Bdd.query(request);

    if (resultQuery == true)
    {
        cout << "Insertion en BDD OK" << endl;
    }
    else
    {
        cout << "Pas réussi à insérer en BDD" << endl;
    }
    
    Bdd.closeBdd();
}
