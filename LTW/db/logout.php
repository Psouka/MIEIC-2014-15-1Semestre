<?php
session_start(); 
	$dbh = new PDO('sqlite:database.db');


	$username = $_SESSION['usernameOn'];
	$ip = $_SESSION['ipOut'];
if($username != 'test'){
	$check = 0;
	$stmt = $dbh->prepare('SELECT username, IPUser FROM UserLogin WHERE username = ?');
	$stmt->execute(array($username, $password));

	while ($row = $stmt->fetch()) {
		//print_r($row);
 		if (in_array($username, $row)) {
 			if ($username === $row['username'] and $ip === $row['IPUser']) {
 				$check = 1;
 				printf ("Good Bye, %s!", $row['username']);

 				$stmt1 = $dbh->prepare('DELETE FROM UserLogin WHERE username = ? and IPUser = ?');
 				$stmt1->execute(array($username,$ip));
 				break;
 			}
 			//else echo("asd");
 		}
 		//echo("asd");
	}
	if($check == 0)
		echo('Something wrong :(');
}
header( 'Location: ../page.html' ) ;
exit();
?>