<?php
$dbh = new PDO('sqlite:database.db');
$dbh->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );
session_start();
$idU = $_SESSION['idUser'];

if(isset($_POST['Age']))
{
	if(is_numeric($_POST['Age'])){ 
		echo($_POST['Age']);
		$stmt = $dbh->prepare("UPDATE User SET age = ?  WHERE idUser = ?");
		$stmt->execute(array($_POST['Age'],$idU));
	}
	
}

if(isset($_POST['Gender']))
{
	echo($_POST['Gender']);
	$stmt = $dbh->prepare("UPDATE User SET gender = ?  WHERE idUser = ?");
	$stmt->execute(array($_POST['Gender'],$idU));
	
}


if(isset($_POST['FirstName']))
{
	
	if(preg_match('/[a-zA-Z]/',$_POST['FirstName'])){
		echo($_POST['FirstName']);
		$stmt = $dbh->prepare("UPDATE User SET firstName = ?  WHERE idUser = ?");
		$stmt->execute(array($_POST['FirstName'],$idU));
	}

}

if(isset($_POST['LastName']))
{

	if(preg_match('/[a-zA-Z]/',$_POST['LastName']))
	{
		echo($_POST['LastName']);
		$stmt = $dbh->prepare("UPDATE User SET lastName = ?  WHERE idUser = ?");
		$stmt->execute(array($_POST['LastName'],$idU));
	}
	
}


if(isset($_POST['newPw']) and isset($_POST['confirmPw']))
{

	if(preg_match('/[a-zA-Z]/',$_POST['newPw']) and preg_match('/[a-zA-Z]/',$_POST['confirmPw'])
		and $_POST['confirmPw'] === $_POST['newPw'])
	{
		echo($_POST['confirmPw']);
		$stmt = $dbh->prepare("UPDATE User SET lastName = ?  WHERE idUser = ?");
		$stmt->execute(array($_POST['LastName'],$idU));
	}
	
}

?>