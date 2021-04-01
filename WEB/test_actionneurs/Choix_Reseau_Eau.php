<?php

$temp = "18";
//cuve du bas
$WaterLevel1 = 1;
//cuve du haut niveau bas
$WaterLevel2 = 0;
//cuve du haut niveau haut
$WaterLevel3 = 0;

//On active la pompe en fonction de la temperature, du niveau d'eau des cuves
   if ($temp < '2')
   { //On verifie la temperature pour eviter que l'eau soit gelé (temp > 1 au minimum)
        echo "La temperature est trop basse pour utiliser l'eau de pluie \n";
   }
   else if ($WaterLevel1 == 0)
   {    //On verifie si la cuve de pluie(bas) est déja remplie (0 = Vide, 1 = remplie)
        echo "Le niveau d'eau de pluie (cuve bas) est trop bas \n";
   }
   else if ($WaterLevel3 == 0)
   {    //On verifie si la cuve de pluie(haut) est déja remplie ou non(0 = Vide, 1 = remplie)
        echo "Pas assez d'eau dans la cuve de pluie (haut) \n";

        if ($temp <= '2')
        { //On verifie la temperature pour eviter que l'eau soit gelé (temp > 1 au minimum)
             echo "La temperature est trop basse pour utiliser la pompe donc on utilise l'eau courante \n";
        }
        else if ($WaterLevel1 == 1)
        {    //On verifie si la cuve de pluie(bas) est remplie (0 = Vide, 1 = remplie)
             echo "Impossible d'utiliser la pompe car niveau de pluie trop bas (cuve bas) \n";
        }
     
        else if ($WaterLevel3 == 1)
        {    //On verifie si la cuve de pluie(haut) est déja remplie (0 = Vide, 1 = remplie)
             echo "La cuve du haut est déja remplie, ne pas remplir \n";
        }
     
         else if ($temp >= '2' && $WaterLevel1 == 1 && $WaterLevel3 == 0)
        {
            echo " On peut activer la pompe \n"; 
            
            while ($WaterLevel3 != 1) {
                //On laisse la pompe active tant que le niveau d'eau n'est pas suffisant
                //On l'arrete au moment ou le Waterlvl3 arrive a 1
                 echo "on laisse la pompe active \n";
             }
        }
   }

   else if ($temp >= '2' && $WaterLevel1 == 1 && $WaterLevel3 == 1)
   {    //On verifie si la cuve de pluie(haut) est déja remplie (0 = Vide, 1 = remplie)
        echo "On peut utiliser l'eau de pluie \n";
   } 

?>