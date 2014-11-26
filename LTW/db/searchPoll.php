<?php
  $db = new PDO('sqlite:database.db');


  $username = $_GET['username'];
  $stmt = $db->prepare('SELECT idUser FROM User WHERE username = ?');
  $stmt->execute(array($username));  
  $temp = $stmt->fetchAll();

  $userId = $temp['idUser'];

  $stmt = $db->prepare('SELECT Question FROM UserQuery WHERE idUser = ?');
  $stmt->execute(array($userId));
  $Polls = $stmt->fetchAll();

  $result = array();
  foreach ($Polls as $tempPoll)
    $result[] = $tempPoll['Question'];    

  echo json_encode($result);
?>