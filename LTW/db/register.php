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
 			
	}
	if($check == 0) {
		$idAccount=0;
		$id1 = $dbh->prepare("SELECT count(*) FROM User");
		$id1->execute();
		$id2 = $id1->fetch();


		$stmt2 = $dbh->prepare('INSERT INTO User (idAccount, username, email, password) VALUES (?, ?, ?, ?)');
		$stmt2->execute(array($id2[0], $username, $email, $password));
		printf ("YAY, Welcome to the Big Dick Club %s!", $username);
	}
?>

<html lang="en">
  <head>
    <title>Back to the form</title>
    <meta charset="utf-8">
  </head>

  <body>
  	<br>
 	<a href="page.html"> ---Back--- </a>
  </body>
</html>