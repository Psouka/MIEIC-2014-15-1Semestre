var seeOptions = 0;


function showOptions(idQuery,username,ip) {
	if(seeOptions == 0)
		$.getJSON("../db/getAnswers.php", {'idQuery' : idQuery}, OptionsReceived);
	else
		sendVote(idQuery,username,ip)
}

function sendVote(idQuery,username,ip){
	var rates =  document.getElementsByName('Vote');
	var OptionX= '';
	for(var i = 0; i < rates.length; i++){
		if(rates[i].checked){
			OptionX = rates[i].value;
		}
	}
	if(OptionX == '')
	{
		alert('Select One');
		return;
	}
	$.postJSON("../db/newVote.php", {'idQuery' : idQuery, 'OptionX' : OptionX, 'IpUser' : ip , 'Username' : username}, alert('Registed'));
}

function  OptionsReceived(data) {
	alert(data);
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
