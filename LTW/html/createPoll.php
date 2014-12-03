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
  <title>Pollerino</title>
  <link rel="shortcut icon" href="../resources/icon.ico"/>
  <meta charset="utf-8">
  <link rel="stylesheet" href="../css/createPoll.css" hreflang="en">
</head>
<body>
  <?php  session_start();   $_SESSION['usernameOn'] = $username;  $_SESSION['ipOut'] = $ip; ?>
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
          <p>Create Poll</p>
        </li>
      </ul>

      <div id="CreatPoll" class="form-action show">
        <h1>Creating Poll</h1>
        <form action="../db/newpoll.php" method="post">
          <ul>
            <p>
              Question:
            </p>
            <li>
              <input type="text" name="Question" placeholder="Question" required>
            </li>

            <p>
             <p>
              Image:
            </p>
            <li>
              <input type="text" name="queryImage" placeholder="Image" required>
            </li>

            <p>


              Options:
            </p>
            <p>
              <div id="dynamicInput">
                <script src="../js/createPoll.js" language="Javascript" type="text/javascript"></script>
                <div class="addtinput">
                <input type="text" name="inputs1" class="newOpt" placeholder="New Optionerino..."> 
                <input type="button" name="deleteInput1" class="buttonDel" value="−" onclick="deleteInput(this);">
                </div>
                <div class="addtinput">
                <input type="text" name="inputs2" class="newOpt" placeholder="New Optionerino..."> 
                <input type="button" name="deleteInput2" class="buttonDel" value="−" onclick="deleteInput(this);">
                </div>
              </div>
              <input type="button" value="Add another optionerino" class="buttonAdd" onClick="addInput('dynamicInput');">
            </p>
            <p>
              Private ? </br></br>
              <input type="checkbox" id="privacy" name="privacy" value="Yes" checked>
            </p>
            <p>
              <li>
                <input type="submit" value="Create" class="button" />
              </li>
            </p>
          </ul>
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