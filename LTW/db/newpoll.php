<?php

function get_tiny_url($url)  {  
	$ch = curl_init();  
	$timeout = 5;  
	curl_setopt($ch,CURLOPT_URL,'http://tinyurl.com/api-create.php?url='.$url);  
	curl_setopt($ch,CURLOPT_RETURNTRANSFER,1);  
	curl_setopt($ch,CURLOPT_CONNECTTIMEOUT,$timeout);  
	$data = curl_exec($ch);  
	curl_close($ch);  
	return $data;  
}


session_start(); 
	$dbh = new PDO('sqlite:database.db');
$dbh->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );
	$username = $_SESSION['usernameOn'];
	$quest = $_POST['Question'];
	$option = $_POST['myInputs'];
	$image = $_POST['queryImage'];

	$new_url = get_tiny_url($image);

echo('depois');
if($username != 'test')
{


	$stmt = $dbh->prepare('SELECT idUser FROM User WHERE username = ?');
	$stmt->execute(array($username));
	$row = $stmt->fetch();


	$stmt = $dbh->prepare('INSERT INTO UserQuery (idUser,Question,Image) VALUES (?, ?, ?)');
	$stmt->execute(array($row['idUser'], $quest,$new_url));



	$stmt = $dbh->prepare('SELECT idUserQuery FROM UserQuery  WHERE Question = ?');
	$stmt->execute(array($quest));
	$row = $stmt->fetch();

foreach ($option as $temp) {
    $stmt = $dbh->prepare('INSERT INTO Answer (idUserQuery,Answerino) VALUES (?, ?)');
	$stmt->execute(array($row['idUserQuery'], $temp));
}
	


}
else
	echo('U WUT MATE');

header( 'Location: ../html/createPoll.php' );
exit();
?>