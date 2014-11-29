

function searchPoll(username,id,word)
{
	clearSearch();
	searchUser(username);
	searchId(id);
	searchWord(word);
}

function searchUser(username) {
	if(username == "")
		return;
	$.getJSON("../db/searchPoll.php", {'username': username}, PollsReceived);
}

function searchId(id) {
	if(id == "")
		return;
	$.getJSON("../db/searchPoll.php", {'id': id}, PollsReceived);
}

function searchWord(word) {
	if(word == "")
		return;
	$.getJSON("../db/searchPoll.php", {'word': word}, PollsReceived);
}


// Called when messages are received
function  PollsReceived(data) {
	$.each(data, resultPoll);
}

// Called for each line received
function resultPoll(index, value) {
	
	var  a = document.createElement('a');
	var linkText = document.createTextNode(value);
	a.appendChild(linkText);
	a.title = value;
	a.href = "../db/poll.php?Question=" + value;
	document.getElementById('dynamicSearch').appendChild(a);

	var br = document.createElement('br');
	document.getElementById('dynamicSearch').appendChild(br);

}


function clearSearch(){
	var list = document.getElementById('dynamicSearch');

	while (list.firstChild) {
		list.removeChild(list.firstChild);
	}

}