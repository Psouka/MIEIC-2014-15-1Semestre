<?php

session_start();

$dbh = new PDO('sqlite:database.db');
$dbh->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );

function randomPassword() {
	$alphabet = "abcdefghijklmnopqrstuwxyzABCDEFGHIJKLMNOPQRSTUWXYZ0123456789";
    $pass = array(); //remember to declare $pass as an array
    $alphaLength = strlen($alphabet) - 1; //put the length -1 in cache
    for ($i = 0; $i < 8; $i++) {
    	$n = rand(0, $alphaLength);
    	$pass[] = $alphabet[$n];
    }
    return implode($pass); //turn the array into a string
}

$_SESSION['errNum'] = 'NoEmailReset';
$email = $_POST['email'];
$newPw = randomPassword();

$stmt = $dbh->prepare('SELECT email FROM User WHERE email = ?');
$stmt->execute(array($email));

while ($row = $stmt->fetch()) {
	if (in_array($email, $row)) {
		$to      = $email;
		$subject = 'Password Reset Request';
		$message = 'Your new password is: ' . $newPw . "\r\n\r\n" . "To change this temporary password go to your profile area and change it.";
		$headers = 'From: adminerino@pollerino.com' . "\r\n" .
		'Reply-To: adminerino@pollerino.com' . "\r\n" .
		'X-Mailer: PHP/' . phpversion();

		mail($to, $subject, $message, $headers);
		break;
	}
}

header( 'Location: ../html/page.php' );

exit();
?> 