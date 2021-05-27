<?php
include('ConfigConnexion.php');
include('../class/capteurs.php');

$buf = "water";
$electrique = rand(0, 100);
$date = date("H");
$tabData[2];

$capteursObject = new capteurs;

$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);

$result = @socket_connect($socket, $adress, $port);

@socket_send($socket, $buf, strlen($buf), 0);

$WaterConso = @socket_read($socket, 60, PHP_BINARY_READ);

$eau_pluie = $WaterConso;
$eau_courante = $eau_pluie;

//$capteursObject->insertBDDConso($eau_pluie, $eau_courante, $electrique, $date);

$tabData[0] = $WaterConso;
$tabData[1] = $date;

echo json_encode($tabData);

socket_close($socket);

?>
