<?php
session_start(); 
	$dbh = new PDO('sqlite:database.db');
	$username = $_SESSION['usernameOn'];
	$ip = $_SESSION['ipOut'];

if($username != 'test'){


	$stmt = $dbh->prepare('SELECT idUser FROM User WHERE username = ?');
	$stmt->execute(array($username));
	$row = $stmt->fetch();
	

	$stmt1 = $dbh->prepare('DELETE FROM UserLogin WHERE idUser = ? and IPUser = ?');
 	$stmt1->execute(array($row['idUser'],$ip));
 	
}
header( 'Location: ../page.html' ) ;
exit();
?>