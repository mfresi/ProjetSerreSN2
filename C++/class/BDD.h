// Déclaration de la classe BDD.
// Dev by Fresi.
#include <iostream>
#include <mysql.h>
#include <cstring>

using namespace std;

class BDD
{
private:
    MYSQL mysql;
public:
    bool initializeBdd();
    bool connectBdd(const char *host, const char *login, const char *password, const char *bdd);
    bool query(const char *request);
    void closeBdd();
};