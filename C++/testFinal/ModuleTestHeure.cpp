#include <iostream>
#include <ctime>
using namespace std;
int main( ) {
   // date / heure actuelle basée sur le système actuel
   time_t actuel = time(0);
   tm *ltm = localtime(&actuel);
   // afficher divers member de la structure tm.
   int annee = 1900 + ltm->tm_year; 
   int mois = 1 + ltm->tm_mon;
   int jour = ltm->tm_mday;
   int heures = ltm->tm_hour;
   char test[10];

    snprintf(test,11,"%d-0%d-%d\n",annee,mois,jour);

    cout << test << endl;
}