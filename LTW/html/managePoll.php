<?php

$dbh = new PDO('sqlite:../db/database.db');


session_start();
if(isset($_SESSION['idQuery']))
  $idPoll = $_SESSION['idQuery'];
else
  $idPoll = $_GET['idUserQuery'];


$_SESSION['idQuery'] = $idPoll;

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
  <div id="fb-root"></div>
  <script>(function(d, s, id) {
    var js, fjs = d.getElementsByTagName(s)[0];
    if (d.getElementById(id)) return;
    js = d.createElement(s); js.id = id;
    js.src = "//connect.facebook.net/en_US/sdk.js#xfbml=1&version=v2.0";
    fjs.parentNode.insertBefore(js, fjs);
  }(document, 'script', 'facebook-jssdk'));</script>
  <script>!function(d,s,id){var js,fjs=d.getElementsByTagName(s)[0],p=/^http:/.test(d.location)?'http':'https';if(!d.getElementById(id)){js=d.createElement(s);js.id=id;js.src=p+'://platform.twitter.com/widgets.js';fjs.parentNode.insertBefore(js,fjs);}}(document, 'script', 'twitter-wjs');</script>
  <?php    $_SESSION['usernameOn'] = $username;  $_SESSION['ipOut'] = $ip; ?>
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
        <p>Options:</p>
      </ul>
      </br>
      <p>
       <div class="chart">
        <script src="../js/chart.js" language="Javascript" type="text/javascript"> </script>
        <script> drawChart(<?= $idPoll ?>);</script>
      </div>
    </p>
    </br>
    <div class="fb-share-button" data-layout="button"></div>
    <a href="https://twitter.com/share" class="twitter-share-button" data-count="none">Tweet</a>
  </form>
</br>
</div>

<div id="ManagePoll" class="form-action hide">
  <form action="../db/update_db.php" method="post">
    <ul>
      <li>
        <h1> <?= $QuestionPoll ?></h1>
      </br>
    </li>
    <li>
      <img src= "<?php echo $ImagePoll ?>">
    </br></br>
    <p> New Image: </p>
  </br>
  <input type="text" name="newImage" placeholder="New Image">
</li>
<li>
</br>
<h1>Options:</h1>
</br>
<?php foreach($pollOptions as $tempOp) : ?>
  <p> <?= $tempOp ?> </p> </br>
  <input type="text" name="<?= $tempOp ?>" placeholder="New Option">
<?php endforeach; ?>
</li>
</ul>
</br>
<p>Do you want remove this Poll?
</br></br>
<input type="checkbox" id="deletePoll" name="deletePoll" value="Yes"></p>
<li id = "buttonli">
  <input type="submit" value="Update" class="button" />
</li>
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