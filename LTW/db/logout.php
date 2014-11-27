<?php
session_start();
	$dbh = new PDO('sqlite:database.db');

	$username = $_SESSION['usernameOn'];
	$ip = $_SESSION['ipOut'];


	$stmt1 = $dbh->prepare('DELETE FROM UserLogin WHERE IPUser = ?');
 	$stmt1->execute(array($ip));


header( 'Location: ../html/page.php' );
?>