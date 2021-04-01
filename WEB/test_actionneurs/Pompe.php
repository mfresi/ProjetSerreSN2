<?php

$temp = "3";
//cuve du bas
$WaterLevel1 = 1;
//cuve du haut niveau bas
$WaterLevel2 = 0;
//cuve du haut niveau haut
$WaterLevel3 = 1;

//On active la pompe en fonction de la temperature, du niveau d'eau des cuves

    //On active la pompe en fonction de la temperature, du niveau d'eau des cuves
   if ($temp <= '2')
   { //On verifie la temperature pour eviter que l'eau soit gelé (temp > 1 au minimum)
        echo "La temperature est trop basse pour utiliser la pompe donc on utilise l'eau courante";
   }
   else if ($WaterLevel1 == 0)
   {    //On verifie si la cuve de pluie(bas) est déja remplie (0 = Vide, 1 = remplie)
        echo "Le niveau d'eau de pluie (cuve bas) est trop bas";
   }

   else if ($WaterLevel3 == 1)
   {    //On verifie si la cuve de pluie(haut) est déja remplie (0 = Vide, 1 = remplie)
        echo "La cuve du haut est déja remplie, ne pas remplir";
   }

    else if ($temp >= '2' && $WaterLevel1 == 1 && $WaterLevel3 == 0)
   {
       echo "On peut activer la pompe"; 
       
       while ($WaterLevel3 != 1) {
           //On laisse la pompe active tant que le niveau d'eau n'est pas suffisant
            echo "on laisse la pompe active";
        }
   }
       
        
