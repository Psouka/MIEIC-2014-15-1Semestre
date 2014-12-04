<?php
$dbh = new PDO('sqlite:../db/database.db');

$idPoll = 4;
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
  <script src="../resources/d3.v3.min.js"> </script>
  <title>Pollerino</title>
  <link rel="shortcut icon" href="../resources/icon.ico"/>
  <meta charset="utf-8">
  <link rel="stylesheet" href="../css/profile.css" hreflang="en">
</head>
<?php flush(); ?>
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
        <a href="../html/Profile.php">My Pollerinos</a>
        <a href="" class="active">Edit Profile(todo maybe?)</a>
        <a href="../html/createPoll.php">Create Pollerinos</a>
      </li>
    </ul>

    <div id="profileEdit" class="form-action show">
      <form>
        <ul>
          <h1> Edit your Profile </h1></br>
          <h2> First Name </h2></br>
          <input type="text" name="FirstName" placeholder="New First Name">
          <h2> Last Name </h2></br>
          <input type="text" name="LastName" placeholder="New Last Name">

          <h2>Idade</h2>
          <select name="age" id="age">
            <option value="" selected="selected">(Select Your Age)</option> 
            <option value="006">6</option>
            <option value="007">7</option>
            <option value="008">8</option>
            <option value="009">9</option>
            <option value="010">10</option>
            <option value="011">11</option>
            <option value="012">12</option>
            <option value="013">13</option>
            <option value="014">14</option>
            <option value="015">15</option>
            <option value="016">16</option>
            <option value="017">17</option>
            <option value="018">18</option>
            <option value="019">19</option>
            <option value="020">20</option>
            <option value="021">21</option>
            <option value="022">22</option>
            <option value="023">23</option>
            <option value="024">24</option>
            <option value="025">25</option>
            <option value="026">26</option>
            <option value="027">27</option>
            <option value="028">28</option>
            <option value="029">29</option>
            <option value="030">30</option>
            <option value="031">31</option>
            <option value="032">32</option>
            <option value="033">33</option>
            <option value="034">34</option>
            <option value="035">35</option>
            <option value="036">36</option>
            <option value="037">37</option>
            <option value="038">38</option>
            <option value="039">39</option>
            <option value="040">40</option>
            <option value="041">41</option>
            <option value="042">42</option>
            <option value="043">43</option>
            <option value="044">44</option>
            <option value="045">45</option>
            <option value="046">46</option>
            <option value="047">47</option>
            <option value="048">48</option>
            <option value="049">49</option>
            <option value="050">50</option>
            <option value="051">51</option>
            <option value="052">52</option>
            <option value="053">53</option>
            <option value="054">54</option>
            <option value="055">55</option>
            <option value="056">56</option>
            <option value="057">57</option>
            <option value="058">58</option>
            <option value="059">59</option>
            <option value="050">50</option>
            <option value="061">61</option>
            <option value="062">62</option>
            <option value="063">63</option>
            <option value="064">64</option>
            <option value="065">65</option>
            <option value="066">66</option>
            <option value="067">67</option>
            <option value="068">68</option>
            <option value="069">69</option>
            <option value="070">70</option>
            <option value="071">71</option>
            <option value="072">72</option>
            <option value="073">73</option>
            <option value="074">74</option>
            <option value="075">75</option>
            <option value="076">76</option>
            <option value="077">77</option>
            <option value="078">78</option>
            <option value="079">79</option>
            <option value="080">80</option>
            <option value="081">81</option>
            <option value="082">82</option>
            <option value="083">83</option>
            <option value="084">84</option>
            <option value="085">85</option>
            <option value="086">86</option>
            <option value="087">87</option>
            <option value="088">88</option>
            <option value="089">89</option>
            <option value="090">90</option>
            <option value="091">91</option>
            <option value="092">92</option>
            <option value="093">93</option>
            <option value="094">94</option>
            <option value="095">95</option>
            <option value="096">96</option>
            <option value="097">97</option>
            <option value="098">98</option>
            <option value="099">99</option>
            <option value="100">100</option>
          </select>
          <h2> Change Password </h2></br>
          <input type="text" name="newPw" placeholder="New Password">
          <input type="text" name="confirmPw" placeholder="Confirm Password">
          <p>

          </p>
          <input type="submit" value="Update" class="button" />
        </ul>
      </form>
    </div>
  </div>
  <footer>
   <center> 2014 LTW  © All rights reserved to no one. </center>
 </br> <center> Pls no copy pasterino </center>
</footer>
</body>
</html>
