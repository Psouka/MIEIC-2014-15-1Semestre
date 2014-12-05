<?php
$dbh = new PDO('sqlite:../db/database.db');
session_start();

if(isset($_SESSION['username']))
  $username = $_SESSION['username'];
else
  $username = "Guest";

if(isset($_SESSION['idUser']))
  $userid = $_SESSION['idUser'];

if(isset($_GET['page'])){ 
  $numPag = $_GET['page'];
}
else {
  $numPag = 1;
}
/*
$questions = array();
$stmt = $dbh->prepare('SELECT idUser, Question FROM UserQuery WHERE idUser = ?');
$stmt->execute(array($userid));
while ($row = $stmt->fetch()) {
  if(in_array($userid, $row)) {
    array_push($questions,$row['Question']);
  }
}
*/
?>

<html lang="en">
<head>
  <script src="../resources/jquery-1.9.1.js"></script>
  <script src="../resources/d3.v3.min.js"> </script>
  <script src="../resources/js/bootstrap.min.js"></script>
  <script src="../js/getPolls.js" language="Javascript" type="text/javascript"></script>
  <title>Pollerino</title>
  <link rel="shortcut icon" href="../resources/icon.ico"/>
  <meta charset="utf-8">
  <link rel="stylesheet" href="../resources/css/bootstrap.min.css">
  <link rel="stylesheet" href="../css/profile.css" hreflang="en">
</head>
<?php flush(); ?>
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
          <li><a href="../html/home.php?page=1">Home</a></li>
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
        <a href="" class="active">Pollerinos</a>
      </li>
    </ul>

    <div id="Poll" class="form-action show">
      <form>
        <ul>
          <div id = "dynamicSearch">
          <script> searchPolls( <?php echo $numPag-1 ?>);  </script>
          </div>
        </ul>
        <nav>
          <ul class="pager">
            <?php 
            $pageB = $numPag-1;
            $pageN = $numPag+1;
            $urlB = 'poll.php?numPag=' . $pageB;
            $urlN = 'poll.php?numPag=' . $pageN;
            ?>
            <?php if($pageB <= 0) :?>
              <li class="previous disabled"><a href=<?= '?page='.$pageB ?>><span aria-hidden="true">&larr;</span> Older</a></li>
            <?php else:?>
              <li class="previous"><a href=<?= '?page='.$pageB ?>><span aria-hidden="true">&larr;</span> Older</a></li>
            <?php endif;?>
            <?php if($pageB <= 0) :?>
              <script language="javascript" > var id = searchPolls(<?php echo $numPag ?>); </script>
              <?php $value = var id;?>
              <?php if($value <= 0) :?>
                <li class="next disabled"><a href=<?= '?page='.$pageN ?>>Newer <span aria-hidden="true">&rarr;</span></a></li>
              <?php else:?>
                <li class="next"><a href=<?= '?page='.$pageN ?>>Newer <span aria-hidden="true">&rarr;</span></a></li>
              <?php endif;?>
            </ul>
          </nav>
        </form>
      </div>
    </div>
  <footer>
   <center> 2014 LTW  © All rights reserved to no one. </center>
 </br> <center> Pls no copy pasterino </center>
</footer>
</body>
</html>