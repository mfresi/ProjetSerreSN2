#include <iostream>
#include <mysql/mysql.h>
 
using namespace std;
 
int main()
{
    char *host = "mysql-projet-serre-eau.alwaysdata.net";
    char *user = "231030_projet"    
    char *pass = "SerreEau1234";
    char *db = "projet-serre-eau-bbdeau";
 
    MYSQL *sock;
    sock = mysql_init(0);
    if (sock) cout << "sock handle ok!" << endl;
    else {
         cout << "sock handle failed!" << mysql_error(sock) << endl;
    }
 
    if (mysql_real_connect(sock, host, user, pass, db, 0, NULL, 0))
         cout << "connection ok!" << endl;
    else {
         cout << "connection fail: " << mysql_error(sock) << endl;
    }
 
    cout << "connection character set: " << mysql_character_set_name(sock) << endl;
 
    system("PAUSE");
 
    mysql_close(sock);
 
    return EXIT_SUCCESS;
}