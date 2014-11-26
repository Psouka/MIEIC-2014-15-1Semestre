<?php
session_start(); 
	$dbh = new PDO('sqlite:database.db');

	$Query = $_SESSION['Query'];
	$Option= $_SESSION['OptionX'];
	$IpUser = $_SESSION['IpUser'];
	$username = $_SESSION['Username'];

if($username != 'test')
{

	$stmt = $dbh->prepare('SELECT idUser FROM User WHERE username = ?');
	$stmt->execute(array($username));
	$row = $stmt->fetch();


	$stmt = $dbh->prepare('INSERT INTO UserQuery (idUser,Question) VALUES (?, ?)');
	$stmt->execute(array($row['idUser'], $quest));



	$stmt = $dbh->prepare('SELECT idUserQuery FROM UserQuery  WHERE Question = ?');
	$stmt->execute(array($quest));
	$row = $stmt->fetch();

	$stmt = $dbh->prepare('INSERT INTO Answer (idUserQuery,Answerino) VALUES (?, ?)');
	$stmt->execute(array($row['idUserQuery'], $option1));

	$stmt = $dbh->prepare('INSERT INTO Answer (idUserQuery,Answerino) VALUES (?, ?)');
	$stmt->execute(array($row['idUserQuery'], $option2));
	
	$stmt = $dbh->prepare('INSERT INTO Answer (idUserQuery,Answerino) VALUES (?, ?)');
	$stmt->execute(array($row['idUserQuery'], $option3));

	$stmt = $dbh->prepare('INSERT INTO Answer (idUserQuery,Answerino) VALUES (?, ?)');
	$stmt->execute(array($row['idUserQuery'], $option4));


}
else
	echo('U WUT MATE');

header( 'Location: ../html/createPoll.php' );
exit();
?>