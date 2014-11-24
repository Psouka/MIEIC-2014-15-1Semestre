<?php
	$dbh = new PDO('sqlite:database.db');
	$username = $_POST['usernameR'];
	$email = $_POST['emailR'];
	$password = $_POST['passwordR'];
	$check = 0;
	$stmt1 = $dbh->prepare('SELECT username FROM User WHERE username = ?');
	$stmt1->execute(array($username));
	$result = $stmt1->fetchAll();
	foreach ($result as $row) {

 		if (in_array($username, $row)) {
 			$check = 1;
 			echo "That username has already been taken <br>
 				  Please, choose another one";
 			break;
 		}
 		if (in_array($email, $row['email'])) {
 			$check = 1;
 			echo "That email has already been taken <br>
 				  Please, choose another one";
 			break;
 		}	

	}
	if($check == 0) {
		$id1 = $dbh->prepare("SELECT count(*) FROM User");
		$id1->execute();
		$stmt2 = $dbh->prepare('INSERT INTO User (username, email, password) VALUES (?, ?, ?)');
		$stmt2->execute(array($username, $email, $password));
		printf ("YAY, Welcome to the Big Dick Club %s!", $username);
	}

?>