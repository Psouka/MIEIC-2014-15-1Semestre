<?php
$dbh = new PDO('sqlite:../db/database.db');
$dbh->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
session_start();
$idPoll = $_GET['idUserQuery'];

if(isset($_SESSION['username']))
  $username = $_SESSION['username'];
else
  $username = "Guest";

if(isset($_SESSION['idUser']))
  $userid = $_SESSION['idUser'];

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
  <script src="../resources/js/bootstrap.min.js"></script>
  <script src="../js/page.js"></script>
  <script src="../js/auxPoll.js" language="Javascript" type="text/javascript"></script>
  <script src="../js/comment.js" language="Javascript" type="text/javascript"></script>
  <title>Pollerino</title>
  <link rel="shortcut icon" href="../resources/icon.ico"/>
  <meta charset="utf-8">
  <link rel="stylesheet" href="../resources/css/bootstrap.min.css">
  <link rel="stylesheet" href="../css/poll.css" hreflang="en">
  <link rel="stylesheet" href="../css/chart.css" hreflang="en">
</head>
<!--<?php flush(); ?> -->
<body>
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
          <li><a href="../html/page.php">Home</a></li>
          <li><a href="../html/createPoll.php">Create</a></li>
          <li><a href="../html/searchPoll.php">Search</a></li>
          <li><a href="../db/logout.php">Logout</a></li>
          
        </ul>
      </div><!-- /.navbar-collapse -->
    </div><!-- /.container-fluid -->
  </nav>
  <div id ="container" class="container poll">
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
        <input type="button" value="Confirm answer" class="button" onclick="sendVote(<?= $idPoll?>,'<?php echo $username ?>');"/>
      </p>
    <?php endif; ?>
    <div class="chart">
      <?php if($seeOptions != 0) :?>
      <script src="../js/chart.js" language="Javascript" type="text/javascript"> </script> <script> drawChart(<?= $idPoll ?>);</script>
    <?php endif; ?>
  </div>
</br>
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
  <p>Comment:</p> </br>
  <textarea name="comment" id="comment" maxlength="170" rows="8" cols="75" style="color:BLACK"></textarea><br/>
  <input type="button" value="Comment!" class="button" onclick="sendComment(<?= $idPoll?>,'<?php echo $username ?>');"/>
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