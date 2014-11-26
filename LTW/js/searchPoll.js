
function searchUser(username) {
	alert(username);
  $.getJSON("../db/searchPoll.php", {'username': username}, PollsReceived);
}

// Called when messages are received
function  PollsReceived(data) {
	alert(data);
  $.each(data, resultPoll);
}

// Called for each line received
function resultPoll(index, value) {
alert('Poll');

var  a = document.createElement('a');
var linkText = document.createTextNode(value);
a.appendChild(linkText);
a.title = value;
a.href = "http://example.com";
document.getElementById('dynamicSearch').appendChild(a);
}
