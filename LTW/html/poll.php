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
$username = "Guest";

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
  <script src="../js/page.js"></script>
  <script src="../js/auxPoll.js" language="Javascript" type="text/javascript"></script>
  <title>Pollerino</title>
  <link rel="shortcut icon" href="../resources/icon.ico"/>
  <meta charset="utf-8">
  <link rel="stylesheet" href="../css/poll.css" hreflang="en">
  <link rel="stylesheet" href="../css/chart.css" hreflang="en">
</head>
<!--<?php flush(); ?> -->
<body>
  <!-- <?php  session_start();   $_SESSION['usernameOn'] = $username;  $_SESSION['ipOut'] = $ip; ?> -->
  <div class="LogoutM">
    <form class = "formLog">
      <ul class="Home"> 
        <li>
          <div class = "leftD">
            <p class = "pollerinoP"> Pollerino </p>
          </div>
          <div class = "rightD">
            <input type="button" value="Home" class="buttonOut" onclick="location.href='../html/page.php'"/>
            <input type="button" value="Search" class="buttonOut" onclick="location.href='../html/searchPoll.php'"/>
            <input type="button" value="Profile" class="buttonOut" onclick="location.href='../html/profile.php'"/>
            <input type="button" value="Log Out" class="buttonOut" onclick="location.href='../db/logout.php'"/>
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
          <a href="#Comments">Poll Comments</a>
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
      <?php if($seeOptions == 0) : ?>
      <p>
        <div id="dynamicOptions">
          <script> init(<?= $seeOptions?>, <?= $idPoll ?>, '<?= $username; ?>');
          </script>
        </div>
        <input type="button" value="Confirm answer" class="button" onclick="sendVote(<?= $idPoll?>,'<?php echo $username ?>');">
      </p>
    <?php endif; ?>
    <p>
      <div class="chart">
        <?php if($seeOptions != 0) :?>
        <script src="../js/chart.js" language="Javascript" type="text/javascript"> </script> <script> drawChart(<?= $idPoll ?>);</script>
      <?php endif; ?>
    </div>
  </p>
  <?php $ref = 'Location: ../html/poll.php?idUserQuery=' + $idPoll; ?>
  <div id="fb-root"></div>
  <script>(function(d, s, id) {
    var js, fjs = d.getElementsByTagName(s)[0];
    if (d.getElementById(id)) return;
    js = d.createElement(s); js.id = id;
    js.src = "//connect.facebook.net/en_US/sdk.js#xfbml=1&version=v2.0";
    fjs.parentNode.insertBefore(js, fjs);
  }(document, 'script', 'facebook-jssdk'));</script>
  <div class="fb-share-button" data-href="https://developers.facebook.com/docs/plugins/" data-layout="button"></div>
  <script>!function(d,s,id){var js,fjs=d.getElementsByTagName(s)[0],p=/^http:/.test(d.location)?'http':'https';if(!d.getElementById(id)){js=d.createElement(s);js.id=id;js.src=p+'://platform.twitter.com/widgets.js';fjs.parentNode.insertBefore(js,fjs);}}(document, 'script', 'twitter-wjs');</script>
  <a href="https://twitter.com/share" class="twitter-share-button" data-count="none">Tweet</a>
</form>
</br>
</div>
<div id="Comments" class="form-action hide">
  <form>
    <h1>Comments</h1></br>
  </br>
  <p>Comment:</p> 
  <textarea name="comment" id="comment" maxlength="170" rows="4" cols="50"></textarea><br />
  <input type="button" value="Comment!" class="buttonOut"/>
</form>
</br>
</div>
</div>
</div>
<footer>
 <center> 2014 LTW  © All rights reserved to no one. </center>
</br> <center> Pls no copy pasterino </center>
</footer>
</body>
</html>