<?php
session_start(); 
$dbh = new PDO('sqlite:database.db');

if( isset($_GET['idQuery']) and isset($_GET['OptionX']) and isset($_GET['Username']) ){ 
	$idQuery = $_GET['idQuery'];
	$OptionX= $_GET['OptionX'];
	$username = $_GET['Username'];

	if($username != 'test')
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


		$stmt = $dbh->prepare('SELECT idAnswer FROM Answer WHERE Answerino = ?');
		$stmt->execute(array($OptionX));
		$row = $stmt->fetch();
		$idAnswer = $row['idAnswer'];

		$stmt = $dbh->prepare('INSERT INTO UserAnswer (idUser,idAnswer,idUserQuery) VALUES (?,?,?)');
		$stmt->execute(array($idUser,$idAnswer,$idQuery));

		echo 'registed';
	}
	else
		echo 'U WUT MATE';

}
else
	echo 'No fun';
?>