<?php
  $db = new PDO('sqlite:database.db');
  $db->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );

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
/*
UPDATE products 
   SET price = 12 
 WHERE name = 'coke' AND price = 8;

*/

   if(isset($_GET['idQuery']) and isset($_GET['newAnswer']) and isset($_GET['idAnswer'])){ 
	$idQ = $_GET['idQuery'];
	$idA = isset($_GET['idAnswer']);
	$newA = isset($_GET['newAnswer']);

	$stmt = $dbh->prepare("UPDATE Answer SET Answerino = ?  WHERE idUserQuery = ? and idAnswer = ?");
	$stmt->execute(array($newA,$idQ,$idA));
	}

	else if(isset($_GET['idQuery']) and isset($_GET['newQuery']))
	{
		$idQ = $_GET['idQuery'];
		$newQuery = $_GET['newQuery'];

		$stmt = $dbh->prepare("UPDATE UserQuery SET Question= ?  WHERE idUserQuery = ?");
		$stmt->execute(array($newQuery,$idQ));
	}

	else if(isset($_GET['DeleteidQuery']))
	{
		//	$stmt1 = $dbh->prepare('DELETE FROM UserLogin WHERE IPUser = ?');
		$idQ = $_GET['DeleteidQuery'];

		$stmt = $dbh->prepare("DELETE FROM UserQuery WHERE idUserQuery = ?");
		$stmt->execute(array($idQ));
	}

	else if(isset($_GET['idQuery']) and isset($_GET['newImage']))
	{
		//	$stmt1 = $dbh->prepare('DELETE FROM UserLogin WHERE IPUser = ?');
		$idQ = $_GET['idQuery'];
		$newImage = $_GET['newImage'];
		$newImage = get_tiny_url($newImage);


		$stmt = $dbh->prepare("UPDATE UserQuery SET Image = ?  WHERE idUserQuery = ?");
		$stmt->execute(array($newQuery,$idQ));
	}
?>