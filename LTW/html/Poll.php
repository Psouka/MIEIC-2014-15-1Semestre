<?php
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

$stmt2 = $dbh->prepare('SELECT Question, Image FROM UserQuery WHERE idUserQuery = ?');
$stmt2->execute(array($idPoll));
$row = $stmt2->fetch();

$QuestionPoll = $row['Question'];
$ImagePoll = $row['Image'];

/*
$question = 0;
$img = 0;

$stmt3 = $dbh->prepare('SELECT idUserQuery, Question, Image FROM UserQuery WHERE idUserQuery = ?');
$stmt3->execute(array($idPoll));
while ($row = $stmt3->fetch()) {
    if(in_array($idPoll, $row)) {
      $question = $row['Question'];
      $img = $row['Image'];
    }
  }
$answers = array();
$stmt4 = $dbh->prepare('SELECT idUserQuery, Answerino FROM Answer WHERE idUserQuery = ?');
$stmt4->execute(array($idPoll));
while ($row = $stmt4->fetch()) {
    if(in_array($idPoll, $row)) {
      array_push($answers, $row['Answerino']);
    }
  }
  */
  ?>

  <html lang="en">
  <head>
    <script src="../resources/jquery-1.9.1.js"></script>
    <script src="../resources/d3.v3.min.js"> </script>
    <script type="text/javascript" src="../js/page.js"></script>
    <title>Pollerino</title>
    <link rel="shortcut icon" href="../resources/icon.ico"/>
    <meta charset="utf-8">
    <link rel="stylesheet" href="../css/Poll.css" hreflang="en">
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
      <div id="dynamicOptions">
        <script src="../js/auxPoll.js" language="Javascript" type="text/javascript">
        </script>
      </div>
      <input type="button" value="Responde" class="buttonAdd" onClick="showOptions(<?= $idPoll ?>,'<?= $username ?>');">
    </p>
    <p>
      <div class="chart"></div>
      <script src="../js/chart.js">
      </script>
      <input type="button" value="Chart" class="buttonAdd" onClick="drawChart(<?= $idPoll ?>);">
    </p>
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
