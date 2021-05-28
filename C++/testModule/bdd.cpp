// Programme test de connexion + insert en BDD sous linux avec la librairie mysql.h
// Dev by Mattei FRESI

#include <iostream>
#include <mysql.h>
#include <cstring>

using namespace std;

// command to compile file -> g++ bdd.cpp -o output $(mysql_config --cflags) $(mysql_config --libs) && ./output

int main(void)
{
    // Création de l'objet mysql + variables.
    MYSQL mysql;
    char response;
    int result;
    const char * request = "INSERT INTO `consommation`(`eau_courante`, `eau_pluie`, `electrique`, `heure`) VALUES (12, 45, 23);";
    const char * host = "192.168.65.54";
    const char * login = "root";
    const char * password = "root";
    const char * bdd = "Serre";

    // Allouage de la mémoire pour l'objet MYSQL.
    // Prend en paramètre un pointeur de l'objet MYSQL.

    mysql_init(&mysql);

    /* Méthode mysql_real_connect qui prend en paramètre :
    
    MYSQL *mysql, 
    const char *host, 
    const char *user, 
    const char *passwd, 
    const char *db, 
    unsigned int port, 
    const char *unix_socket, 
    unsigned long client_flag) */
    
    if(mysql_real_connect(&mysql, host, login, password, bdd,0,NULL,0))
    {
        // Requête pour insérer les consommations d'eau de pluie, eau courant et consommation electrique.
        // Prend en paramètre un pointeur de l'objet MYSQL, une requête mysql et une taille.
        // Renvoie 0 si pas de problème.
        result = mysql_real_query(&mysql, request, strlen(request));

        if (result == 0)
        {
            cout << "Insertion en base OK !" << endl;
        }
        else
        {
            cout << "Insertion en base PAS OK ! " << endl;
        }
    }
    else
    {
       cout << "Une erreur s'est produite lors de la connexion à la BDD!" << endl;
    }

    // Méthode mysql_close qui ferme la connexion.
    // Elle prend en paramètre l'objet mysql.
    mysql_close(&mysql);

    return 0;
}
