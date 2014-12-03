<?php
$dbh = new PDO('sqlite:../db/database.db');
$dbh->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

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

$seeOptions = 0;

$stm = $dbh->prepare('SELECT idUserQuery, idUser FROM UserAnswer WHERE idUserQuery = ? AND idUser = ?');
$stm->execute(array($idPoll, $userid));
while ($row = $stm->fetch()) {
  if(in_array($userid, $row)) {
    if(in_array($idPoll, $row)) {
      $seeOptions = 1;
    }
  }
}

$stmt2 = $dbh->prepare('SELECT Question, Image FROM UserQuery WHERE idUserQuery = ?');
$stmt2->execute(array($idPoll));
$row = $stmt2->fetch();

$QuestionPoll = $row['Question'];
$ImagePoll = $row['Image'];

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
      <form class = "formLog" action="../db/logout.php" method="post">
        <ul class="Home"> 
          <li>
            <div class = "leftD">
              <p class = "pollerinoP"> Pollerino </p>
            </div>
            <div class = "rightD">
              <input type="submit" value="Home" class="buttonOut" />
              <input type="submit" value="Search" class="buttonOut" />
              <input type="submit" value="Profile" class="buttonOut" />
              <input type="submit" value="Log Out" class="buttonOut" />
            </div>
            <div class = "rightP">
              <p class = "userP"><?= $username ?></p>
            </div>
          </li>
        </ul>
      </form>
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
            <img src= "<?= $ImagePoll ?>">
          </br></br>
          <p class = "pOpt">Options:</p>
        </ul>
        <p>
          <div id="dynamicOptions">
            <?php if($seeOptions == 0) : ?>
              <script src="../js/auxPoll.js" language="Javascript" type="text/javascript"></script> <script> init(<?= $seeOptions?>, <?= $idPoll ?>);
            </script>
          <?php endif; ?>
        </div>
      </p>
      <p>
        <div class="chart">
          <?php if($seeOptions != 0) :?>
            <script src="../js/chart.js" language="Javascript" type="text/javascript"> </script> <script> drawChart(<?= $idPoll ?>);</script>
          <?php endif; ?>
        </div>
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
