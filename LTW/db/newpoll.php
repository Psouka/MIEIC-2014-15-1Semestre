<?php
session_start(); 
	$dbh = new PDO('sqlite:database.db');

	$username = $_SESSION['usernameOn'];
	$quest = $_POST['Question'];
	$option = $_POST['myInputs'];
	$image = $_POST['queryImage'];

	$new_url;
?>
<html lang="en">
<script src="../js/tiny.js" language="Javascript" type="text/javascript"></script>
	<script type="text/javascript">
  <?= $new_url =clone get_tiny_url($image);?>
</script>
</hmtl>
<?php
if($username != 'test')
{


	$stmt = $dbh->prepare('SELECT idUser FROM User WHERE username = ?');
	$stmt->execute(array($username));
	$row = $stmt->fetch();


	$stmt = $dbh->prepare('INSERT INTO UserQuery (idUser,Question,Image) VALUES (?, ?)');
	$stmt->execute(array($row['idUser'], $quest,$new_url));



	$stmt = $dbh->prepare('SELECT idUserQuery FROM UserQuery  WHERE Question = ?');
	$stmt->execute(array($quest));
	$row = $stmt->fetch();

foreach ($option as $temp) {
    $stmt = $dbh->prepare('INSERT INTO Answer (idUserQuery,Answerino) VALUES (?, ?)');
	$stmt->execute(array($row['idUserQuery'], $temp));
}
	


}
else
	echo('U WUT MATE');

echo($new_url);
//header( 'Location: ../html/createPoll.php' );
//exit();
?>