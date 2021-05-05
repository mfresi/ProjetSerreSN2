<?php include ('class/capteurs.php'); ?>


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>



    <form action ="" method="POST">
    <input type="submit" name="truncate" value="archiver données">
    </form>
    <form>
    <input type="submit" name="afficher" value="afficher données">
    </form action ="" method="POST">
    <?php
    if(isset($_POST['afficher']))
    {
        $requete = ("SELECT * FROM `consommation`");
        echo $requete;
    }
    if(isset($_POST['truncate']))
    {
    $requete = ("SELECT * FROM `consommation`");
    $requete2 = ("INSERT INTO `test`(`id_consommation`, `eau_pluie`, `eau_courante`, `electrique`, `date`) VALUES ('?,?,?,?')");
    $requete3 =("TRUNCATE TABLE `consommation`");
    }
?>
</body>
</html>



