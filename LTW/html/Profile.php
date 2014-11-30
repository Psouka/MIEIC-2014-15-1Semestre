<?php
$dbh = new PDO('sqlite:../db/database.db');

$idPoll = 4;
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
  <title>Pollerino</title>
  <link rel="shortcut icon" href="../resources/icon.ico"/>
  <meta charset="utf-8">
  <link rel="stylesheet" href="../css/profile.css" hreflang="en">
</head>
<body>
  <?php  session_start();   $_SESSION['usernameOn'] = $username;  $_SESSION['ipOut'] = $ip; ?>
  <div id ="container" class="container">
    <div class="LogoutM">
      <form class = "formLog" action="../db/logout.php" method="post">
        <ul class="Home"> 
          <li>
           <p class = "userP"><?= $username ?></p>
         </li>
         <li>
           <input type="submit" value="Home" class="buttonOut" />
         </li>
       </ul>   
       <ul class="Logout"> 
        <li>
         <input type="submit" value="Log Out" class="buttonOut" />
       </li>
     </ul>      
   </form>
 </div>
 <div class="flat-form">
  <ul class="tabs">
    <li>
      <a href="" class="active">My Pollerinos</a>
      <a href="../html/editProfile.php">Edit Profile(todo maybe?)</a>
      <a href="../html/createPoll.php">Create or search Pollerinos</a>
    </li>
  </ul>

  <div id="Poll" class="form-action show">
    <form>
    </script></center>
    <ul>
      <?php if(is_null($questions)) : ?>
        <h1> You dont have any pollerinos! </h1></br>
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
