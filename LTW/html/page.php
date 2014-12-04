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
	<?php
	session_start();
	$errNum = 0;
	$errMsg = 0;

	if(isset($_SESSION['errNum'])) {
		$errNum = $_SESSION['errNum'];
	}
	if(strcmp($errNum,'UserNotChars') === 0) {
		$errMsg = 'Username cannot contain chars';
	}
	if(strcmp($errNum,'UserTaken') === 0) {
		$errMsg = 'Username already taken';
	}
	if(strcmp($errNum,'EmailTaken') === 0) {
		$errMsg = 'Email already in use';
	}
	if(strcmp($errNum,'WrongInputs') === 0) {
		$errMsg = 'Wrong Username or Password';
	}
	if(strcmp($errNum,'NoEmailReset') === 0) {
		$errMsg = 'This email is not registered';
	}
	unset($_SESSION['errNum']);
	?>
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

			<?php if((strcmp($errNum,'UserNotChars') === 0) or (strcmp($errNum,'UserTaken') === 0) or (strcmp($errNum,'EmailTaken') === 0) or strcmp($errNum, 'NoEmailReset') === 0) : ?>
			<div id="login" class="form-action hide">
			<?php else : ?>
			<div id="login" class="form-action show">
			<?php endif;?>
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
						<?php if(strcmp($errNum,'WrongInputs') === 0) : ?> 
						<p class="error"> <?= $errMsg ?> </p>
					<?php endif; ?>
					<input type="submit" value="Login" class="button" />
				</li>
			</ul>
		</form>

	</div>
	<?php if((strcmp($errNum,'UserNotChars') === 0) or (strcmp($errNum,'UserTaken') === 0) or (strcmp($errNum,'EmailTaken') === 0)) : ?>
	<div id="register" class="form-action show">
	<?php else : ?>
	<div id="register" class="form-action hide">
	<?php endif; ?>
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
				<?php if((strcmp($errNum,'UserNotChars') === 0) or (strcmp($errNum,'UserTaken') === 0) or (strcmp($errNum,'EmailTaken') === 0)) : ?>
				<p class="error"> <?= $errMsg ?> </p>
			<?php endif; ?>
			<input type="submit" value="Sign Up" class="button" />
		</li>
	</ul>
</form>
</div>
<?php if(strcmp($errNum,'NoEmailReset') === 0) : ?>
	<div id="reset" class="form-action show">
	<?php else : ?>
	<div id="reset" class="form-action hide">
	<?php endif; ?>
	<h1>Reset Password</h1>
	<p class = "resetPw">
		To reset your password enter your email
		and we'll send you a link to reset your password.
	</p>
	<form action="../db/resetPw.php" method="post">
		<ul>
			<li>
				<input type="email" id="email" name="email" placeholder="E-mail" required><br>
			</li>
			<li>
				<?php if(strcmp($errNum,'NoEmailReset') === 0) : ?>
				<p class="error"> <?= $errMsg ?> </p>
			<?php endif; ?>
			<input type="submit" value="Send" class="button" />
		</li>
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
