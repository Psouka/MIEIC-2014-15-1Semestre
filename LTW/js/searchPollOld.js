function searchPoll(username,id,word)
{
	clearSearch();
	var elem = document.getElementById('dynamicSearch');
	var h1 = document.createElement('H1');
	var tE = document.createTextNode('Results: ');
	h1.appendChild(tE);
	elem.appendChild(h1);
	elem.appendChild(document.createElement('br'));
	elem.appendChild(document.createElement('br'));
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
	
	var elem = document.getElementById('dynamicSearch');
	var a = document.createElement('a');
	var linkText = document.createTextNode(value);
	a.appendChild(linkText);
	a.title = value;
	a.href = "../db/poll.php?Question=" + value;
	elem.appendChild(a);
	elem.appendChild(document.createElement('br'));
	elem.appendChild(document.createElement('br'));
	elem.appendChild(document.createElement('br'));
}


function clearSearch(){
	var list = document.getElementById('dynamicSearch');

	while (list.firstChild) {
		list.removeChild(list.firstChild);
	}

}