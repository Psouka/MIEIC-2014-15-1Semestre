<?php
session_start(); 
$dbh = new PDO('sqlite:database.db');

if( isset($_POST['idQuery']) and isset($_POST['OptionX']) and isset($_POST['Username']) ){ 
	$idQuery = $_POST['idQuery'];
	//$OptionX= $_POST['OptionX'];
	$OptionX = json_decode($_POST['OptionX']);
	$username = $_POST['Username'];

	if($username != 'Guest')
	{
		$stmt = $dbh->prepare('SELECT idUser FROM User WHERE username = ?');
		$stmt->execute(array($username));
		$row = $stmt->fetch();
		$idUser = $row['idUser'];
		
		$stmt = $dbh->prepare('SELECT * FROM UserAnswer WHERE idUser = ? and idUserQuery = ?');
		$stmt->execute(array($idUser,$idQuery));
		$row = $stmt->fetchAll();

		$checkVote = count($row);
		if($checkVote != 0)
		{
			echo 'Voted';
			exit();
		}

		foreach ($OptionX as $Option) {
			$stmt = $dbh->prepare('SELECT idAnswer FROM Answer WHERE Answerino = ?');
			$stmt->execute(array($Option));
			$row = $stmt->fetch();
			$idAnswer = $row['idAnswer'];

			$stmt = $dbh->prepare('INSERT INTO UserAnswer (idUser,idAnswer,idUserQuery) VALUES (?,?,?)');
			$stmt->execute(array($idUser,$idAnswer,$idQuery));
			
		}
		

		echo 'registed';
	}
	else
		echo 'U WUT MATE';

}
else
	echo 'No fun';
?>