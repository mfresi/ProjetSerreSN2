#include <iostream>
#include <mysql/mysql.h>
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