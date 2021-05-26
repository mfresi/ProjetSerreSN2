<?php
    include('../class/capteurs.php');

    $eau_pluie = rand(0, 100);
    $eau_courante = rand(0, 100);
    $electrique = rand(0, 100);
    $date = date("Y-m-d");

    $capteursObject = new capteurs;

    $result = $capteursObject->insertBDDConso($eau_pluie, $eau_courante, $electrique, $date);

    echo json_encode($result);
?>

<?php
    function getConsoElec()
    {
        $consoObject = new capteurs;
        $conso = $this->_bdd->query('SELECT `electrique` FROM `consommation`');
        while ($tabConso = $conso->fetch()) {
            echo ($tabConso['electrique'] . ",");

            $result = $consoObject->getWaterConsoPluie();
            echo json_encode($result);
        }
    }
?>

