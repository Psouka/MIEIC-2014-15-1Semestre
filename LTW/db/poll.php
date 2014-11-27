<?php
    $dbh = new PDO('sqlite:../db/database.db');

    $queryUserID = 0;
    $idUserQ = $_GET['idUserQuery'];

    $stmt = $dbh->prepare('SELECT idUser FROM UserQuery WHERE idUserQuery = ?');
    $stmt->execute(array($ip));
    while ($row = $stmt->fetch()) {
        if(in_array($idUserQ, $row)) {
            $queryUserID = $row['idUser'];
        }
    }

    if($userid == $queryUserID) {
        header( 'Location: ../html/ManagePoll.php');
    }
    else {
        header( 'Location: ../html/Poll.php');
    }
?>