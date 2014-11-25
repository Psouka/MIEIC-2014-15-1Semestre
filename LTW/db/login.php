<?php

	$dbh = new PDO('sqlite:database.db');

	$username = $_POST['usernameL'];
	$password = $_POST['passwordL'];

	$check = 0;
	$ip = 0;
	$stmt = $dbh->prepare('SELECT username, password, idUser FROM User WHERE username = ? AND password = ?');
	$stmt->execute(array($username, $password));

	while ($row = $stmt->fetch()) {
		//print_r($row);
 		if (in_array($username, $row)) {
 			if ($password === $row['password']) {
 				$check = 1;
 				printf ("Welcome back, %s!", $row['username']);

 				if (!empty($_SERVER['HTTP_CLIENT_IP'])) {
 					$ip = $_SERVER['HTTP_CLIENT_IP'];
 				} elseif (!empty($_SERVER['HTTP_X_FORWARDED_FOR'])) {
 					$ip = $_SERVER['HTTP_X_FORWARDED_FOR'];
 				} else {
 					$ip = $_SERVER['REMOTE_ADDR'];
 				}

 				$stmt2 = $dbh->prepare('INSERT INTO UserLogin (idUser, IPUser) VALUES (?, ?)');
 				$stmt2->execute(array($row['idUser'], $ip));

 				printf ("Welcome back, %s!", $row['username']);
 				break;
 			}
 			//else echo("asd");
 		}
 		//echo("asd");
	}

	if($check == 0)
		header( 'Location: ../page.html' );
	else
header( 'Location: ../html/createPoll.php' );

exit();
?>