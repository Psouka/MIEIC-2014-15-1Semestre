<?php
$db = new PDO('sqlite:database.db');

$db->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );

$array = array();

if(isset($_GET['idUserQuey'])){ 

	$stmt = $db->prepare("SELECT PollComment , idUser FROM Comment WHERE idUserQuery = ?");
	$stmt->execute(array($_GET['idUserQuey']));

	$Temperino = $stmt->fetchAll();

	foreach ($Temperino as $temp)
		$array[] = $temp['Question'];

	echo json_encode($array);
// Retorna numa array as perguntas não privadas
}
?>