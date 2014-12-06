function searchPolls(page)
{
	var elem = document.getElementById('dynamicSearch');
	var h1 = document.createElement('H1');
	var tE = document.createTextNode('My Polls: ');
	var ul = document.createElement('ul');
	ul.setAttribute('id', 'pollList');
	h1.appendChild(tE);
	elem.appendChild(h1);
	elem.appendChild(ul);
	search_p(page);
}

function search_p(page) {

	var data = $.getJSON("../db/getPolls.php",{'numPag' : page}, PollsReceived);
	if(data.lenght == 0) {
		return 0;
	}
	else 
		return 1;
}

// Called when messages are received
function  PollsReceived(data) {
	$.each(data, resultPoll);
}

// Called for each line received
function resultPoll(index, value) {
	var elem = document.getElementById('pollList');
	var li = document.createElement('li');
	var a = document.createElement('a');
	var linkText = document.createTextNode(value);
	a.appendChild(linkText);
	a.title = value;
	a.href = "../db/poll.php?Question=" + value;
	li.appendChild(a);
	elem.appendChild(li);
	elem.appendChild(document.createElement('br'));
}
