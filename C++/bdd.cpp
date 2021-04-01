#include <iostream>
#include <mysql/mysql.h>

using namespace std;

struct connection_details{
    const char *server, *user, *pasword, *database;
};

MYSQL * mysql_connection_setup(struct connection_details mysql_details){
    MYSQL *connection = mysql_init(NULL);

    if(!mysql_real_connections(connection, mysql_details.server, mysql_details.user, mysql_details.pasword, mysql_details.database, 0, NULL, 0))
    {
        cout << "Connection error: " << mysql_error(connection) << endl;
        exit(1);
    }

    return connection;
}

MYSQL_RES* mysql_execute(MYSQL *connection_details, const char *sql_query){
    if(mysql_query(connection, sql_query)){
        cout << "MYSQL Query error: " << mysql_error(connection) << endl;
        exit(1);
    }

    return mysql_user_results(connection);
}

int main(int argc, char const * argv[])
{
    MYSQL *request;
    MYSQL *response;
    MYSQL *row;

    struct connection_details mysqlD;
    mysqlD.server = "mysql-projet-serre-eau.alwaysdata.net";
    mysqlD.user = "231030_projet";
    mysqlD.password = "SerreEau1234";
    mysqlD.database = "projet-serre-eau-bbdeau";

    request = mysql_connection_setup(mysqlD);

    response = mysql_execute_query(request, "INSERT INTO `consommation`(`eau_pluie`, `eau_courante`) VALUES (14, 24);");

    cout << "Reponse de la requete : \n" << endl;

    while((row = mysql_fetch_row(response)) != NULL)
    {
        cout << "Eau de pluie : " << row['eau_pluie'] << "Eau courante : " << row['eau_courante'] << endl;
    }

    mysql_free_result(response);
    mysql_close(request);

    return 0;

}
