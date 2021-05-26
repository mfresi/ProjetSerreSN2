<?php
    include('../class/capteurs.php');

    $capteursObject = new capteurs;

    $capteursObject->getHour();

    echo json_encode($capteursObject);
?>