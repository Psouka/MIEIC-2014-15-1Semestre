<?php
$db = new PDO('sqlite:database.db');
$db->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );
$result = array();

session_start();

if(isset($_SESSION['username']))
  $usernameIP = $_SESSION['username'];
else
  $usernameIP = "Guest";

if(isset($_SESSION['idUser']))
  $userid = $_SESSION['idUser'];

$ip = $_SESSION['ip'];

if(isset($_GET['username'])){ 
  $username = $_GET['username'];

  $stmt = $db->prepare('SELECT idUser FROM User WHERE username = ?');
  $stmt->execute(array($username));  
  $temp = $stmt->fetch();


  $userId = $temp['idUser'];
  if($usernameIP !== $username){ 
    $stmt = $db->prepare('SELECT Question FROM UserQuery WHERE idUser = ? and Privacy = ?');
    $stmt->execute(array($userId,0));
  }
  else{ 
    $stmt = $db->prepare('SELECT Question FROM UserQuery WHERE idUser = ?');
    $stmt->execute(array($userId));
  }


  $Polls = $stmt->fetchAll();

  foreach ($Polls as $tempPoll)
    $result[] = $tempPoll['Question'];    
}

if(isset($_GET['id'])){

  $id = $_GET['id'];
  $stmt = $db->prepare('SELECT Question FROM UserQuery WHERE idUserQuery = ? and Privacy = ? or idUserQuery = ? and idUser = ?');
  $stmt->execute(array($id,0,$id,$userid));
  $Poll = $stmt->fetch();

  if(!empty($Poll))
    $result[] = $Poll['Question'];
}

if(isset($_GET['word'])){

  $word = $_GET['word'];

  $stmt = $db->prepare('SELECT Question FROM UserQuery WHERE Privacy = ? or idUser = ?');
  $stmt->execute(array(0,$userid));
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