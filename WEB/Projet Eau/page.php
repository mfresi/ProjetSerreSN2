<?php include ('class/capteurs.php'); ?>
<link rel="stylesheet" href="assets/css/Button.css">


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


<div>
    <form action ="" method="POST">
    <input class="button button2" type="submit" name="archiver" value="archiver données">
    </form>
    <form action ="" method="POST">
    <input class="button button2" type="submit" name="afficher" value="afficher données">
    </form>
</div>

    <p id="conso"></p>
    <input class="button button2" type=button onclick=window.location.href="index.php" value="Retour page principale" />
    </div>
    
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

<script>
    function archiveData() {
    //pour appeler une API on utilise la méthode fetch()
    //pour appeler une API on utilise la méthode fetch()
    fetch('API/archiveDate.php').then((response) => response.json())
        .then(function(data) {
            // data est la réponse http de notre API.
            console.log(data);
            //S'il est minuit on archive les conso
            if (data == "10:12")
            {
                console.log("Archivage OK");
            }
            else
            {
                console.log("Archivage pas OK");
            }
        })
        .catch(function(error) {
            // This is where you run code if the server returns any errors
            //console.log(error);
        });
}
// On appel la fonction archiveData toutes les heures.
setInterval("archiveData()", 3600000);
</script>



