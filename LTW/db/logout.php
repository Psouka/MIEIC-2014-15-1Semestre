<?php
session_start();
	$dbh = new PDO('sqlite:database.db');

	$username = $_SESSION['usernameOn'];
	$ip = $_SESSION['ipOut'];

	$check = 0;
	$stmt = $dbh->prepare('SELECT idUser FROM User WHERE username = ?');
	$stmt->execute(array($username));
	$row = $stmt->fetch();

	$id = $row['idUser'];


	$stmt1 = $dbh->prepare('DELETE FROM UserLogin WHERE idUser = ? and IPUser = ?');
 	$stmt1->execute(array($id,$ip));


header( 'Location: ../html/page.php' );
?>