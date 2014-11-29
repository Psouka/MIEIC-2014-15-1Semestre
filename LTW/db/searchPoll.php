<?php
  $db = new PDO('sqlite:database.db');
  $db->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );
  $result = array();


if(isset($_GET['username'])){ 
  $username = $_GET['username'];

  $stmt = $db->prepare('SELECT idUser FROM User WHERE username = ?');
  $stmt->execute(array($username));  
  $temp = $stmt->fetch();


  $userId = $temp['idUser'];

  $stmt = $db->prepare('SELECT Question FROM UserQuery WHERE idUser = ?');
  $stmt->execute(array($userId));
  $Polls = $stmt->fetchAll();
 
  foreach ($Polls as $tempPoll)
    $result[] = $tempPoll['Question'];    
}

if(isset($_GET['id'])){
  
  $id = $_GET['id'];
  $stmt = $db->prepare('SELECT Question FROM UserQuery WHERE idUserQuery = ?');
  $stmt->execute(array($id));
  $Poll = $stmt->fetch();

   $result[] = $Poll['Question'];
}

if(isset($_GET['word'])){

  $word = $_GET['word'];

  $wordsize = strlen($word);
  if($wordsize < 3)
  {
   echo json_encode($result);
   exit(); 
  }


  $stmt = $db->prepare('SELECT Question FROM UserQuery');
  $stmt->execute();
  $Polls = $stmt->fetchAll();

  foreach ($Polls as $tempPoll){ 
    if(stripos($tempPoll['Question'],$word) !== false)
     {  
      $result[] = $tempPoll['Question'];  
    }
    }
}
  echo json_encode($result);
?>