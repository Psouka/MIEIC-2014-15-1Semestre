<?php
$dbh = new PDO('sqlite:../db/database.db');

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

$questions = array();
$stmt = $dbh->prepare('SELECT idUser, Question FROM UserQuery WHERE idUser = ?');
$stmt->execute(array($userid));
while ($row = $stmt->fetch()) {
  if(in_array($userid, $row)) {
    array_push($questions,$row['Question']);
  }
}

?>

<html lang="en">
<head>
  <script src="../resources/jquery-1.9.1.js"></script>
  <script src="../resources/d3.v3.min.js"> </script>
  <script src="../resources/js/bootstrap.min.js"></script>
  <title>Pollerino</title>
  <link rel="shortcut icon" href="../resources/icon.ico"/>
  <meta charset="utf-8">
  <link rel="stylesheet" href="../resources/css/bootstrap.min.css">
  <link rel="stylesheet" href="../css/profile.css" hreflang="en">
</head>
<?php flush(); ?>
<body>
  <?php  session_start();   $_SESSION['usernameOn'] = $username;  $_SESSION['ipOut'] = $ip; ?>
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
        <a href="" class="active">My Pollerinos</a>
        <a href="../html/editProfile.php">Edit Profile(todo maybe?)</a>
        <a href="../html/createPoll.php">Create Pollerinos</a>
      </li>
    </ul>

    <div id="Poll" class="form-action show">
      <form>
      </script></center>
      <ul>
        <?php $questions = array_filter($questions);
        if(empty($questions)) : ?>
        <h1> You dont have any pollerinos! </h1></br>
        <h2> Click on create menu and create your first one! </h2> </br>
      <?php else : ?>
        <h1> Your Pollerinos: </h1></br>
        <li>
          <?php foreach($questions as $question) : ?>
            <h2> <?= $question ?> </h2> </br>
          <?php endforeach; ?>
        </li></br>
      <?php endif; ?>
    </ul>
  </form>
</div>
</div>
<footer>
 <center> 2014 LTW  © All rights reserved to no one. </center>
</br> <center> Pls no copy pasterino </center>
</footer>
</body>
</html>