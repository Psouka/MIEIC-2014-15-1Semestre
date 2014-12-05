<?php
$db = new PDO('sqlite:database.db');

$db->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );

$array = array();

if(isset($_GET['numPag'])){ 
	$numP = $_GET['numPag'];
}
else {
	$numP= 0;
}
$var = $numP * 10;
$limit = $var + 10;

$stmt = $db->prepare("SELECT Question FROM UserQuery WHERE Privacy = ? and rowid >= '$var' and rowid < '$limit' ");
$stmt->execute(array(0));

$Temperino = $stmt->fetchAll();

foreach ($Temperino as $temp)
		$array[] = $temp['Question'];

echo json_encode($array);
// Retorna numa array as perguntas não privadas
?>