<?php
$dbh = new PDO('sqlite:../db/database.db');
session_start();
$idPoll = $_GET['idUserQuery'];

if(isset($_SESSION['username']))
  $username = $_SESSION['username'];
else
  $username = "Guest";
$userid = $_SESSION['idUser'];

$query =  $_GET['Question'];

$stmt = $dbh->prepare('SELECT idUserQuery, idUser FROM UserQuery WHERE Question = ?');
$stmt->execute(array($query));
$temp = $stmt->fetch();

$idQ =$temp['idUserQuery'];
$idU = $temp['idUser'];


if($idU === $userid)
{
    header( 'Location: ../html/managePoll.php?idUserQuery='.$idQ);
    exit();
}


header( 'Location: ../html/poll.php?idUserQuery='.$idQ);
exit();

?>