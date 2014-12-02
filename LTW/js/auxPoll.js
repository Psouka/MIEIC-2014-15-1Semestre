function showOptions(idQuery,username) {
		sendVote(idQuery,username)
}

function sendVote(idQuery,username){
	var rates =  document.getElementsByName('Vote');
	var OptionX= '';
	for(var i = 0; i < rates.length; i++){
		if(rates[i].checked){
			OptionX = rates[i].value;
		}
	}
	if(OptionX == '')
	{
		alert('Select one option');
		return;
	}
	$.post("../db/newVote.php", {'idQuery' : idQuery, 'OptionX' : OptionX , 'Username' : username}, registed);
	document.getElementsByClassName('chart')[0].display.style = 'block';
	document.getElementsByClassName('dynamicOptions')[0].display.style = 'none';
	alert('Vote registed!')
}

function  OptionsReceived(data) {
	$.each(data, resultOptions);
}

// Called for each line received
function resultOptions(index, value) {
	seeOptions = 1;
	var radioHtml = value +'<input type="radio" name="Vote"';
	radioHtml += 'value="' + value + '"'
	radioHtml += '/>';
	var radioFragment = document.createElement('div');
	radioFragment.innerHTML = radioHtml;

	document.getElementById('dynamicOptions').appendChild(radioFragment);
	return radioFragment.firstChild;
}

function init(seeOptions) {
	if(seeOptions == 0) {
		$.getJSON("../db/getAnswers.php", {'idQuery' : idQuery}, OptionsReceived);
	}
	else {
		document.getElementsByClassName('chart')[0].display.style = 'none';
	}
}
