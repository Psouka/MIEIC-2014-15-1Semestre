<?php

	$dbh = new PDO('sqlite:database.db');

	$userid = $_POST['usernameOut'];
	$ip = $_POST['ipOut'];

	$check = 0;
	$stmt = $dbh->prepare('SELECT idUser FROM UserLogin');
	$stmt->execute();

	while ($row = $stmt->fetch()) {
 		if (in_array($userid, $row)) {
 			if ($username === $row['username']) {
 				$check = 1;
 				printf ("Good Bye, %s!", $row['username']);

 				$stmt1 = $dbh->prepare('DELETE FROM UserLogin WHERE username = ? and IPUser = ?');
 				$stmt1->execute();
 				break;
 			}
 		}
	}
	if($check == 0)
		echo('Something wrong :(');

header( 'Location: ../html/page.php' );
?>