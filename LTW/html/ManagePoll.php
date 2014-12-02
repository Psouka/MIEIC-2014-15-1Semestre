<?php
session_start();


$dbh = new PDO('sqlite:../db/database.db');

$idPoll = $_GET['idUserQuery'];
$ip = 0;
if (!empty($_SERVER['HTTP_CLIENT_IP'])) {
  $ip = $_SERVER['HTTP_CLIENT_IP'];
} elseif (!empty($_SERVER['HTTP_X_FORWARDED_FOR'])) {
  $ip = $_SERVER['HTTP_X_FORWARDED_FOR'];
} else {
  $ip = $_SERVER['REMOTE_ADDR'];
}
$username = "test";

$userid = 0;

$stmt = $dbh->prepare('SELECT idUser, IPUser FROM UserLogin WHERE IPUser = ?');
$stmt->execute(array($ip));

while ($row = $stmt->fetch()) {
  if(in_array($ip, $row)) {
    $userid = $row['idUser'];
    $stmt1 = $dbh->prepare('SELECT username, idUser FROM User WHERE idUser = ?');
    $stmt1->execute(array($userid));
    while ($row1 = $stmt1->fetch()) {
      if(in_array($userid, $row1)) {
        $username = $row1['username'];
      }
    }
  }
}

$stmt = $dbh->prepare('SELECT idUser FROM UserQuery WHERE idUserQuery = ?');
$stmt->execute(array($idPoll));
$row = $stmt->fetch();

if($userid != $row['idUser']){
  header( 'Location: ../html/profile.php' );
  exit();
}

$stmt2 = $dbh->prepare('SELECT Question, Image FROM UserQuery WHERE idUserQuery = ?');
$stmt2->execute(array($idPoll));
$row = $stmt2->fetch();

$QuestionPoll = $row['Question'];
$ImagePoll = $row['Image'];


$pollOptions = array();
$stmt = $dbh->prepare('SELECT Answerino FROM Answer WHERE idUserQuery = ?');
$stmt->execute(array($idPoll));
while ($row = $stmt->fetch()) {
  array_push($pollOptions,$row['Answerino']);
}


?>

<html lang="en">
<head>
  <script src="../resources/jquery-1.9.1.js"></script>
  <script src="../resources/d3.v3.min.js"> </script>
  <script type="text/javascript" src="../js/page.js"></script>
  <title>Pollerino</title>
  <link rel="shortcut icon" href="../resources/icon.ico"/>
  <meta charset="utf-8">
  <link rel="stylesheet" href="../css/poll.css" hreflang="en">
  <link rel="stylesheet" href="../css/chart.css" hreflang="en">
</head>
<body>
  <?php  session_start();   $_SESSION['usernameOn'] = $username;  $_SESSION['ipOut'] = $ip; ?>
  <div class="LogoutM">
    <form action="createPoll.php" method="post">
      <ul class="Home"> 
        <li>
         <p><center><?= $username ?></center></p>
       </li>
       <li>
         <input type="submit" value="Home" class="buttonOut" />
       </li>
     </ul>
   </form>   
   <ul class="Logout"> 
    <form action="../db/logout.php" method="post">
      <li>
       <input type="submit" value="Log Out" class="buttonOut" />
     </li>
   </form>
 </ul>      
</div>
<div id ="container" class="container">
  <div class="flat-form">
    <ul class="tabs">
      <li>
        <a href="#Poll" class="active">Poll Statistics</a>
      </li>
      <li>
        <a href="#ManagePoll">Manage Poll</a>
      </li>
    </ul>

    <div id="Poll" class="form-action show">
      <form>
        <ul>
          <li>
            <h1> <?= $QuestionPoll ?></h1>
          </br>
        </li>
        <img src= "<?php echo $ImagePoll ?>">
      </br></br>
      <h2>Options:</h2>
    </ul>
    <p>
      <div class="chart"></div>
      <script src="../js/chart.js">
      </script>
      <input type="button" value="Chart" class="buttonAdd" onClick="drawChart(<?= $idPoll ?>);">
    </p>
  </form>
</div>

<div id="ManagePoll" class="form-action hide">
  <form action="update_db.php" method="post">
    <ul>
      <li>
        <h1> <?= $QuestionPoll ?></h1>
      </br>
    </li>
    <li>
      <img src= "<?php echo $ImagePoll ?>">
    </br></br>
    <h2> New Image: </h2>
  </br>
  <input type="text" name="newImage" placeholder="New Image">
</li>
<li>
</br>
<h1>Options:</h1>
</br>
<?php foreach($pollOptions as $tempOp) : ?>
  <h2> <?= $tempOp ?> </h2> </br>
  <input type="text" name="<?= $tempOp ?>" placeholder="New Option">
<?php endforeach; ?>
</li>
</ul>
</br>
Do you want remove this Poll? 
<input type="checkbox" id="deletePoll" name="deletePoll" value="No">
<input type="submit" value="Update" class="button" />
</form>
</div>

</div>
</div>
<footer>
 <center> 2014 LTW  © All rights reserved to no one. </center>
</br> <center> Pls no copy pasterino </center>
</footer>
</body>
</html>
