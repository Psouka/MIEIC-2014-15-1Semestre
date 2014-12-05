var multiple = 0;
var idQ;

function sendVote(idQuery, username){
	var rates =  document.getElementsByName('Vote');
	var OptionX = [];
	for(var i = 0; i < rates.length; i++){
		if(rates[i].checked){
			OptionX.push(rates[i].value);
		}
	}
	if(OptionX.length == 0)
	{
		alert('Select one option');
		return;
	}

	$.post("../db/newVote.php", {'idQuery' : idQuery, 'OptionX' : JSON.stringify(OptionX) , 'Username' : username}, location.reload(true));
}

function  OptionsReceived(data) {
	$.each(data, resultOptions);
}

// Called for each line received
function resultOptions(index, value) {
	seeOptions = 1;
	if(multiple == 0)
		var radioHtml = '<input type="radio" name="Vote"';
	else
		var radioHtml = '<input type="checkbox" name="Vote"';
	radioHtml += 'value="' + value + '"'
	radioHtml += '/>' + value;
	var radioFragment = document.createElement('div');
	radioFragment.setAttribute('class', 'radio');
	radioFragment.innerHTML = radioHtml;

	document.getElementById('dynamicOptions').appendChild(radioFragment);

	return radioFragment.firstChild;
}

function initMultiple(data){
	console.log(data);
	multiple = data;
	$.getJSON("../db/getAnswers.php", {'idQuery' : idQ}, OptionsReceived);
}

function init(seeOptions, idQuery) {
	idQ = idQuery;
	if(seeOptions == 0) {
		$.get("../db/getPolltype.php",{'idQuery' : idQuery},initMultiple);
		
	}
}