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

function get_tiny_url($url)  {  
  $ch = curl_init();  
  $timeout = 5;  
  curl_setopt($ch,CURLOPT_URL,'http://tinyurl.com/api-create.php?url='.$url);  
  curl_setopt($ch,CURLOPT_RETURNTRANSFER,1);  
  curl_setopt($ch,CURLOPT_CONNECTTIMEOUT,$timeout);  
  $data = curl_exec($ch);  
  curl_close($ch);  
  return $data;  
}

$Link = 'http://'.$_SERVER['HTTP_HOST'].$_SERVER['PHP_SELF'] .'?idUserQuery='. $idPoll;
$Link = str_replace("managePoll","poll",$Link);
$Link = get_tiny_url($Link);

?>

<html lang="en">
<head>
  <script src="../resources/jquery-1.9.1.js"></script>
  <script src="../resources/d3.v3.min.js"> </script>
  <script src="../resources/js/bootstrap.min.js"></script>
  <script type="text/javascript" src="../js/page.js"></script>
  <title>Pollerino</title>
  <link rel="shortcut icon" href="../resources/icon.ico"/>
  <meta charset="utf-8">
  <link rel="stylesheet" href="../resources/css/bootstrap.min.css">
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
  <nav class="navbar navbar-default navbar-fixed-top" role="navigation">
    <div class="container-fluid">
      <!-- Brand and toggle get grouped for better mobile display -->
      <div class="navbar-header">
        <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
          <span class="sr-only">Toggle navigation</span>
          <span class="icon-bar"></span>
          <span class="icon-bar"></span>
          <span class="icon-bar"></span>
        </button>
        <a class="navbar-brand" href="../html/page.php"><p>Pollerino</p></a>
      </div>

      <!-- Collect the nav links, forms, and other content for toggling -->
      <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
        <ul class="nav navbar-nav navbar-right">
          <li id = "userL"><a href="../html/profile.php"><?= $username?></a></li>
          <li><a href="../html/page.php">Home</a></li>
          <li><a href="../html/createPoll.php">Create</a></li>
          <li><a href="../html/searchPoll.php">Search</a></li>
          <li><a href="../html/logout.php">Logout</a></li>
          
        </ul>
      </div><!-- /.navbar-collapse -->
    </div><!-- /.container-fluid -->
  </nav>
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
              <h1> Link: </h1>
              <?php echo $Link?>
            </br>
          </li>
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
</br></br>
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