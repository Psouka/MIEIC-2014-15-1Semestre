<?php
	$dbh = new PDO('sqlite:database.db');
	$username = $_POST['usernameR'];
	$email = $_POST['emailR'];
	$password = $_POST['passwordR'];

	if (preg_match('/[\'^£$%&*()}{@#~?><>,|=_+¬-]/', $username))
	{
		header( 'Location: ../html/page.php' );
		exit();
	}


	$check = 0;
	$stmt1 = $dbh->prepare('SELECT `username`, `email` FROM User WHERE username = ? or email = ?');
	$stmt1->execute(array($username,$email));
	$result = $stmt1->fetchAll();
	foreach ($result as $row) {

 		if (in_array($username, $row['username'])) {
 			$check = 1;
 			echo "That username has already been taken <br>
 				  Please, choose another one";
 			break;
 		}
 		if ($email == $row['email']) {
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
		$stmt2->execute(array($username, $email, sha1($password)));
	}

header( 'Location: ../html/page.php' );
exit();
?>