<?php
session_start(); 
	$dbh = new PDO('sqlite:database.db');

	$idQuery = $_POST['idQuery'];
	$OptionX= $_POST['OptionX'];
	$IpUser = $_POST['IpUser'];
	$username = $_POST['Username'];

if($username != 'test')
{
	$idUser;
	$stmt = $dbh->prepare('SELECT idUser FROM User WHERE username = ?');
	$stmt->execute(array($username));
	$row = $stmt->fetch();
	$idUser = $row['idUser'];

	$stmt = $dbh->prepare('INSERT INTO UserQuery (idUser,Question) VALUES (?, ?)');
	$stmt->execute(array($row['idUser'], $quest));


	$stmt = $dbh->prepare('SELECT idUserQuery FROM UserQuery  WHERE Question = ?');
	$stmt->execute(array($quest));
	$row = $stmt->fetch();


}
else
	echo('U WUT MATE');


?>