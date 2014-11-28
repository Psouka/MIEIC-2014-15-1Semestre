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
  <script type="text/javascript" src="../js/page.js"></script>
   <title>Pollerino</title>
   <link rel="shortcut icon" href="../resources/icon.ico"/>
        <meta charset="utf-8">
        <link rel="stylesheet" href="../css/createPoll.css" hreflang="en">
</head>
<body>
    <?php  session_start();   $_SESSION['usernameOn'] = $username;  $_SESSION['ipOut'] = $ip; ?>
    <div class="Login">
        <form action="../db/logout.php" method="post">

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
                        <input type="text" name="inputs1" class="newOpt" placeholder="New Option..." required>
                        <input type="button" name="deleteInput1" value="−" class="buttonDel" onClick="deleteInput(this);" required>
                        <input type="text" name="inputs2" class="newOpt" placeholder="New Option..." required>
                        <input type="button" name="deleteInput2" value="−" class="buttonDel" onClick="deleteInput(this);" required>
                    </div>
                    <input type="button" value="Add another optionerino" class="buttonAdd" onClick="addInput('dynamicInput');">
                </p>
                <p>
                    <li>
                        <input type="submit" value="Create" class="button" />
                    </li>
                </p>
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
                            <input type="text" id= "wordInput" name="kWord" placeholder="Key Word" >
                        </li>
                         <li>
                            <input type="text" id ="idInput" name="searchID" placeholder="ID" >
                        </li>
                        <li>
                            <input type="text" id = "userInput" name="username" placeholder="Username" >
                        </li>
                        <p>
                    <div id="dynamicSearch">
                         <script src="../js/searchPoll.js" language="Javascript" type="text/javascript"></script>
                    </div>
                    <input type="button" value="Search" class="button"
                    onClick="searchUser(this.form.userInput.value);searchId(this.form.idInput.value);searchWord(this.form.wordInput.value);">
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