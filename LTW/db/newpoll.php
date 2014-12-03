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

if(isset($_POST['privacy']))
	$privacy = 1;
else
	$privacy = 0;

echo($privacy);

	//$option = $_POST['myInputs'];
$image = $_POST['queryImage'];

$new_url = get_tiny_url($image);

$option = array();

$i1 = 'inputs';
$i2 = 1;
$ifinal = $i1 . $i2;
$pos = 0;

while(isset($_POST[$ifinal])) {
	$option[$pos] = $_POST[$ifinal];
	$i2++;
	$pos++;
	$ifinal = $i1 . $i2;
}

if($username != 'test')
{

	$stmt = $dbh->prepare('SELECT idUser FROM User WHERE username = ?');
	$stmt->execute(array($username));
	$row = $stmt->fetch();


	$stmt = $dbh->prepare('INSERT INTO UserQuery (idUser,Question,Image,Privacy) VALUES (?, ?, ?,?)');
	$stmt->execute(array($row['idUser'], $quest,$new_url,$privacy));



	$stmt = $dbh->prepare('SELECT idUserQuery FROM UserQuery  WHERE Question = ?');
	$stmt->execute(array($quest));
	$row = $stmt->fetch();

	foreach ($option as $temp) {
		$stmt = $dbh->prepare('INSERT INTO Answer (idUserQuery,Answerino) VALUES (?, ?)');
		$stmt->execute(array($row['idUserQuery'], $temp));
	}
	
	header( 'Location: ../html/poll.php?idUserQuery='.$row['idUserQuery']);
	exit();

}
else
	echo('U WUT MATE');

header( 'Location: ../html/createPoll.php' );
exit();
?>