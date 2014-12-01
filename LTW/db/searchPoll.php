<?php
$db = new PDO('sqlite:database.db');
$db->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );
$result = array();


$ip = 0;
if (!empty($_SERVER['HTTP_CLIENT_IP'])) {
  $ip = $_SERVER['HTTP_CLIENT_IP'];
} elseif (!empty($_SERVER['HTTP_X_FORWARDED_FOR'])) {
  $ip = $_SERVER['HTTP_X_FORWARDED_FOR'];
} else {
  $ip = $_SERVER['REMOTE_ADDR'];
}
$usernameIP = "test";

$userid = 0;

$stmt = $db->prepare('SELECT idUser, IPUser FROM UserLogin WHERE IPUser = ?');
$stmt->execute(array($ip));

while ($row = $stmt->fetch()) {
  if(in_array($ip, $row)) {
    $userid = $row['idUser'];
    $stmt1 = $db->prepare('SELECT username, idUser FROM User WHERE idUser = ?');
    $stmt1->execute(array($userid));
    while ($row1 = $stmt1->fetch()) {
      if(in_array($userid, $row1)) {
        $usernameIP = $row1['username'];
      }
    }
  }
}



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
  $stmt = $db->prepare('SELECT Question FROM UserQuery WHERE idUserQuery = ? and Privacy = ?');
  $stmt->execute(array($id,0));
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


 $stmt = $db->prepare('SELECT Question FROM UserQuery WHERE Privacy = ?');
 $stmt->execute(array(0));
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