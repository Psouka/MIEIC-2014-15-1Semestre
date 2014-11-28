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
</head>
<body>
  <?php  session_start();   $_SESSION['usernameOn'] = $username;  $_SESSION['ipOut'] = $ip; ?>
  <div class="Login">
            <ul class="Login"> 
                <li>
                     <p><center><?= $username ?></center></p>
                </li>
                <li>
                  <form action="../html/createPoll.php" method="post">
                     <input type="submit" value="Home" class="buttonOut" />
                      </form>
                </li>
                <li>
                  <form action="../db/logout.php" method="post">
                     <input type="submit" value="Log Out" class="buttonOut" />
                     </form>
                </li>
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
      <h1>Poll</h1>
      <form>
        <ul>
          <p>
            Question?
          </p>
          <li>
            <p> Questão aqui </p>
          </li>

          <p>
            Options:
          </p>
          script js para por as respostas
        </ul>
      </form>
    </div>
    <div class="chart"></div>
    <script src="../js/chart.js">
    drawChart(2);
    </script>
  </div>
</div>
<footer>
 <center> 2014 LTW  © All rights reserved to no one. </center>
</br> <center> Pls no copy pasterino </center>
</footer>
</body>
</html>
