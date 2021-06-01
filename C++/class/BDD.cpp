#include "BDD.h"

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
void BDD::closeBdd()
{
    mysql_close(&mysql);
}