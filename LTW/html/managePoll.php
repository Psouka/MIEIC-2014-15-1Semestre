<?php

$dbh = new PDO('sqlite:../db/database.db');


session_start();
if(isset($_SESSION['idQuery']))
  $idPoll = $_SESSION['idQuery'];
else
  $idPoll = $_GET['idUserQuery'];


$_SESSION['idQuery'] = $idPoll;


$idPoll = $_GET['idUserQuery'];

if(isset($_SESSION['username']))
  $username = $_SESSION['username'];
else
  $username = "Guest";

if(isset($_SESSION['idUser']))
  $userid = $_SESSION['idUser'];

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
  <script type="text/javascript">var switchTo5x=true;</script>
  <script type="text/javascript" src="../resources/buttons.js"></script>
  </head>
<body>
  <?php    $_SESSION['usernameOn'] = $username;  $_SESSION['ipOut'] = $ip; ?>
  <nav class="navbar navbar-default navbar-fixed-top" role="navigation">
    <div class="container-fluid">
      <!-- Brand and toggle get grouped for better mobile display -->
      <div class="navbar-header">
        <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
          <span class="sr-only">Toggle navigation</span>
          <span> <p>Menu</p> </span>
        </button>
        <a class="navbar-brand" href="../html/page.php"><p>Pollerino</p></a>
      </div>
      <!-- Collect the nav links, forms, and other content for toggling -->
      <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
        <ul class="nav navbar-nav navbar-right">
          <li id = "userL"><a href="../html/profile.php"><?= $username?></a></li>
          <li><a href="../html/home.php">Home</a></li>
          <li><a href="../html/createPoll.php">Create</a></li>
          <li><a href="../html/searchPoll.php">Search</a></li>
          <li><a href="../db/logout.php">Logout</a></li>
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
              <a href=<?php echo $Link?>> <?php echo $Link?> </a>
            </br>
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
<span class='st_facebook_large' displayText='Facebook'></span>
<span class='st_googleplus_large' displayText='Google +'></span>
<span class='st_twitter_large' displayText='Tweet'></span>
<span class='st_linkedin_large' displayText='LinkedIn'></span>
<span class='st_pinterest_large' displayText='Pinterest'></span>
<span class='st_email_large' displayText='Email'></span>
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