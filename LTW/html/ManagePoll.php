<?php
$dbh = new PDO('sqlite:../db/database.db');

$Poll = $_GET['idUserQuery'];
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
  <script type="text/javascript" src="../js/page.js"></script>
  <title>Pollerino</title>
  <link rel="shortcut icon" href="../resources/icon.ico"/>
  <meta charset="utf-8">
  <link rel="stylesheet" href="../css/createPoll.css" hreflang="en">
</head>
<body>
    <?php  session_start();   $_SESSION['usernameOn'] = $username;  $_SESSION['ipOut'] = $ip; ?>
    <div class="Logout">
        <form action="createPoll.php" method="post">
            <ul class="Home"> 
                <li>
                   <p><?= $username ?></p>
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
<div id ="container" class="container">
    <div class="flat-form">
        <ul class="tabs">
            <li>
                <a href="#Poll" class="active">Poll Statistics</a>
            </li>
            <li>
                <a href="#PollOptions">Manage Poll</a>
            </li>
        </ul>

        <div id="Poll" class="form-action show">
            <h1>Poll Statistics</h1>
            <form>
                <ul>
                    <p>
                        Question?
                    </p>
                    <li>
                        <p> Questão aqui </p>
                    </li>

                    <p>
                        Options:
                    </p>
                    script js para por as respostas
                </ul>
            </form>

        </div>

        <div id="ManagePoll" class="form-action hide">
            <h1>ManagePoll</h1>
            <p>
                Apagar
            </p> 
            Script aqui
            <form>
                cenas
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
