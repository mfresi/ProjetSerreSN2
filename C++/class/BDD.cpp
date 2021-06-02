// Implémentation des méthodes de la classe BDD.
#include "BDD.h"
// Permet l'allouage de la mémoire pour l'objet MYSQL.
// Return true en cas de succès et false en cas d'echec.
bool BDD::initializeBdd()
{
    MYSQL * resultMysql_init;

    resultMysql_init = mysql_init(&mysql);

    if (resultMysql_init != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// Permet la connexion à la base de données.
// Return true en cas de succès et false en cas d'echec.
bool BDD::connectBdd(const char *host, const char *login, const char *password, const char *bdd)
{
    MYSQL * resultConnexionToBdd;

    resultConnexionToBdd = mysql_real_connect(&mysql, host, login, password, bdd, 0, NULL, 0);

    if (resultConnexionToBdd != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// Permet d'exécuter les requêtes SQL.
// Return true en cas de succès et false en cas d'echec.
bool BDD::query(const char *request)
{
    bool resultQuery;

    resultQuery = mysql_real_query(&mysql, request, strlen(request));

    if (resultQuery == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// Supprime l'allouage de la mémoire de l'objet MYSQL.
void BDD::closeBdd()
{
    mysql_close(&mysql);
}