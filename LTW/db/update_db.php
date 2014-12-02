<?php
$dbh = new PDO('sqlite:database.db');
$dbh->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );
session_start();
function get_tiny_url($url){  
	$ch = curl_init();  
	$timeout = 5;  
	curl_setopt($ch,CURLOPT_URL,'http://tinyurl.com/api-create.php?url='.$url);  
	curl_setopt($ch,CURLOPT_RETURNTRANSFER,1);  
	curl_setopt($ch,CURLOPT_CONNECTTIMEOUT,$timeout);  
	$data = curl_exec($ch);  
	curl_close($ch);  
	return $data;  
}

$idQ = $_SESSION['idQuery'];

if(isset($_POST['newQuery']))
{
	
	$newQuery = $_POST['newQuery'];

	$stmt = $dbh->prepare("UPDATE UserQuery SET Question= ?  WHERE idUserQuery = ?");
	$stmt->execute(array($newQuery,$idQ));
}

if(isset($_POST['DeleteidQuery']))
{

	$stmt = $dbh->prepare("DELETE FROM UserQuery WHERE idUserQuery = ?");
	$stmt->execute(array($idQ));

	$stmt = $dbh->prepare("DELETE FROM Answer WHERE idUserQuery = ?");
	$stmt->execute(array($idQ));

	$stmt = $dbh->prepare("DELETE FROM UserAnswer WHERE idUserQuery = ?");
	$stmt->execute(array($idQ));
	
}

if(isset($_POST['newImage']))
{
	$newImage = $_POST['newImage'];
	$newImage = get_tiny_url($newImage);


	$stmt = $dbh->prepare("UPDATE UserQuery SET Image = ?  WHERE idUserQuery = ?");
	$stmt->execute(array($newImage,$idQ));
	
}


if(isset($_POST['newAnswer']) and isset($_POST['Answerino'])){ 

	$Ans = isset($_POST['idAnswer']);
	$newA = isset($_POST['newAnswer']);

	$stmt = $dbh->prepare("UPDATE Answer SET Answerino = ?  WHERE idUserQuery = ? and Answerino = ?");
	$stmt->execute(array($newA,$idQ,$Ans));
}


?>