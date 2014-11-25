<html lang="en">
<head>
        <meta charset="utf-8">
   <title>Pollerino</title>
  <script src="../resources/jquery-1.9.1.js"></script>
  <script src="../js/page.js"></script>
   <link rel="shortcut icon" href="../resources/icon.ico">
   <link rel="stylesheet" href="../css/page.css" hreflang="en">
</head>
<body>
    <div id ="container" class="container">
        <div class="flat-form">
            <ul class="tabs">
                <li>
                    <a href="#login" class="active">Login</a>
                </li>
                <li>
                    <a href="#register">Register</a>
                </li>
                <li>
                    <a href="#reset">Reset Password</a>
                </li>
            </ul>

            <div id="login" class="form-action show">
                <h1>Login on Pollerino</h1>
                <form action="../db/login.php" method="post">
                    <ul>
                        <li>
                            <input type="text" name="usernameL" placeholder="Username" required>
                        </li>
                        <li>
                            <input type="password" name="passwordL" placeholder="Password" required>
                        </li>
                        <li>
                            <input type="submit" value="Login" class="button" />
                        </li>
                    </ul>
                </form>

            </div>

            <div id="register" class="form-action hide">
                <h1>Register</h1>
                 <form action="../db/register.php" method="post">
                    <ul>
                        <li>
                            <input type="text" id="username" name="usernameR" placeholder="Username" required><br>
                        </li>
                        <li>
                            <input type="email" id="email" name="emailR" placeholder="E-mail" required><br>
                        </li>
                        <li>
                           <input type="password" id="password" name="passwordR" maxlength="8" placeholder="Password" required><br>
                        </li>
                        <li>
                            <input type="submit" value="Sign Up" class="button" />
                        </li>
                    </ul>
                </form>
            </div>

            <div id="reset" class="form-action hide">
                <h1>Reset Password</h1>
                <p>
                    To reset your password enter your email
                    and we'll send you a link to reset your password.
                </p>
                <form>
                    <ul>
                        <li>
                            <input type="email" id="email" name="emailRecover" placeholder="E-mail" required><br>
                        </li>
                        <li>
                            <input type="submit" value="Send" class="button" />
                        </li>
                    </ul>
                </form>
            </div>

        </div>
    </div>
    <footer>
           <center> 2014 LTW  © All righterinos reserved to no one. </center>
        </footer>
</body>
</html>
