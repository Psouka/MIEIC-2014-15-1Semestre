<?php
$dbh = new PDO('sqlite:database.db');
$dbh->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );
session_start();
$idQ = $_SESSION['idQuery'];

$change = 0;


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


function changeOption($oldOp,$newOp)
{
	echo($oldOp);
	echo($newOp);
	echo("\r\n");
	$dbh = new PDO('sqlite:database.db');
	$idQ = $_SESSION['idQuery'];
	$stmt = $dbh->prepare("UPDATE Answer SET Answerino = ?  WHERE idUserQuery = ? and Answerino = ?");
	$stmt->execute(array($newOp,$idQ,$oldOp));
}



if(isset($_POST['deletePoll']))
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

	if(preg_match('/[a-zA-Z]/',$_POST['newImage']))
	{
		$newImage = $_POST['newImage'];
		$newImage = get_tiny_url($newImage);


		$stmt = $dbh->prepare("UPDATE UserQuery SET Image = ?  WHERE idUserQuery = ?");
		$stmt->execute(array($newImage,$idQ));

		$change = 1;
	}
	
}

$stmt = $dbh->prepare("SELECT Answerino FROM Answer WHERE idUserQuery = ?");
$stmt->execute(array($idQ));
$Answers = $stmt->fetchAll();

foreach ($Answers as $temp)
{

	if(isset($_POST[$temp['Answerino']]))
	{
		if (preg_match('/[a-zA-Z]/',$_POST[$temp['Answerino']])) {
			changeOption($temp['Answerino'],$_POST[$temp['Answerino']]);
			$change = 1;
		}
		
	}
}



if($change != 0)
{
	$stmt = $dbh->prepare("DELETE FROM UserAnswer WHERE idUserQuery = ?");
	$stmt->execute(array($idQ));
}

header( 'Location: ../html/ManagePoll.php' );

?>