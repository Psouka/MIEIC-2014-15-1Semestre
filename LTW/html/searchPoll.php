<?php
$dbh = new PDO('sqlite:../db/database.db');
session_start();

if(isset($_SESSION['username']))
  $username = $_SESSION['username'];
else
  $username = "Guest";
if(isset($_SESSION['idUser']))
  $userid = $_SESSION['idUser'];
?>

<html lang="en">
<head>
  <script src="../resources/jquery-1.9.1.js"></script>
  <script src="../resources/js/bootstrap.min.js"></script>
  <title>Pollerino</title>
  <link rel="shortcut icon" href="../resources/icon.ico"/>
  <meta charset="utf-8">
  <link rel="stylesheet" href="../resources/css/bootstrap.min.css">
  <link rel="stylesheet" href="../css/createPoll.css" hreflang="en">
  <script  type="text/javascript" src="../js/searchPoll.js"></script>
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
          <p>Search Poll</p>
        </li>
      </ul>
      <div id="SearchPoll" class="form-action show">
        <h1>Searching for Poll</h1>
        <p>
          Give key words / Id's / Username
        </p>
        <form>
          <ul>
            <li>
              <input type="text" id= "word" name="kWord" placeholder="Key Word" >
            </li>
            <li>
              <input type="text" id ="id" name="searchID" placeholder="ID" >
            </li>
            <li>
              <input type="text" id = "username" name="username" placeholder="Username" >
            </li>
            <div id = "results">
            </div>
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