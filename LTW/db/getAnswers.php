<?php
  $db = new PDO('sqlite:database.db');
  $db->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );

  $array = array();

  if(isset($_GET['idQuery'])){ 
	$idQ = $_GET['idQuery'];

	$stmt = $dbh->prepare("SELECT Answerino FROM Answer WHERE idUserQuery = ?");
	$stmt->execute(array($idQ));
	$Temperino = $stmt->fetchAll();


	foreach ($Temperino as $temp)
    $array[] = $temp['Answerino'];  
}


echo json_encode($array);
// Retorna numa array as respostas para uma pergunta ex: [resposta1,resposta2,resposta3]
?>