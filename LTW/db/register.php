<?php
session_start();

$dbh = new PDO('sqlite:database.db');
$username = $_POST['usernameR'];
$email = $_POST['emailR'];
$password = $_POST['passwordR'];

if (preg_match('/[\'^£$%&*()}{@#~?><>,|=_+¬-]/', $username)) {
	$_SESSION['errNum'] = 'UserNotChars';
} 
else {
	$check = 0;
	$stmt1 = $dbh->prepare('SELECT `username`, `email` FROM User WHERE username = ? or email = ?');
	$stmt1->execute(array($username,$email));
	$result = $stmt1->fetchAll();
	foreach ($result as $row) {

		if ($username == $row['username']) {
			$check = 1;
			$_SESSION['errNum'] = 'UserTaken';
			break;
		}
		if ($email == $row['email']) {
			$check = 1;
			$_SESSION['errNum'] = 'EmailTaken';
			break;
		}	
	}
	if($check == 0) {
		$id1 = $dbh->prepare("SELECT count(*) FROM User");
		$id1->execute();
		$stmt2 = $dbh->prepare('INSERT INTO User (username, email, password) VALUES (?, ?, ?)');
		$stmt2->execute(array($username, $email, sha1($password)));
	}

	$to      = $email;
		$subject = 'Password Reset Request';
		$message = 'Welcome ' . $username . ' !' . ;
		$headers = 'From: adminerino@pollerino.com' . "\r\n" .
		'Reply-To: adminerino@pollerino.com' . "\r\n" .
		'X-Mailer: PHP/' . phpversion();
		mail($to, $subject, $message, $headers);
}

header( 'Location: ../html/login.php' );
exit();
?>