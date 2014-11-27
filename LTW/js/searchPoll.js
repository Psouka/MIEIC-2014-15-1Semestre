
function searchUser(username) {
  $.getJSON("../db/searchPoll.php", {'username': username}, PollsReceived);
}

function searchId(id) {
  $.getJSON("../db/searchPoll.php", {'id': id}, PollsReceived);
}

function searchWord(word) {
  $.getJSON("../db/searchPoll.php", {'word': word}, PollsReceived);
}


// Called when messages are received
function  PollsReceived(data) {
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
