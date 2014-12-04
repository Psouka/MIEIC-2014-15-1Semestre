<?php
$db = new PDO('sqlite:database.db');
$db->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );


if(isset($_GET['idQuery'])){ 
	$idQ = $_GET['idQuery'];

	$stmt = $db->prepare("SELECT Multiple FROM UserQuery WHERE idUserQuery = ?");
	$stmt->execute(array($idQ));
	$Temperino = $stmt->fetch();

	//$array[] = $Temperino['Multiple'];  
	echo($Temperino['Multiple']);
}

// Retorna numa array as respostas para uma pergunta ex: [1] ou [0]
?>