<?php include ('class/capteurs.php'); ?>


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta charset="utf-8">
    <title>Archiver les données</title>
    <script src="JS/consommation.js"></script>
</head>
<body>



    <form action ="" method="POST">
    <input type="submit" name="archiver" value="archiver données">
    </form>
    <form action ="" method="POST">
    <input type="submit" name="afficher" value="afficher données">
    </form>

    <p id="conso"></p>

    <?php
    
    $conso = new capteurs;

    if(isset($_POST["afficher"]))
    {
        $conso->displayArchivage();
    }


    if(isset($_POST['archiver']))
    {
        $resultArchivage = $conso->archiveData();

        if ($resultArchivage = true)
        {
            echo "Archivage des données OK";
        }
        else
        {
            echo "pas réussi à archiver les données";
        }

        $conso->purgeTable();
    }
   /* echo $conso;
    if(isset($_POST['truncate']))
    {
    $requete = ("SELECT * FROM `consommation`");
    $requete2 = ("INSERT INTO `test`(`id_consommation`, `eau_pluie`, `eau_courante`, `electrique`, `date`) VALUES ('?,?,?,?')");
    $requete3 = ("TRUNCATE TABLE `consommation`");
    }*/
?>

</body>
</html>


