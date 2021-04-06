#include <iostream>
#include <mysql/mysql.h>
#include <cstring>

using namespace std;

// command to compile file -> g++ nameFile.cpp -o output -L/usr/include/mariadb/mysql -lmariadbclient && ./output

int main(void)
{
    MYSQL mysql;
    char response;
    int result;
    const char * request = "INSERT INTO `consommation`(`eau_pluie`, `eau_courante`, `electrique`) VALUES (12, 45, 24);";

    mysql_init(&mysql);
    
    if(mysql_real_connect(&mysql,"mysql-projet-serre-eau.alwaysdata.net","231030_mattei","37pgmh55","projet-serre-eau_bddeau",0,NULL,0))
    {
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

    mysql_close(&mysql);
    return 0;
}