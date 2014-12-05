<?php
session_start(); 
$dbh = new PDO('sqlite:database.db');

if( isset($_POST['idQuery']) and isset($_POST['Comment']) and isset($_POST['Username']) ){ 
	$idQuery = $_POST['idQuery'];
	$username = $_POST['Username'];
	$comment = $_POST['Comment'];

	if($username != 'Guest')
	{
		$stmt = $dbh->prepare('SELECT idUser FROM User WHERE username = ?');
		$stmt->execute(array($username));
		$row = $stmt->fetch();
		$idUser = $row['idUser'];

		
		$stmt = $dbh->prepare('INSERT INTO PollComment (idUserQuery,idUser,Comment) VALUES (?,?,?)');
		$stmt->execute(array($idQuery,$idUser,$comment));


		echo 'commented';
	}
	else
		echo 'U WUT MATE';

}
else
	echo 'No fun';
?>