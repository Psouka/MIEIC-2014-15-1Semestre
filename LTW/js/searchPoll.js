
function searchUser(username) {
  $.getJSON("../db/searchPoll.php", {'username': username}, PollsReceived);
}

// Called when messages are received
function  PollsReceived(data) {
  $.each(data, resultPoll);
}

// Called for each line received
function resultPoll(index, value) {

var  a = document.createElement('a');
var linkText = document.createTextNode(Query);
a.appendChild(linkText);
a.title = Query;
a.href = "http://example.com";
document.getElementById('dynamicSearch').appendChild(a);
}
