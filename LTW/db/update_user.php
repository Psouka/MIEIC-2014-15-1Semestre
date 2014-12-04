<?php
$dbh = new PDO('sqlite:database.db');
$dbh->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );
session_start();
$idU = $_SESSION['idQuery'];

if(isset($_POST['Age']))
{
	$stmt = $dbh->prepare("UPDATE User SET age = ?  WHERE idUser = ?");
	$stmt->execute(array($_POST['Age'],$idU));
	
}

if(isset($_POST['Gender']))
{
	$stmt = $dbh->prepare("UPDATE User SET gender = ?  WHERE idUser = ?");
	$stmt->execute(array($_POST['Gender'],$idU));
	
}


if(isset($_POST['FirstName']))
{

	if(preg_match('/[a-zA-Z]/',$_POST['newImage']))
	{
		$stmt = $dbh->prepare("UPDATE User SET firstName = ?  WHERE idUser = ?");
		$stmt->execute(array($_POST['FirstName'],$idU));
	}
	
}

if(isset($_POST['LastName']))
{

	if(preg_match('/[a-zA-Z]/',$_POST['newImage']))
	{
		$stmt = $dbh->prepare("UPDATE User SET lastName = ?  WHERE idUser = ?");
		$stmt->execute(array($_POST['LastName'],$idU));
	}
	
}

?>