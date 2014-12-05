<?php
session_start();

$dbh = new PDO('sqlite:database.db');

$username = $_POST['usernameL'];
$password = $_POST['passwordL'];

$errNum = 0;
$check = 0;
$ip = 0;
$stmt = $dbh->prepare('SELECT username, password, idUser, loginAttempts, email FROM User WHERE username = ?');
$stmt->execute(array($username));

if ($row = $stmt->fetch()) {
	if (in_array($username, $row)) {
		if (sha1($password) === $row['password']) {
			$check = 1;

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
			
		}
	}
}

if($check == 0) {
	$loginAtemp = $row['loginAttempts'];
	$loginAtemp++;

	if($loginAtemp > 3)
	{
		$stmt = $dbh->prepare('UPDATE User SET loginAttempts = ? WHERE idUser = ?');
		$stmt->execute(array(0, $row['idUser']));
		$_SESSION['email'] = $row['email'];
		header( 'Location: ../db/resetPw.php' );
		exit();

	}

	$stmt = $dbh->prepare('UPDATE User SET loginAttempts = ? WHERE idUser = ?');
	$stmt->execute(array($loginAtemp, $row['idUser']));

	$_SESSION['errNum'] = 'WrongInputs';
	header( 'Location: ../html/page.php' );
}
else {
	header( 'Location: ../html/profile.php' );
	unset($_SESSION['errNum']);
}

exit();
?>