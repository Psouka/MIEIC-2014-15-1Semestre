<?php

	$dbh = new PDO('sqlite:database.db');

	$username = $_POST['usernameL'];
	$password = $_POST['passwordL'];

	$check = 0;
	$stmt = $dbh->prepare('SELECT username, password FROM User WHERE username = ? AND password = ?');
	$stmt->execute(array($username, $password));

	while ($row = $stmt->fetch()) {
		//print_r($row);
 		if (in_array($username, $row)) {
 			if ($password === $row['password']) {
 				$check = 1;
 				printf ("Welcome back, %s!", $row['username']);
 				break;
 			}
 			//else echo("asd");
 		}
 		//echo("asd");
	}
	if($check == 0)
		echo('Sorry bro, wrong username or password :(');

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