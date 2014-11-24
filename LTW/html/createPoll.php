<?php
    $dbh = new PDO('sqlite:../db/database.db');
    $dbh->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );
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
   <title>PollPage</title>
   <link rel="shortcut icon" href="../resources/icon.ico"/>
        <meta charset="utf-8">
        <link rel="stylesheet" href="../css/createPoll.css" hreflang="en">
</head>
<body>
    <div class="Login">
        <form action="logout.php" method="post">
            <ul class="Login"> 
                <li>
                     <p><center><?= $username ?></center></p>
                </li>
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
                    <a href="#CreatPoll" class="active">Create Poll</a>
                </li>
                <li>
                    <a href="#SearchPoll">Search Poll</a>
                </li>
            </ul>

            <div id="CreatPoll" class="form-action show">
                <h1>Creating Poll</h1>
                 <form action="../db/newpoll.php" method="post">
               <?php  session_start();   $_SESSION['usernameOn'] = $username; ?>
                    <ul>
                        <p>
                    Question?
                </p>
                        <li>
                            <input type="text" name="Question" placeholder="Question" required>
                        </li>

                         <p>
                    Options:
                </p>
                        <li>
                            <input type="text" name="option1" placeholder="Option 1" required>
                        </li>
                        <li>
                            <input type="text" name="option2" placeholder="Option 2" required>
                        </li>
                        <li>
                            <input type="text" name="option3" placeholder="Option 3" >
                        </li>
                        <li>
                            <input type="text" name="option4" placeholder="Option 4" >
                        </li>
                        <li>
                            <input type="submit" value="Create" class="button" />
                        </li>
                    </ul>
                </form>

            </div>

            <div id="SearchPoll" class="form-action hide">
                <h1>Searching for Poll</h1>
                <p>
                    Give key words / Id's / Username
                </p>
                <form>
                    <ul>
                        <li>
                            <input type="text" name="kWord" placeholder="Key Word" >
                        </li>
                         <li>
                            <input type="text" name="searchID" placeholder="ID" >
                        </li>
                        <li>
                            <input type="text" name="SearchUser" placeholder="Username" >
                        </li>
                        <li>
                            <input type="submit" value="Search" class="button" />
                        </li>
                    </ul>
                </form>
            </div>

        </div>
    </div>
    <footer>
           <center> 2014 LTW  © All rights reserved to no one. </center>
        </footer>
</body>
</html>
