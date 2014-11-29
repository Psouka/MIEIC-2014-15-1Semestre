<?php
$db = new PDO('sqlite:database.db');
$db->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );

$array = array();

if(isset($_GET['idQuery'])){ 
	$idQ = $_GET['idQuery'];

	$stmt = $db->prepare("SELECT * FROM Answer WHERE idUserQuery = ?");
	$stmt->execute(array($idQ));
	$row = $stmt->fetchAll();

	$numberOptions = count($row);

	for ($i = 0,$autoinc = 1; $i < $numberOptions; $i++,$autoinc++) {
		$numberVotes = 0;

		$stmt = $db->prepare("SELECT * FROM UserAnswer WHERE idUserQuery = ? and idUserAnswer = ?");
		$stmt->execute(array($idQ,$autoinc));
		$row = $stmt->fetchAll();
		$numberVotes = count($row);
		$array[] = $numberVotes;
	}

}

echo json_encode($array);
// Retorna numa array o numero de votos de cada resposta ex: [100,10,20]
?>