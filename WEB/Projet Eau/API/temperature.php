<?php include ("API/ConfigConnexion.php");
?>
<?php
$buf = "temp";

$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);

$result = @socket_connect($socket, $adress, $port);

@socket_send($socket, $buf, strlen($buf), 0);

$receiveC = @socket_read($socket, 60, PHP_BINARY_READ);

echo json_encode($receiveC);

socket_close($socket);

?>